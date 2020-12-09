N = []
while True:
    try:
        N.append(int(input()))
    except:
        break

def isValid(P, target):
    mem = set()
    for i in P:
        if target-i in mem:
            return True
        else:
            mem.add(i)
    return False

p_size = 25
invalid = 0
for i in range(p_size, len(N)):
    P = N[i-p_size:i]
    target = N[i]
    if not isValid(P, target):
        invalid = target
        break

print(invalid)

for i in range(len(N)): 
    sum = N[i] 
    for j in range(i+1, len(N)):
        sum += N[j] 
        if sum == invalid: 
            print(min(N[i:j-1]) + max(N[i:j-1]))
            exit()
        elif sum > invalid: 
            break