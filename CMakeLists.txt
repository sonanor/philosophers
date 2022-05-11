cmake_minimum_required(VERSION 3.21)
project(philo C)

set(CMAKE_C_STANDARD 11)

add_executable(philo
        philo/philo.c philo/philo.h philo/threads.c philo/utils.c philo/mutexes.c philo/actions.c philo/input.c philo/helpers.c)
