import numpy as np
from scipy import stats

n_simulations = 10000000
win = 0
win_list = []

for i in range(n_simulations):
    coin = 1
    n_consequtive_heads = 0
    
    while coin == 1:
        coin = np.random.binomial(1, 0.5)
        if coin == 1:
            n_consequtive_heads += 1
    
    if n_consequtive_heads != 0:
        new_win = 2 ** n_consequtive_heads
        win += new_win
        win_list.append(new_win)
    else:
        win_list.append(0)


win_list = np.array(win_list, dtype=np.int32)
print("Expected Winnings:", win / n_simulations)
# Of course the median is 0 or 2 (smth. else is very unlikely)
print("Median Winnings:", np.median(win_list), "\n")

mode_stat = stats.mode(win_list)
print("Mode Winnings:", mode_stat[0])
print("Mode Num. Occurences:", mode_stat[1], "\n")

bins = np.bincount(win_list)
unique = np.unique(win_list)

for u in unique:
    print("Won {}$ {} times".format(u, bins[u]))