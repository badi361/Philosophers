/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleepandthink.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguzel <bguzel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 16:45:28 by bguzel            #+#    #+#             */
/*   Updated: 2023/06/18 16:45:29 by bguzel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	mutex_sleep(t_philo *philo)
{
	pthread_mutex_lock(philo->sleep_mutex);
	print_message(philo, "is sleeping\n");
	pthread_mutex_unlock(philo->sleep_mutex);
	usleep_fonc(philo->list->time_to_sleep);
}
