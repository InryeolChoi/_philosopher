# _philosophers

한국어 버전은 다음 링크를 참조해주세요 : [link](./README_ko.md)
Please refer to this page if you can read English

## Project Overview
> Implementation of the "Dining Philosopher Problem".

* philo_basic: Each philosopher is treated as a thread, using mutexes to solve concurrency issues in a multithreaded environment.
* philo_bonus: Each philosopher is treated as a process, using semaphores to solve concurrency issues in a multiprocess environment.

### Language
* Written in C.
* The following functions were used to create the files:
```{bash}
memset, printf, malloc, free, write,
usleep, gettimeofday, pthread_create,
pthread_detach, pthread_join, pthread_mutex_init,
pthread_mutex_destroy, pthread_mutex_lock,
pthread_mutex_unlock
```

## Features
* Philosophers can perform only one activity at a time.
* Philosophers repeatedly engage in three activities: eating, thinking, and sleeping.
* Each philosopher has one fork to their right and left.
* Philosophers must use both forks to eat.
* It's essential to manage philosophers so they don't starve to death.

## Key Concepts
* Multithreading: [Link](https://en.wikipedia.org/wiki/Multithreading_(computer_architecture))
* Multiprocessing: [Link](https://en.wikipedia.org/wiki/Multiprocessing)
* Concurrency: [Link](https://en.wikipedia.org/wiki/Concurrency_(computer_science))
* Mutexes & Semaphores: [Link](https://en.wikipedia.org/wiki/Lock_(computer_science)#Mutexes_vs._semaphores)

## How to Run
1. Compile: Use the Makefile to compile the program.
2. philo_basic : `./philo (number of philosophers) (survival time) (eating time) (sleeping time) (number of times to eat)`
3. philo_bonus : `./philo_bonus (number of philosophers) (survival time) (eating time) (sleeping time) (number of times to eat)`

### tips
* If `(eating time) + (sleeping time)` is longer than `(survival time)`, a philosopher will die.
* `(number of times to eat)` is optional.
* Both `philo_basic` and `philo_bonus` are executed in the same way.

```{bash}
# Checking death within a certain time
./philo 4 60 200 200

# Situations where a philosopher will definitely die
./philo 1 800 200 200
./philo 5 410 200 200
./philo 4 310 200 100

# Situations where philosophers live forever
./philo 4 410 200 200
./philo 5 610 200 200
./philo 5 800 200 200

# Infinite life situations (hard mode)
./philo 199 610 200 200 
./philo 200 410 200 200
```

## File Structure
### philo_basic
* philo_main.c: Contains the program's main function.
* philo_info.h: Includes structure definitions and header files.
* philo_input.c: Contains functions related to input parameter processing.
* philo_exe.c: Contains main functions simulating the philosopher's actions.
* philo_check.c: Contains functions to check the state of the philosophers.
* util_func.c, util_other.c: Includes utility functions.
### philo_bonus
* philo_bonus_main.c: Contains the program's main function.
* philo_bonus_info.h: Includes structure and semaphore-related header files.
* philo_bonus_exe.c, philo_bonus_child.c: Contains main functions simulating the philosopher's actions.
* philo_bonus_func.c: Includes helpful features.
* philo_bonus_util.c, philo_bonus_libft.c: Includes utility functions.