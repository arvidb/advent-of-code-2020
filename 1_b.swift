let target: Int = 2020

var nums = [Int]()
while let tmp = readLine(), let i = Int(tmp) {
    nums.append(i)
}

nums.sort()

for (i, num) in nums.enumerated() {
    var l = i+1
    var r = nums.count - 1
    while l < r {
        let cand = [num, nums[l], nums[r]]
        let sum = cand.reduce(0, +)
        if sum == target {
            print("found", cand.reduce(1, *))
            break
        } else if sum < target {
            l += 1
        } else {
            r -= 1
        }
    }
}