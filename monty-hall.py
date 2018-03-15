import numpy as np

# Parameters
n_simulations = 100000

n_doors = 3
n_open_doors = 1

if n_open_doors+1 >= n_doors:
    raise ValueError("n_doors has to be greater than open_doors+1")

for strategy in ['stay', 'switch']:
    won_car = 0
    for i in range(n_simulations):
        car_door_i = np.random.randint(0, n_doors)
        choosen_door_i = np.random.randint(0, n_doors)
        
        if strategy == 'stay':
            if choosen_door_i == car_door_i:
                won_car += 1
        else:
            cant_choose_doors = [car_door_i]
            if choosen_door_i != car_door_i: cant_choose_doors.append(choosen_door_i)
            
            closed_dors_i = np.delete(np.arange(n_doors), cant_choose_doors)
            
            monty_open_doors = np.random.choice(closed_dors_i, n_open_doors, replace=False)
            
            closed_dors_i = np.delete(np.arange(n_doors), monty_open_doors)
            chosen_i = np.where(closed_dors_i==choosen_door_i)[0][0]
            closed_dors_i = np.delete(closed_dors_i, chosen_i)
            
            switched_door_i = np.random.choice(closed_dors_i, 1)[0]
            
            if switched_door_i == car_door_i:
                won_car += 1
        

    expected_car_winning = won_car / n_simulations
    print("Expected car winning with", strategy, "strategy:", expected_car_winning)

print("\nYou see... Switching is always better. This can be proven either by thinking logically, simulation or LOTP (law of total probability) with extra conditioning.")
