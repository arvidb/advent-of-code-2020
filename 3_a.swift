var map = [String]()
while let line = readLine() {
    map.append(line)
}

var nTrees = 0
var pos = (x: 0, y: 0)
while pos.y < map.count {

    if map[pos.y][pos.x] == "#" {
        nTrees += 1
    }

    pos = ((pos.x + 3) % map.first!.count, 
           pos.y + 1)
}

print(nTrees)