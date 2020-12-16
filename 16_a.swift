var rules = [String: [ClosedRange<Int>]]()
var myTickets = [[Int]]()
var nearTickets = [[Int]]()

var i = 0
while let line = readLine() {
    if line.last == ":" {
        i += 1
    }
    else if line.contains(":") {
        let tmp = line.split(separator: ":")
        let cl = String(tmp[0])
        let rule = tmp[1].split(separator: " ").compactMap({ range -> ClosedRange<Int>? in
            guard range != "or" else { return nil }
            let r = range.split(separator: "-")
            return Int(r[0])!...Int(r[1])!
            })
        rules[cl] = rule
    } 
    else {
        if i == 1 {
            myTickets.append(line.split(separator: ",").map({Int($0)!}))
        } else {
            nearTickets.append(line.split(separator: ",").map({Int($0)!}))
        }
    }
}

var result = 0
for ticket in nearTickets {
    for n in ticket {
        if !rules.values.contains(where: { $0.contains(where: { $0.contains(n) }) }) {
            result += n
        }
    }
}

print(result)
