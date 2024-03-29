## Philosophers

The goal of this project is to solve the dining philosoperhs problem, implementing a multithreding solution:

N philosophers are sitting at a round table and eating. A fork is placed between every 2 philosophers, and each one of them repeats the actions `eating ➔ sleeping ➔ thinking`.



### Usage

```shell
./philo <N> <time_die> <time_eat> <time_sleep> [<nb_meals>]
```

 KEY           | Parameter      |
| :-------------: |:-------------:|
| `N`           |number of philos / number of forks     |
| `time_die`           | time that a philo can spend withou eating |
| `time_eat`           | time of a meal  |
| `time_sleep`           | time of a nap |
| `nb_meals`           | number of times every philo has to eat so that the simulation stops |

If nb_meals is not specified, the simuation stops when a philo dies.

### Rules

- Philos eat, sleep or think alternatively. Meaning that they can't do two actions at the same time.
- There are many forks as philos
- Eating takes two forks (left and right fork of each philo)
- When the meal ends, the philo puts both forks in the table and starts sleeping
- Philos need to eat and should never starve
- 

### References
- https://github.com/nafuka11/philosophers-visualizer
