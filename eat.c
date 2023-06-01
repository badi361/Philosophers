#include "philo.h"

void	print_message(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->list->print_mutex);
	if (death_check(philo) == 1 && (philo->eat_count != philo->list->must_eat_count))
		printf("%lums %d %s", get_time() - philo->list->begin_time, philo->id + 1, str);
	pthread_mutex_unlock(&philo->list->print_mutex);
}

void	mutex_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_message(philo, "has taken a fork\n");
	if (philo->list->number_of_the_philosophers == 1)
	{
		pthread_mutex_unlock(philo->left_fork);
		philo->list->death = 42;
		return ;
	}
	pthread_mutex_lock(philo->right_fork);
	print_message(philo, "has taken a fork\n");
	pthread_mutex_lock(philo->eat_mutex);
	philo->last_eat_time = get_time();
	print_message(philo, "is eating\n");
	philo->eat_count++;
	pthread_mutex_unlock(philo->eat_mutex);
	usleep_fonc(philo->list->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

int		is_it_finish(t_philo *philo)
{
	int i;

	i = 0;
	if (philo->list->must_eat_count == -1)
		return (0);
	while (i < philo->list->number_of_the_philosophers)
	{
		pthread_mutex_lock(philo[i].eat_mutex);
		if (philo[i].eat_count < philo->list->must_eat_count)
		{
			pthread_mutex_unlock(philo[i].eat_mutex);
			return (0);
		}
		pthread_mutex_unlock(philo[i].eat_mutex);
		i++;
	}
	pthread_mutex_lock(&philo->list->death_mutex);
	philo->list->death = 42;
	pthread_mutex_unlock(&philo->list->death_mutex);
	return (1);
}

int		any_death(t_philo *philo)
{
	int i;

	i = 0;
	while (i < philo->list->number_of_the_philosophers)
	{
		pthread_mutex_lock(philo[i].eat_mutex);
		if ((int)(get_time() - philo[i].last_eat_time) >= philo->list->time_to_die)
		{
			pthread_mutex_lock(&philo->list->death_mutex);
			philo->list->death = 42;
			pthread_mutex_unlock(&philo->list->death_mutex);
			pthread_mutex_unlock(philo[i].eat_mutex);
			printf("%lums %d %s", get_time() - philo->list->begin_time, philo[i].id + 1, "dead\n");
			return (1);
		}
		pthread_mutex_unlock(philo[i].eat_mutex);
		i++;
	}
	return (0);
}