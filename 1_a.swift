let target: Int = 2020

var mem = Set<Int>()
while let tmp = readLine(), let i = Int(tmp) {
    let rem = target - i
    if mem.contains(rem) {
        print("found", i*rem)
    } else {
        mem.insert(i)
    }
}