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
            flashStart = int(originHex, 16)
            flashSize = int(sizeHex, 16)
        elif(name == '.flash_end'):
            flashUsedEnd = int(originHex, 16)
        elif(name == 'RAM'):
            ramStart = int(originHex, 16)
            ramSize = int(sizeHex, 16)
        elif(name == '.heap'):
            ramUsedEnd = int(originHex, 16)

    flashUsed = flashUsedEnd - flashStart
    flashUsedPercent = flashUsed / flashSize * 100
    flashLast = flashStart + flashSize - 1

    ramUsed = ramUsedEnd - ramStart
    ramUsedPercent = ramUsed / ramSize * 100
    ramLast = ramStart + ramSize - 1

    print("")
    print("Flash available: 0x%08X-0x%08X / %i bytes" % (flashStart, flashLast, flashSize))
    print("Flash used:      %i bytes (%.2f%%)" % (flashUsed, flashUsedPercent))
    print("RAM available:   0x%08X-0x%08X / %i bytes" % (ramStart, ramLast, ramSize))
    print("RAM used:        %i bytes (%.2f%%)" % (ramUsed, ramUsedPercent))
    print("")

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: memory_usage.py <map-file>")
        sys.exit(1)
    main(sys.argv[1])

