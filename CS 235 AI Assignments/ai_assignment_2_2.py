class state:
    def __init__(self, c_l, m_l, cost, boat, depth, parent):
        self.c_l = c_l
        self.m_l = m_l
        self.cost = cost
        self.boat = boat
        self.depth = depth
        self.parent = parent


def successor(st):
    rl = []
    if st.boat == "left":
        if st.c_l >= 2:
            rl.append(state(st.c_l - 2, st.m_l, st.cost + 2 * cost_c, "right", st.depth + 1, st))
        if st.c_l >= 1:
            rl.append(state(st.c_l - 1, st.m_l, st.cost + cost_c, "right", st.depth + 1, st))
        if st.m_l >= 2:
            rl.append(state(st.c_l, st.m_l - 2, st.cost + 2 * cost_m, "right", st.depth + 1, st))
        if st.m_l >= 1:
            rl.append(state(st.c_l, st.m_l - 1, st.cost + cost_m, "right", st.depth + 1, st))
        if st.c_l >= 1 and st.m_l >= 1:
            rl.append(state(st.c_l - 1, st.m_l - 1, st.cost + cost_m + cost_c, "right", st.depth + 1, st))

    elif st.boat == "right":
        if st.c_l <= 1:
            rl.append(state(st.c_l + 2, st.m_l, st.cost + 2 * cost_c, "left", st.depth + 1, st))
        if st.c_l <= 2:
            rl.append(state(st.c_l + 1, st.m_l, st.cost + cost_c, "left", st.depth + 1, st))
        if st.m_l <= 2:
            rl.append(state(st.c_l, st.m_l + 1, st.cost + cost_m, "left", st.depth + 1, st))
        if st.c_l <= 1:
            rl.append(state(st.c_l, st.m_l + 2, st.cost + 2 * cost_c, "left", st.depth + 1, st))
        if st.c_l <= 2 and st.m_l <= 2:
            rl.append(state(st.c_l + 1, st.m_l + 1, st.cost + cost_c + cost_m, "left", st.depth + 1, st))
    return rl


def check(st):
    stat = 0
    if st.m_l != 0 and st.m_l < st.c_l:
        stat = 1
        print("Invalid")
    elif st.m_l != 3 and st.m_l > st.c_l:
        stat = 1
        print("Invalid")
    return stat


print("AI Assignment 2 Part 2:\n-------------------------------\n\n\n")
print("Note:- Lists contain states but are displaying only by arc cost so far")
print("States are represented by: (missionaries on left bank, cannibals on left bank, position of boat, arc cost)")

ol = []
cl = []
ex = 0
ge = 1
cost_c = 20
cost_m = 10

start = state(3, 3, 0, "left", 0, None)
goal = state(0, 0, 0, "nope", 0, start)
print("\nBFS")
ol.append(start)
while len(ol) != 0:
    stat = 0
    print("OL : ", end='')
    for x in ol:
        print(x.cost, end=' ')
    print()
    print("CL : ", end='')
    for x in cl:
        print(x.cost, end=' ')
    print()

    st = ol.pop(0)
    print("Extracted node : ", "(", st.m_l, st.c_l, st.boat, st.cost, ")")
    stat = check(st)
    if st.c_l == 0 and st.m_l == 0 and st.boat == "right":
        goal = st
        break

    for x in ol:
        if x.m_l == st.m_l and x.c_l == st.c_l and x.boat == st.boat:
            if x.cost > st.cost:
                ol.remove(x)
                break
            else:
                print("already in ol")
                stat = 1

    for x in cl:
        if x.m_l == st.m_l and x.c_l == st.c_l and x.boat == st.boat:
            if x.cost > st.cost:
                cl.remove(x)
                break
            else:
                print("already in cl")
                stat = 1

    if stat == 0:
        cl.append(st)
        ex = ex + 1
    else:
        print("State is dropped")
    if stat == 0:
        rl = successor(st)
        ge = ge + len(rl)
        ol = ol + rl
print("Generated nodes", ge)
print("Expanded nodes", ex)
if goal.boat == "nope":
    print("Solution doesnt exist")
else:
    print("Found solution with cost is", goal.cost)
    print("The path is:")
    gp = []
    while goal != None:
        gp.insert(0, goal)
        goal = goal.parent
    for x in gp:
        print("(", x.m_l, x.c_l, x.boat, x.cost, ")")

