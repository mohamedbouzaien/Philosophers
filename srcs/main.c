/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouzaie <mbouzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 17:49:55 by mbouzaie          #+#    #+#             */
/*   Updated: 2021/12/21 13:57:47 by mbouzaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philosophers.h"
#include <stdio.h>

uint64_t	get_time(void)
{
	static struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * (uint64_t)1000) + (time.tv_usec / 1000));
}

void	do_actions(t_philo *philo)
{
	pthread_mutex_lock(&(philo->args->write_m));
	print_action(get_time() - philo->args->start_t, philo->id, " is sleeping\n");
	pthread_mutex_unlock(&(philo->args->write_m));
	usleep(philo->args->sleep_t * 1000);
	pthread_mutex_lock(&(philo->args->write_m));
	print_action(get_time() - philo->args->start_t, philo->id, " is thinking\n");
	pthread_mutex_unlock(&(philo->args->write_m));
}

void	*life_cycle(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		do_actions(philo);
	}
	return (NULL);
}

int	init(t_args *args)
{
	int	i;

	pthread_mutex_init(&(args->write_m), NULL);
	args->philos = (t_philo **)malloc(sizeof(t_philo *) * (args->number + 1));
	args->start_t = get_time();
	i = 0;
	while (i < args->number)
	{
		args->philos[i] = (t_philo *)malloc(sizeof(t_philo) + 1);
		args->philos[i]->id = i + 1;
		args->philos[i]->args = args;
		i++;
	}
	i = 0;
	while (i < args->number)
	{
		if (pthread_create(&(args->philos[i]->thread), NULL, life_cycle, args->philos[i]) != 0)
			return (1);
		usleep(100);
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_args	*args;

	args = (t_args *)malloc(sizeof(t_args) + 1);
	if (ac > 4)
	{
		args->number = ft_atoi(av[1]);
		args->die_t = ft_atoi(av[2]);
		args->eat_t = ft_atoi(av[3]);
		args->sleep_t = ft_atoi(av[4]);
		if (ac == 6)
			args->eat_n = ft_atoi(av[5]);
		return (init(args));
	}
	return (0);
}