/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouzaie <mbouzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 17:49:55 by mbouzaie          #+#    #+#             */
/*   Updated: 2022/02/02 16:42:49 by mbouzaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philosophers.h"
#include <stdio.h>

void	take_fork(t_philo *philo, int fork_id, int position)
{
	pthread_mutex_lock(&philo->args->forks[fork_id]);
	print_action(get_time(), philo, " has taken a fork\n");
	if (position == RIGHT)
		philo->fork_r = &philo->args->forks[fork_id];
	else
		philo->fork_l = &philo->args->forks[fork_id];
}

void	putdown_forks(t_philo *philo)
{
	if (philo->fork_r != NULL)
		pthread_mutex_unlock(philo->fork_r);
	if (philo->fork_l != NULL)
		pthread_mutex_unlock(philo->fork_l);
}

int	do_actions(t_philo *philo)
{
	if (check_death(philo->args))
		return (0);
	take_fork(philo, philo->id - 1, RIGHT);
	if (philo->id == philo->args->number)
		take_fork(philo, 0, LEFT);
	else
		take_fork(philo, philo->id, LEFT);
	print_action(get_time(), philo, " is eating\n");
	ft_usleep(philo->args->eat_t);
	pthread_mutex_lock(&philo->args->death_m);
	philo->last_eat_t = get_time() - philo->args->start_t;
	philo->eat_n++;
	pthread_mutex_unlock(&philo->args->death_m);
	putdown_forks(philo);
	if (check_death(philo->args))
		return (0);
	print_action(get_time(), philo, " is sleeping\n");
	ft_usleep(philo->args->sleep_t);
	if (check_death(philo->args))
		return (0);
	print_action(get_time(), philo, " is thinking\n");
	return (1);
}

void	handle_exit(t_args *args)
{
	int	i;

	i = 0;
	while (i < args->number)
	{
		pthread_join(args->philos[i].thread, NULL);
		i++;
	}
	i = 0;
	pthread_mutex_destroy(&args->death_m);
	pthread_mutex_destroy(&args->write_m);
	while (i < args->number)
	{
		pthread_mutex_destroy(&args->forks[i]);
		i++;
	}
	free(args->philos);
	free(args->forks);
}

int	main(int ac, char **av)
{
	t_args	*args;

	if (ac > 4 && ac < 7)
	{
		args = (t_args *)malloc(sizeof(t_args) + 1);
		args->number = ft_atoi(av[1]);
		args->die_t = ft_atoi(av[2]);
		args->eat_t = ft_atoi(av[3]);
		args->sleep_t = ft_atoi(av[4]);
		args->eat_n = 0;
		if (ac == 6)
			args->eat_n = ft_atoi(av[5]);
		if (init(args))
		{
			create_threads(args);
			observe(args);
			handle_exit(args);
		}
		free(args);
	}
	return (0);
}