ol.clear()
cl.clear()
ex = 0
ge = 1
goal = state(0, 0, 0, "nope", 0, None)
start = state(3, 3, 0, "left", 0, start)
print("\nDFS")
ol.append(start)
while len(ol) != 0:
    stat = 0
    print("OL : ", end='')
    for x in ol:
        print(x.cost, end=' ')
    print()
    print("CL : ", end='')
    for x in cl:
        print(x.cost, end=' ')
    print()
    st = ol.pop(0)
    print("Extracted node : ", "(", st.m_l, st.c_l, st.boat, st.cost, ")")
    stat = check(st)
    if st.c_l == 0 and st.m_l == 0 and st.boat == "right":
        goal = st
        break

    for x in ol:
        if x.m_l == st.m_l and x.c_l == st.c_l and x.boat == st.boat:
            if x.cost > st.cost:
                ol.remove(x)
                break
            else:
                print("already in ol")
                stat = 1

    for x in cl:
        if x.m_l == st.m_l and x.c_l == st.c_l and x.boat == st.boat:
            if x.cost > st.cost:
                cl.remove(x)
                break
            else:
                print("already in cl")
                stat = 1

    if stat == 0:
        cl.append(st)
        ex = ex + 1
    else:
        print("State is dropped")
    if stat == 0:
        rl = successor(st)
        ge = ge + len(rl)
        ol = rl + ol

print("Generated nodes", ge)
print("Expanded nodes", ex)
if goal.boat == "nope":
    print("Solution doesnt exist")
else:
    print("Found solution with cost is", goal.cost)
    print("The path is:")
    gp = []
    while goal != None:
        gp.insert(0, goal)
        goal = goal.parent
    for x in gp:
        print("(", x.m_l, x.c_l, x.boat, x.cost, ")")

print("\nIterative depth search with k =", 20)
for k in range(20):
    ol.clear()
    cl.clear()
    ex = 0
    ge = 1
    goal = state(0, 0, 0, "nope", 0, None)
    start = state(3, 3, 0, "left", 0, start)
    ol.append(start)
    print("Iterating with k=", k)
    while len(ol) != 0:
        ol.sort(key=lambda x: x.cost, reverse=True)
        stat = 0
        print("OL : ", end='')
        for x in ol:
            print(x.cost, end=' ')
        print()
        print("CL : ", end='')
        for x in cl:
            print(x.cost, end=' ')
        print()
        st = ol.pop(0)
        print("Extracted node : ", "(", st.m_l, st.c_l, st.boat, st.cost, ")")
        if st.depth > k:
            stat = 1
        stat = check(st)
        if st.c_l == 0 and st.m_l == 0 and st.boat == "right":
            goal = st
            break

        for x in ol:
            if x.m_l == st.m_l and x.c_l == st.c_l and x.boat == st.boat:
                if x.cost > st.cost:
                    ol.remove(x)
                    break
                else:
                    print("already in ol")
                    stat = 1

        for x in cl:
            if x.m_l == st.m_l and x.c_l == st.c_l and x.boat == st.boat:
                if x.cost > st.cost:
                    cl.remove(x)
                    break
                else:
                    print("already in cl")
                    stat = 1

        if stat == 0:
            cl.append(st)
            ex = ex + 1

        else:
            print("State is dropped")
        if stat == 0:
            rl = successor(st)
            ge = ge + len(rl)
            ol = rl + ol

    print("Generated nodes", ge)
    print("Expanded nodes", ex)
    if goal.boat == "nope":
        print("Solution doesnt exist")
    else:
        print("Found solution with cost is", goal.cost)
        print("The path is:")
        gp = []
        while goal != None:
            gp.insert(0, goal)
            goal = goal.parent
        for x in gp:
            print("(", x.m_l, x.c_l, x.boat, x.cost, ")")
        break

ol.clear()
cl.clear()
ex = 0
ge = 1
goal = state(0, 0, 0, "nope", 0, None)
start = state(3, 3, 0, "left", 0, start)
print("\nUCS")
ol.append(start)
while len(ol) != 0:
    ol.sort(key=lambda x: x.cost, reverse=False)
    stat = 0
    print("OL : ", end='')
    for x in ol:
        print(x.cost, end=' ')
    print()
    print("CL : ", end='')
    for x in cl:
        print(x.cost, end=' ')
    print()
    st = ol.pop(0)
    print("Extracted node : ", "(", st.m_l, st.c_l, st.boat, st.cost, ")")
    stat = check(st)
    if st.c_l == 0 and st.m_l == 0 and st.boat == "right":
        goal = st
        break

    for x in ol:
        if x.m_l == st.m_l and x.c_l == st.c_l and x.boat == st.boat:
            if x.cost > st.cost:
                ol.remove(x)
                break
            else:
                print("already in ol")
                stat = 1

    for x in cl:
        if x.m_l == st.m_l and x.c_l == st.c_l and x.boat == st.boat:
            if x.cost > st.cost:
                cl.remove(x)
                break
            else:
                print("already in cl")
                stat = 1

    if stat == 0:
        cl.append(st)
        ex = ex + 1
    else:
        print("State is dropped")

    if stat == 0:
        rl = successor(st)
        ge = ge + len(rl)
        ol = ol + rl
print("Generated nodes", ge)
print("Expanded nodes", ex)

if goal.boat == "nope":
    print("Solution doesnt exist")
else:
    print("Found solution with cost is", goal.cost)
    print("The path is:")
    gp = []
    while goal != None:
        gp.insert(0, goal)
        goal = goal.parent
    for x in gp:
        print("(", x.m_l, x.c_l, x.boat, x.cost, ")")
