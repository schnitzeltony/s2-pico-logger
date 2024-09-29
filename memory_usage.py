#!/usr/bin/env python3

import sys

def parse_line(line):
    parts = line.split()
    if len(parts) >= 3:
        return parts[0], parts[1], parts[2]
    return None, None, None

def main(map_file):
    mapFile = open(map_file, 'r', encoding='latin-1')
    for line in mapFile:
        name, originHex, sizeHex = parse_line(line)
        if(name == 'FLASH'):
            originHexFlash = originHex
            sizeHexFlash = sizeHex
        elif(name == '.flash_end'):
            endFlashHex = originHex
            endFlashDec = int(originHex, 16)
        elif(name == 'RAM'):
            originHexRam = originHex
            sizeHexRam = sizeHex
        elif(name == '.heap'):
            endRamDec = int(originHex, 16)
            endRamHex = originHex

    sizeDecFlash = int(sizeHexFlash, 16)
    print("")
    print("Flash:")
    print("Total: %s / %i" % (sizeHexFlash, sizeDecFlash))
    print("Start: %s / End: %s" % (originHexFlash, endFlashHex))
    flashUsed = endFlashDec - int(originHexFlash, 16)
    flashUsedPercent = flashUsed / sizeDecFlash * 100
    print("Used:  %i / %.2f%%" % (flashUsed, flashUsedPercent))

    sizeDecRam = int(sizeHexRam, 16)
    print("")
    print("RAM:")
    print("Total: %s / %i" % (sizeHexRam, sizeDecRam))
    print("Start: %s / End: %s" % (originHexRam, endRamHex))
    ramUsed = endRamDec - int(originHexRam, 16)
    ramUsedPercent = ramUsed / sizeDecRam * 100
    print("Used:  %i / %.2f%%" % (ramUsed, ramUsedPercent))

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: memory_usage.py <map-file>")
        sys.exit(1)
    main(sys.argv[1])

