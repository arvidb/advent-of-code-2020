from functools import lru_cache

N = [0]
while True:
    try:
        N.append(int(input()))
    except:
        break

N.sort()

@lru_cache
def find_all(i, base):
    if i >= len(N):
        return 0
    if N[i] - base > 3:
        return 0
    if N[i] == max(N):
        return 1

    return sum([find_all(i+1, N[i]), find_all(i+2, N[i]), find_all(i+3, N[i])])

print(find_all(0, 0))