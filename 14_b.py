import re

def getBase(mask, addr):
    addr = str(bin(addr)[2:]).zfill(36)
    addr = list(addr)
    for i, c in enumerate(mask):
        if c == 'X':
            addr[i] = 'X'
            continue
        elif c == '1' or addr[i] == '1':
            addr[i] = '1'
        else:
            addr[i] = '0'
    return addr

def getAddress(mask):
    if mask.count('X') == 0:
        return [int(''.join(mask), 2)]

    addresses = []
    for i, b in enumerate(mask):
        if b == 'X':
            mask[i] = '0'
            addresses += getAddress(list(mask))
            mask[i] = '1'
            addresses += getAddress(list(mask))

    return addresses



MEM = {}
mask = ""
while True:
    try:
        line = input()
        if line.startswith("mask"):
            mask = line[7:]
        else:
            m, b = line.split("=")
            m = re.sub('[^0-9]+','', m)
            b = int(b)

            for addr in getAddress(getBase(mask, int(m))):
                MEM[addr] = b
    except:
        break

print(sum(MEM.values()))
