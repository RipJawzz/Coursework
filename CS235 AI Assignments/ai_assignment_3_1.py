import random


# determines the fitness value of the queen_arrangement state
def fitness_value(queen_arrangement):
    fv = 0
    for i in range(8):
        ok = True
        for r in range(8):
            if r == i:
                continue
            # checks for same row
            if queen_arrangement[i] == queen_arrangement[r]:
                ok = False
                break
            # checks on diagonals
            if queen_arrangement[i] - i == queen_arrangement[r] - r or queen_arrangement[i] + i == queen_arrangement[
                r] + r:
                ok = False
                break

        if ok:
            fv += 1
    return fv


# generates the next generation of queen_arrangement state
def successors(queen_arrangement):
    curr_val = fitness_value(queen_arrangement)
    na = []
    suc = []
    for rq in range(8):
        ori = queen_arrangement[rq]
        # produce all successors by moving chosen queen
        for i in range(8):
            queen_arrangement[rq] = i
            if fitness_value(queen_arrangement) > curr_val:
                suc.append(queen_arrangement.copy())
        queen_arrangement[rq] = ori
        if len(suc) != 0:
            break
    return suc


# initialize a state with all 8 queens on the board
queen_arrangement = [random.randint(0, 7) for x in range(8)]
print('ori', queen_arrangement, fitness_value(queen_arrangement))
num_generated = 1
num_expanded = 0

# stochaistic hill climbing. Continues till no better successors are found
while True:
    suc = successors(queen_arrangement)
    num_expanded += 1
    suc_w=[]
    b=fitness_value(queen_arrangement)
    for i in suc:
        suc_w.append(fitness_value(i)-b)
    print('succ:')

    if not suc:
        print("Empty!")
        break
    for x in suc:
        print(x, fitness_value(x))

    num_expanded += 1
    num_generated += len(suc)
    # gets the next queens state from suc (successors list)
    queen_arrangement = random.choices(suc,suc_w)[0]
    print("current:", queen_arrangement, fitness_value(queen_arrangement))

# prints the queen arrangement
for i in range(8):
    for i2 in range(8):
        if queen_arrangement[i2] == i:
            print('+', end=' ')
        else:
            print('-', end=' ')
    print()
print('Final state:', queen_arrangement)
print('Fitness value is:', )
print(fitness_value(queen_arrangement))
print('Number of nodes generated :', num_generated)
print('Number of nodes expanded :', num_expanded)
