#include "philo.h"

t_philo	*add_philosophers_detail(t_list *list)
{
	t_philo *philo;
	int i;

    i = 0;
	philo = malloc(sizeof(t_philo) * list->number_of_the_philosophers);
	while (i < list->number_of_the_philosophers)
	{
		philo[i].id = i;
		philo[i].eat_count = 0;
		philo[i].list = list;
		philo[i].begin_philo = get_time() - list->begin_time;
		i++;
	}
    philo->list->death = 1;
	return (philo);
}

int     death_check(t_philo *philo)
{
    pthread_mutex_lock(&philo->list->death_mutex);
    if (philo->list->death == 1)
    {
        pthread_mutex_unlock(&philo->list->death_mutex);
        return (1);
    }
    pthread_mutex_unlock(&philo->list->death_mutex);
    return (0);
}
void    *thread_begin(void *philo) //creat fonksiyınu parametre olarak * döndürmemi istiyor
{
    t_philo *temp;
    int value;
    temp = philo;
    if (temp->id % 2 == 1)
        usleep(1000);
    while (1)
    {
        value = death_check(temp);
        if (value != 1)
            break ;
        mutex_eat(temp);
        mutex_sleep(temp);
	    print_message(temp, "is thinking\n");
    }
    return (NULL);
}
void    creat_thread(t_philo *philo)
{
    int i;

    i = 0;
    while (i < philo->list->number_of_the_philosophers)
    {
        philo[i].last_eat_time = get_time();
        pthread_create(&philo[i].threads_philos, NULL, thread_begin, &philo[i]);
        i++;
    }
    while (1)
    {
        if (is_it_finish(philo) == 1)
            break;
        if (any_death(philo) == 1)
            break;
    }
}
int main(int ac, char **av)
{
    t_list      *list;
    t_philo     *philo;
    list = malloc(sizeof(t_list));
    int k;
    k = 1;
    if (arg_control(av) == 1 || ac > 6)
    {
        write(2, "Wrong Argument\n", 15);
        return (0);
    }
    while (av[k])
    {
        if (ft_atoi(av[k]) == -1)
            return (0);
        k++;
	}
    list = get_arg(ac, av, list);
    list->begin_time = get_time();
	philo = add_philosophers_detail(list);
	get_forks(list, philo);
    get_sleep_and_eat_mutex(philo, list);
    creat_thread(philo);
    k = 0;
    while (k < philo->list->number_of_the_philosophers)
    {
        pthread_join(philo[k].threads_philos, NULL);
        k++;
    }
    end_the_game(philo);
}
//Genel olarak, -> operatörü, bir işaretçi üzerinden bir üyeye erişmek için kullanılırken, . operatörü doğrudan bir yapının üyesine erişmek için kullanılır.