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
            startFlash = int(originHex, 16)
            sizeFlash = int(sizeHex, 16)
        elif(name == '.flash_end'):
            endFlashUsed = int(originHex, 16)
        elif(name == 'RAM'):
            startRam = int(originHex, 16)
            sizeRam = int(sizeHex, 16)
        elif(name == '.heap'):
            endRamUsed = int(originHex, 16)

    endFlash = startFlash + sizeFlash -1
    flashUsed = endFlashUsed - startFlash
    flashUsedPercent = flashUsed / sizeFlash * 100

    iEndRam = startRam + sizeRam -1
    ramUsed = endRamUsed - startRam
    ramUsedPercent = ramUsed / sizeRam * 100

    print("")
    print("Flash available: 0x%08X-0x%08X / %i bytes" % (startFlash, endFlash, sizeFlash))
    print("Flash used:      %i bytes (%.2f%%)" % (flashUsed, flashUsedPercent))
    print("RAM available:   0x%08X-0x%08X / %i bytes" % (startRam, iEndRam, sizeRam))
    print("RAM used:        %i bytes (%.2f%%)" % (ramUsed, ramUsedPercent))
    print("")

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: memory_usage.py <map-file>")
        sys.exit(1)
    main(sys.argv[1])

