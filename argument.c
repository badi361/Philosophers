/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguzel <bguzel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 16:18:00 by bguzel            #+#    #+#             */
/*   Updated: 2023/06/18 16:48:40 by bguzel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	get_forks(t_list *list, t_philo *philo)
{
	int	i;

	i = 0;
	list->forks = malloc(sizeof(pthread_mutex_t)
			* list->number_of_the_philosophers);
	while (i < list->number_of_the_philosophers)
	{
		philo[i].right_fork = &list->forks[i];
		if (i == 0)
			philo[i].left_fork = &list->forks[list->number_of_the_philosophers
				- 1];
		else
			philo[i].left_fork = &list->forks[i - 1];
		pthread_mutex_init(&list->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&list->death_mutex, NULL);
}

int	arg_control(char **av)
{
	int	i;
	int	k;

	k = 1;
	while (av[k])
	{
		i = 0;
		while (av[k][i])
		{
			if (av[k][i] >= '0' && av[k][i] <= '9')
				i++;
			else
				return (1);
		}
		k++;
	}
	return (0);
}

t_list	*get_arg(int ac, char **av, t_list *list)
{
	list->number_of_the_philosophers = ft_atoi(av[1]);
	list->time_to_die = ft_atoi(av[2]);
	list->time_to_eat = ft_atoi(av[3]);
	list->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		list->must_eat_count = ft_atoi(av[5]);
	else
		list->must_eat_count = -1;
	return (list);
}

unsigned long	get_time(void)
{
	unsigned long	result;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	result = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (result);
}

void	get_sleep_and_eat_mutex(t_philo *philo, t_list *list)
{
	int	i;

	i = 0;
	list->all_sleep_mutex = malloc(sizeof(pthread_mutex_t)
			* list->number_of_the_philosophers);
	list->all_eat_mutex = malloc(sizeof(pthread_mutex_t)
			* list->number_of_the_philosophers);
	list->all_print_mutex = malloc(sizeof(pthread_mutex_t)
			* list->number_of_the_philosophers);
	while (i < list->number_of_the_philosophers)
	{
		philo[i].sleep_mutex = &list->all_sleep_mutex[i];
		philo[i].eat_mutex = &list->all_eat_mutex[i];
		philo[i].print_mutex = &list->all_print_mutex[i];
		pthread_mutex_init(&list->all_sleep_mutex[i], NULL);
		pthread_mutex_init(&list->all_eat_mutex[i], NULL);
		pthread_mutex_init(&list->all_print_mutex[i], NULL);
		i++;
	}
}
