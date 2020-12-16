var rules = [(String, [ClosedRange<Int>])]()
var myTickets = [[Int]]()
var nearTickets = [[Int]]()

var i = 0
while let line = readLine() {
    guard !line.isEmpty else { continue }

    if line.last == ":" {
        i += 1
    }
    else if line.contains(":") {
        let tmp = line.split(separator: ":")
        let cl = String(tmp[0])
        let rule = tmp[1].split(separator: " ").compactMap(
            { range -> ClosedRange<Int>? in
                guard range != "or" else { return nil }
                let r = range.split(separator: "-")
                return Int(r[0])!...Int(r[1])!
            })
        rules.append((cl, rule))
    } 
    else {
        if i == 1 {
            myTickets.append(line.split(separator: ",").map({Int($0)!}))
        } else {
            nearTickets.append(line.split(separator: ",").map({Int($0)!}))
        }
    }
}

var validTickets = [[Int]]()
validTickets = nearTickets.filter({ ticket in
    var valid = true
    for n in ticket where !rules.contains(where: { $0.1.contains(where: { $0.contains(n) }) }) {
        valid = false
        break
    }

    return valid
})

var candidates = [String: [Int]]()
var found = Set<String>()
for i in 0..<validTickets.first!.count {
    let col = validTickets.map({ $0[i] })
    for rule in rules {
        if col.allSatisfy({ n in rule.1.contains(where: { $0.contains(n) }) }) {
            candidates[rule.0, default: []].append(i)
        }
    }
}

var confirmed = [Int: String]()
while confirmed.count != myTickets.first!.count {
    for candidate in candidates {
        let m = candidate.value.filter({ !confirmed.keys.contains($0) })
        if m.count == 1 {
            confirmed[m.first!] = candidate.key
        }
    }
}

var result = 1
for kv in confirmed.filter({ $0.value.starts(with: "departure")}) {
    result *= myTickets.first![kv.key]
}

print(result)
