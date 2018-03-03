import numpy as np
import sys

def simulate(people, n_same_bd):    
    sample_people = np.random.randint(1, 366, size=(int(people)))

    ''' CUSTOM ALGORITHM

    for X in range(len(sample_people)):
        occurences = 0
        for x in range(len(sample_people)):
            if sample_people[x] == sample_people[X] and x != X:
                occurences += 1

            if occurences == n_same_bd-1:
                return 1
    return 0
    '''

    if np.max(np.bincount(sample_people)) >= n_same_bd:
        return 1
    return 0


if __name__ == '__main__':
    people, n_same_bd = sys.argv[1:]
    n_rounds = 50000

    simulation_match = 0
    
    for i in range(n_rounds):
        simulation_match += simulate(people, int(n_same_bd))
    
    probability = simulation_match / n_rounds

    print("{} People in a group. Probability of at least {} people with same birthday: {}".format(people, n_same_bd, probability))
