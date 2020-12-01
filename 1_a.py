nums = set()
target = 2020
while True:
    try:
        cur = int(input())
        rem = target - cur
        if rem in nums:
            print("found", cur*rem)
            break
        else:
            nums.add(cur)
    except:
       break
        
