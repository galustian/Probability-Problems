import numpy as np

n_simulations = 1000

# Parameters
total_money = 100
gamblers_money_param = 49
gamblers_chance = 0.495

if __name__ == '__main__':
    ntimes_gambler_bankrupt = 0
    gamblers_money = gamblers_money_param
    
    for i in range(n_simulations):
        
        while gamblers_money != 0 and gamblers_money != total_money:
            game_won = np.random.binomial(1, gamblers_chance)
            if game_won == 1:
                gamblers_money += 1
            else:
                gamblers_money -= 1
        if gamblers_money == 0:
            ntimes_gambler_bankrupt += 1

        # Reset Money
        gamblers_money = gamblers_money_param

    expected_bankrupcy = ntimes_gambler_bankrupt / n_simulations
    
    print("Expected Bankrupcy of Gambler:", expected_bankrupcy)