#include "philo.h"

int	ft_atoi(const char *str)
{
	unsigned int	i;
	long			l;
	int				k;

	i = 0;
	k = 1;
	l = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			k = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		l = (l * 10) + (str[i] - 48) * k;
		if (l > 2147483647)
			return (-1);
		if (l < -2147483648)
			return (-1);
		i++;
	}
	return (l);
}

void	usleep_fonc(int until)
{
	unsigned long	localtime;

	localtime = get_time();
	while ((get_time() - localtime) < (unsigned long)until)
		usleep(100);
}

void	end_the_game(t_philo *philo)
{
	int i;

	i = 0;
	while (i < philo->list->number_of_the_philosophers)
	{
		pthread_mutex_destroy(&philo->list->forks[i]);
		pthread_mutex_destroy(&philo->list->all_sleep_mutex[i]);
		pthread_mutex_destroy(&philo->list->all_eat_mutex[i]);
		i++;
	}
	pthread_mutex_destroy(&philo->list->death_mutex);
    pthread_mutex_destroy(&philo->list->print_mutex);
	free(philo->list->all_eat_mutex);
	free(philo->list->all_sleep_mutex);
	free(philo->list->forks);
	free(philo);
}
