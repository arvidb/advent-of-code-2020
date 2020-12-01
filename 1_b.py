nums = []
target = 2020
while True:
    try:
        nums.append(int(input()))
    except:
        break
        
nums.sort()

for i, cur in enumerate(nums):
    l = i+1
    r = len(nums)-1
    
    while(l < r):
        sum3 = sum([cur, nums[l], nums[r]])
        if (sum3 == target):
            print("found", cur * nums[l] * nums[r])
            break
        elif (sum3 < target):
            l += 1
        else:
            r -= 1
        
