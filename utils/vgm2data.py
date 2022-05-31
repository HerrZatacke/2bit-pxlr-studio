#!/usr/bin/env python3
import sys
from struct import unpack
from pathlib import Path
from optparse import OptionParser

def main(argv=None):
    parser = OptionParser("Usage: vgm2data.py [options] INPUT_FILE_NAME.VGM")
    parser.add_option("-o", '--out',        dest='outfilename',                                      help='output file name')
    parser.add_option("-i", '--identifier', dest='identifier',                                       help='C source identifier')

    parser.add_option("-1", "--no-nr1x",    dest="no_nr1x",     action="store_true",  default=False, help='disable channel 0')
    parser.add_option("-2", "--no-nr2x",    dest="no_nr2x",     action="store_true",  default=False, help='disable channel 1')
    parser.add_option("-3", "--no-nr3x",    dest="no_nr3x",     action="store_true",  default=False, help='disable channel 2')
    parser.add_option("-4", "--no-nr4x",    dest="no_nr4x",     action="store_true",  default=False, help='disable channel 3')
    parser.add_option("-5", "--no-nr5x",    dest="no_nr5x",     action="store_true",  default=False, help='disable NR5X manipulation')
    parser.add_option("-s", "--no-init",    dest="no_init",     action="store_true",  default=False, help='disable sound init')
    parser.add_option("-w", "--no-wave",    dest="no_wave",     action="store_true",  default=False, help='disable waveform loading')

    parser.add_option("-d", "--delay",      dest='delay',                             default=1,     help='delay size')
    parser.add_option("-b", '--bank',       dest='bank',        default="255",                       help='BANK number (default AUTO=255)')    

    (options, args) = parser.parse_args()

    if (len(args) == 0):
        parser.print_help()
        parser.error("Input file name required\n")
    
    infilename = Path(args[0])
    
    if options.outfilename == None:
        outfilename = infilename.with_suffix('.c')
    else:
        outfilename = Path(options.outfilename)
        
    if options.identifier == None:
        identifier = str(Path(infilename.name).with_suffix(''))
    else: 
        identifier = options.identifier
                
    disabled_channels = set()
    if (options.no_nr1x): 
        disabled_channels.add(0)
        print("Channel 1 disabled")
    if (options.no_nr2x): 
        disabled_channels.add(1)
        print("Channel 2 disabled")
    if (options.no_nr3x): 
        disabled_channels.add(2)
        print("Channel 3 disabled")
    if (options.no_nr4x): 
        disabled_channels.add(3)
        print("Channel 4 disabled")
    if (options.no_nr5x):
        print("NR5x registers disabled")
    if (options.no_wave):
        print("waveform data update disabled")
               
    with open(str(infilename), "rb") as inf:
        channel_mute_mask = 0

        # check VGM format
        if inf.read(4) != b'Vgm ':
            print("invalid file format")
            sys.exit(1)
        inf.seek(0x08)
        if (unpack('<I', inf.read(4))[0] < 0x161):
            print("VGM version too low")
            sys.exit(1)
        inf.seek(0x80)
        if (unpack('<I', inf.read(4))[0] == 0):
            print("VGM must contain GameBoy data")
            sys.exit(1)
            
        # output C source file
        with open(str(outfilename), "wb") as outf:                
            inf.seek(0x34)
            offset = unpack('<I', inf.read(4))[0]
            inf.seek(offset - 4, 1)

            outf.write(bytes(("#pragma bank {1:s}\n\n"
                              "#include <gbdk/platform.h>\n"
                              "#include <stdint.h>\n\n"
                              "BANKREF({0:s})\n"
                              "const uint8_t {0:s}[] = {{\n").format(identifier, options.bank), "ascii"))

            row = {}
            data = inf.read(1)
            while (data):
                if data == b'\x66':
                    outf.write(bytes("1,0b{:08b}\n}};\n".format(7), "ascii"))
                    break;
                elif data == b'\xb3':
                    addr, data = unpack('BB', inf.read(2))
                    addr += 0x10
                    if addr in range(0x10, 0x16):
                        row.setdefault(0, {})[addr-0x10]=data
                    elif addr in range(0x16, 0x20):
                        row.setdefault(1, {})[addr-0x15]=data
                    elif addr in range(0x1A, 0x1F):
                        row.setdefault(2, {})[addr-0x1A]=data
                    elif addr in range(0x20, 0x24):
                        row.setdefault(3, {})[addr-0x1F]=data
                    elif addr in range(0x24, 0x27):
                        row.setdefault(4, {})[addr-0x24]=data
                    elif addr in range(0x30, 0x40):
                        row.setdefault(5, {})[addr-0x30]=data
                    else:
                        print("ERROR: Invalid register address: 0x{:02x}".format(addr))
                        sys.exit(1)
                    value = data
                elif data == b'\x62':            
