N = []
while True:
    try:
        N.append(int(input()))
    except:
        break

N.sort()

base = 0
result = [0] * 4
for n in N:
    result[n-base] += 1
    base = n

print(result[1] * (result[3] + 1))
