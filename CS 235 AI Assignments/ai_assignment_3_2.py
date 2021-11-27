import random


def func_value(gene):
    num = gene_value(gene)
    return 2 * num * num + 1


def gene_value(gene):
    return gene[0] * 4 + gene[1] * 2 + gene[2] * 1


def mutate(gene):
    # mutating gene with 25% probability
    if random.randint(0, 3) >= 3:
        print('Mutating!', gene)
        # randomly select a bit to mutate
        n = random.randint(0, len(gene)-1)
        gene[n] = 1 if gene[n] == 0 else 0
        print('Mutated', gene)
    return gene


# find the best chromosome from the set of genes
def max_genes(genes):
    b = genes[0]
    for i in genes:
        if func_value(i) > func_value(b):
            b = i.copy()
    return b.copy()


# generate the next generation from genes generation
def next_gen(genes):
    global num_exp
    global num_gen
    next = []
    while len(next) != population_size:
        # k-way selection
        p_pool = genes.copy()
        p1 = p_pool[random.randint(0, len(p_pool) - 1)].copy()
        p_pool.remove(p1)
        p2 = p_pool[random.randint(0, len(p_pool) - 1)].copy()
        p_pool.remove(p2)
        b1 = p2.copy()
        if func_value(p1) > func_value(p2):
            b1 = p1.copy()

        p_pool = genes.copy()
        p1 = p_pool[random.randint(0, len(p_pool) - 1)].copy()
        p_pool.remove(p1)
        p2 = p_pool[random.randint(0, len(p_pool) - 2)].copy()
        p_pool.remove(p2)
        b2 = p2.copy()
        if func_value(p1) > func_value(p2):
            b2 = p1.copy()

        print('Parent pair', b1, b2)

        o1 = b1.copy()
        o2 = b2.copy()
        # uniform crossover
        for i in range(0, len(o1)):
            if random.randint(0, 4) > 3:
                t = o1[i]
                o1[i] = o2[i]
                o2[i] = t
        print('offsprings ', o1, o2)
        num_gen = num_gen + 2
        num_exp = num_exp + 2
        # mutating
        o1 = mutate(o1)
        o2 = mutate(o2)
        # validation of offsprings
        if gene_value(o1) == 7 or gene_value(o1) == 0:
            print('Invalid offspring!', o1)
        else:
            next.append(o1.copy())
        if gene_value(o2) == 7 or gene_value(o2) == 0:
            print('Invalid offspring!', o2)
        elif len(next) != population_size:
            next.append(o2.copy())

    return next


# initialization
population_size = 3
k_way = 2
genes = []
num_gen = population_size
num_exp = 0
print('Maximization of function using GA[k-way,uniform crossover,bit flip mutation]\n\n')
# generating initial population
while True:
    if len(genes) == population_size:
        break
    gene = [random.randint(0, 1) for x in range(3)]
    if gene_value(gene) <= 6 and gene_value(gene) != 0:
        genes.append(gene.copy())

print('Initial population:')
for x in genes:
    print(x)

best_gene = [0, 0, 0]
# running GA till we get best chromosome
while True:
    for i in genes:
        if func_value(i) > func_value(best_gene):
            best_gene = i.copy()
    if gene_value(best_gene) == 6:
        break
    genes = next_gen(genes)
    print('\n\n\nCurrent population:')
    for x in genes:
        print(x)

print('The best chromosome is:', best_gene)
print('The maximum value is', func_value(best_gene))
print('number of nodes generated', num_gen)
print('number of nodes expanded', num_exp)
