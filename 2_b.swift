#!/usr/bin/swift -frontend -interpret -enable-source-import -I.

import helpers

var numValid = 0
while let line = readLine() {
    let tmp = line.split(separator: " ")

    let range = tmp[0].split(separator: "-")
    let lo = Int(range[0])!
    let hi = Int(range[1])!
    let char = tmp[1].first!
    let pass = tmp[2]

    let a = pass[hi-1]
    let b = pass[lo-1]
    if a == char || b == char {
        numValid += a == b ? 0 : 1
    }
}

print(numValid)