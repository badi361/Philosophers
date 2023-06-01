#include "philo.h"

void	mutex_sleep(t_philo *philo)
{
	pthread_mutex_lock(philo->sleep_mutex);
	print_message(philo, "is sleeping\n");
	pthread_mutex_unlock(philo->sleep_mutex);
	usleep_fonc(philo->list->time_to_sleep);
}