#                    if (not row.setdefault(0, {}).setdefault(4, None)):
#                        row.pop(0, None)
#                    if (not row.setdefault(1, {}).setdefault(4, None)):
#                        row.pop(1, None)
                        
                    result = ""    
                    count = 0    
                    # NR5x regs:
                    ch = row.pop(4, None)
                    if (ch) and (not options.no_nr5x):
                        val = ch.pop(3, -1)
                        if (val != -1) and (not options.no_init):
                            count += 1
                            result = "{}0b{:08b},0x{:02x},".format(result, 0b00100100, val)
                        mask = 4
                        tmp = ""
                        for i in range(0, 2):
                            val = ch.pop(i, -1)
                            if (val != -1):
                                mask |= 1 << (7 - i)
                                tmp = "{}0x{:02x},".format(tmp, val)
                        if (mask != 4):
                            count += 1
                            result = "{}0b{:08b},{}".format(result, mask, tmp)
                    
                    # AUD3WAVE[]
                    ch = row.pop(5, None)
                    if (ch) and (not options.no_wave):
                        mask = 5
                        tmp = ""
                        for i in range(0, 16):
                            val = ch.pop(i, 0)
                            tmp = "{}0x{:02x},".format(tmp, val)
                        count += 1
                        result = "{}0b{:08b},{}".format(result, mask, tmp)                    
                        
                    # NR1x, NR2x, NR3x, NR4x regs:
                    for j in range(0, 4):
                        ch = row.pop(j, None)
                        if (ch) and (not j in disabled_channels):
                            mask = j
                            tmp = ""
                            for i in range(0, 5):
                                val = ch.pop(i, -1)
                                if (val != -1):
                                    mask |= 1 << (7 - i)
                                    tmp = "{}0x{:02x},".format(tmp, val)
                            if (mask != j) and ((mask & 0b00001000) != 0):
                                count += 1
                                result = "{}0b{:08b},{}".format(result, mask, tmp)
                                channel_mute_mask |= (1 << j)

                    # optional delay
                    count |= max(0, int(options.delay) - 1) << 4

                    # output result
                    result = "0x{:02x},{}\n".format(count, result)
                    outf.write(bytes(result, "ascii"))

                    # reset row
                    row = {}
                    pass
                else:
                    print("ERROR: unsupported command 0x{:02x}".format(unpack('B', data)[0]))
                    sys.exit(1)
                data = inf.read(1)
                
            outf.write(bytes("void AT(0b{1:08b}) __mute_mask_{0:s};".format(identifier, channel_mute_mask), "ascii"))

        # output C header file
        if outfilename.suffix == ".c":
            with open(str(outfilename.with_suffix('.h')), "wb") as hdrf:
                hdrf.write(bytes(("#ifndef __{0:s}_INCLUDE__\n"
                                  "#define __{0:s}_INCLUDE__\n\n"
                                  "#include <gbdk/platform.h>\n"
                                  "#include <stdint.h>\n\n"
                                  "#define MUTE_MASK_{0:s} 0b{1:08b}\n\n"
                                  "BANKREF_EXTERN({0:s})\n"
                                  "extern const uint8_t {0:s}[];\n"
                                  "extern void __mute_mask_{0:s};\n\n"
                                  "#endif\n").format(identifier, channel_mute_mask), "ascii"))
        
if __name__=='__main__':
    main()
