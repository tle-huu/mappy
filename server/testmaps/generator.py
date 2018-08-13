import sys                                          # for command line arguments
import random

# NORTH   = 1
# EAST    = 2
# SOUTH   = 4
# WEST    = 8

def mazeCreate(mx, my, level):
    maze = [[0 for x in range(my)] for y in range(mx)]
    #some random DFS i copied form Internet:
    orient_x = [0, 1, 0, -1]
    orient_y = [-1, 0, 1, 0]
    beg_y = 0

    for i in range(level):
        for j in range(mx):
            beg_x = random.randint(0, mx - 1)
            if (beg_x - 1 < 0 or maze[beg_x - 1][beg_y] == 0) and (beg_x + 1 >= mx or maze[beg_x + 1][beg_y] == 0): break
            # print ("here begx: ", beg_x, " mx: ", mx)

        for j in range(my):
            beg_y = random.randint(0, my - 1)
            if (beg_x - 1 < 0 or maze[beg_x - 1][beg_y] == 0) and (beg_x + 1 >= mx or maze[beg_x + 1][beg_y] == 0): break
            # print ("here2")
       
        maze[beg_x][beg_y] = 1
        end_x = random.randint(0, mx - 1)
        line_beg = beg_x if end_x > beg_x else end_x
        line_end = end_x if end_x > beg_x else beg_x
        while line_beg < line_end:
            maze[line_beg][beg_y] = 1
            line_beg += 1

        end_y = random.randint(0, my - 1)
        line_beg = beg_y if end_y > beg_y else end_y
        line_end = end_y if end_y > beg_y else beg_y
        while line_beg < line_end:
            maze[beg_x][line_beg] = 1
            line_beg += 1
        
        mazeTrim = [ y for x in maze for y in x]
        mazeStr = ''.join(map(str,mazeTrim))

    return (maze)


def generateMap(mx, my, level):
    filename = ''.join([str(mx), "x", str(my)])
    file = open(filename,"w+")
    mapDimentions = ''.join([str(mx), " ", str(my), "\n"])
    file.write(mapDimentions)
    maze = mazeCreate(mx, my, level)
    
    mazeTrim = [ y for x in maze for y in x]
    mazeStr = ''.join(map(str,mazeTrim))

    for i in range(mx * my):
        file.write(mazeStr[i])
        if (i+1) % my == 0: file.write("\n")
    
    file.close()


if len(sys.argv) < 4:
    print("Usage: ./generate <x> <y> <difficulty>")
    quit()

generateMap(int(sys.argv[1]), int(sys.argv[2]), int(sys.argv[3]))
