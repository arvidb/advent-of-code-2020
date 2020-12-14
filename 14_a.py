import re
MEM = {}
mask = ""
while True:
    try:
        line = input()
        if line.startswith("mask"):
            mask = line
        else:
            m, b = line.split("=")
            m = re.sub('[^0-9]+','', m)
            b = int(b)

            for i, c in enumerate(mask[::-1]):
                if c == 'X':
                    continue
                elif c == '0':
                    b &= ~(1 << i)
                elif c == '1':
                    b |= 1 << i
            MEM[m] = b
    except:
        break

print(sum(MEM.values()))

