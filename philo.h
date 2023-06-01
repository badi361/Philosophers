#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>

typedef struct  s_list
{
    int               number_of_the_philosophers;
    int               time_to_die;
    int               time_to_eat;
    int               time_to_sleep;
	int				  must_eat_count;
    unsigned long     begin_time;
	pthread_mutex_t	  *forks;
    pthread_mutex_t   death_mutex;
    pthread_mutex_t   *all_eat_mutex;
    pthread_mutex_t   print_mutex;
    pthread_mutex_t   thinking_mutex;
    pthread_mutex_t   *all_sleep_mutex;
    int               death;
}   t_list;

typedef struct s_philo
{
    unsigned long       last_eat_time;
    int     			id;
    int     			eat_count;
	long long			begin_philo;
    pthread_mutex_t     *eat_mutex;
    pthread_mutex_t     *sleep_mutex;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		*left_fork;
    pthread_t           threads_philos;
    t_list              *list;

}   t_philo;

int             arg_control(char **av);
int	            ft_atoi(const char *str);
int             death_check(t_philo *philo);
unsigned long   get_time();
t_list  		*get_arg(int ac, char **av, t_list *list);
t_philo			*add_philosophers_detail(t_list *list);
void			get_forks(t_list *list, t_philo *philo);
void            *thread_begin(void *philo);
void            creat_thread(t_philo *philo);
void	        print_message(t_philo *philo, char *str);
void	        mutex_eat(t_philo *philo);
void	        usleep_fonc(int until);
void            mutex_sleep(t_philo *philo);
void	        mutex_think(t_philo *philo);
int		        is_it_finish(t_philo *philo);
int		        any_death(t_philo *philo);
void	        end_the_game(t_philo *philo);
void	        get_sleep_and_eat_mutex(t_philo *philo, t_list *list);

#endif