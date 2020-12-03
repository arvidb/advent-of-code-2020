
var numValid = 0
while let line = readLine() {
    let tmp = line.split(separator: " ")

    let range = tmp[0].split(separator: "-")
    let lo = Int(range[0])!
    let hi = Int(range[1])!
    let char = tmp[1].first!
    let pass = tmp[2]

    var cnt = [Character: Int]()

    for c in pass {
        cnt[c] = (cnt[c] ?? 0) + 1
    }

    let n = (cnt[char] ?? 0)
    if n >= lo && n <= hi {
        numValid += 1
    }
}

print(numValid)