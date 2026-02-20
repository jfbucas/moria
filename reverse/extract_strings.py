import sys

DUMP_PATH = '/home/edo/prog/moria2014/moria/reverse/memory.dump'
SEGMENT_BASE = 0x22DE0

with open(DUMP_PATH, 'rb') as f:
    data = f.read()
dump_size = len(data)

def read_pascal_string(pos, max_len):
    if pos >= dump_size: return None
    length = data[pos]
    if length == 0 or length > max_len: return None
    if pos + 1 + length > dump_size: return None
    raw = data[pos + 1 : pos + 1 + length]
    bad = sum(1 for b in raw if b < 0x20 and b not in (0x09, 0x0D))
    if bad > max(1, len(raw) * 0.1): return None
    try:
        text = raw.decode('cp850')
        if text.endswith(chr(0x0D)): text = text[:-1]
        if not text.strip(): return None
        return (length, text)
    except:
        return None

print('=' * 100)
print('MORIA DOS 1.9.8.7 - COMPLETE STRING EXTRACTION FROM MEMORY DUMP')
print('=' * 100)
print('Memory dump: %d bytes (0x%X)' % (dump_size, dump_size))
print('DS segment base: 0x%X' % SEGMENT_BASE)
print()

total = 0

print('=' * 100)
print('SECTION 1: MAIN MESSAGE TABLE (DS-relative offsets, 16-bit unsigned wrap)')
print('=' * 100)
print()
print('  ID | Rgn | Abs Offset | DS:Offset | Len | Text')
print('-----+-----+------------+-----------+-----+' + '-' * 55)

for msg_id in range(0, 550):
    if msg_id <= 100:
        signed = msg_id * 51 - 15287
        region = 1; max_len = 50
    elif msg_id <= 300:
        signed = (msg_id - 100) * 31 - 10677
        region = 2; max_len = 30
    elif msg_id <= 400:
        signed = (msg_id - 300) * 73 - 17572
        region = 3; max_len = 72
    else:
        signed = (msg_id - 400) * 16 - 7283
        region = 4; max_len = 15
    unsigned = signed & 0xFFFF
    pos = SEGMENT_BASE + unsigned
    result = read_pascal_string(pos, max_len)
    if result:
        length, text = result
        print('%4d |  R%d | 0x%08X |  0x%04X   | %3d | %s' % (msg_id, region, pos, unsigned, length, text))
        total += 1

print()

print('=' * 100)
print('SECTION 2: ITEM/PROPERTY DESCRIPTION TABLE (stride 29, base 0x2A967)')
print('=' * 100)
print()
print('  # | Abs Offset | Len | Text')
print('----+------------+-----+' + '-' * 55)
base29 = 0x2A967
for i in range(0, 200):
    pos = base29 + i * 29
    if pos >= dump_size - 29: break
    result = read_pascal_string(pos, 28)
    if result:
        length, text = result
        print('%3d | 0x%08X | %3d | %s' % (i, pos, length, text))
        total += 1

print()

tables = [
    ('POTION COLORS (base order)', -0x5e49, 24),
    ('POTION COLORS (shuffled)', -0x5cc9, 24),
    ('RING MATERIALS (base order)', -0x5b49, 19),
    ('RING MATERIALS (shuffled)', -0x5a19, 19),
    ('WAND WOODS (base order)', -0x58e9, 22),
    ('WAND WOODS (shuffled)', -0x5789, 22),
    ('GEMS (base order)', -0x5629, 10),
    ('GEMS (shuffled)', -0x5589, 10),
]

print('=' * 100)
print('SECTION 3: RANDOMIZATION LOOKUP TABLES (stride 16, DS-relative)')
print('=' * 100)

for name, base_offset, max_items in tables:
    print()
    print('--- %s ---' % name)
    print('  # | Abs Offset | Len | Text')
    print('----+------------+-----+' + '-' * 30)
    for i in range(1, max_items + 1):
        signed = i * 16 + base_offset
        unsigned = signed & 0xFFFF
        pos = SEGMENT_BASE + unsigned
        result = read_pascal_string(pos, 15)
        if result:
            length, text = result
            print('%3d | 0x%08X | %3d | %s' % (i, pos, length, text))
            total += 1

print()
print('=' * 100)
print('GRAND TOTAL Strings extracted: %d' % total)
print('=' * 100)
