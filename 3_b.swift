#!/usr/bin/swift -frontend -interpret -enable-source-import -I.

import helpers

var map = [String]()
while let line = readLine() {
    map.append(line)
}

var result = [Int]()
let checks: [(x:Int, y:Int)] = [(1, 1), (3, 1), (5, 1), (7, 1), (1, 2)]
for check in checks {
    var nTrees = 0
    var pos = (x: 0, y: 0)
    
    while pos.y < map.count {
        if map[pos.y][pos.x] == "#" {
            nTrees += 1
        }

        pos = ((pos.x + check.x) % map.first!.count, 
               pos.y + check.y)
    }

    result.append(nTrees)
}

print(result.reduce(1, { $0 * $1 }))