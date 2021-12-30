/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouzaie <mbouzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 17:58:30 by mbouzaie          #+#    #+#             */
/*   Updated: 2021/12/30 18:20:28 by mbouzaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philosophers.h"

void	*life_cycle(void *arg)
{
	int		ret_actions;
	int		ret_death;
	t_philo	*philo;

	philo = (t_philo *)arg;
	ret_actions = 1;
	ret_death = 0;
	while (ret_actions && !ret_death)
	{
		ret_actions = do_actions(philo);
		ret_death = check_death(philo->args);
	}
	return (NULL);
}

int	create_threads(t_args *args)
{
	int	i;

	i = 0;
	while (i < args->number)
	{
		if (pthread_create(&(args->philos[i].thread), NULL, life_cycle, \
			&(args->philos[i])) != 0)
			return (0);
		i += 2;
	}
	i = 1;
	while (i < args->number)
	{
		if (pthread_create(&(args->philos[i].thread), NULL, life_cycle, \
			&(args->philos[i])) != 0)
			return (0);
		i += 2;
	}
	return (1);
}

int	init(t_args *args)
{
	int	i;

	pthread_mutex_init(&(args->write_m), NULL);
	pthread_mutex_init(&args->death_m, NULL);
	args->philos = (t_philo *)malloc(sizeof(t_philo) * (args->number + 1));
	args->start_t = get_time();
	args->finish = 0;
	i = 0;
	while (i < args->number)
	{
		args->philos[i].eat_n = 0;
		args->philos[i].id = i + 1;
		args->philos[i].args = args;
		i++;
	}
	args->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * \
					(args->number + 1));
	i = 0;
	while (i < args->number)
	{
		pthread_mutex_init(&(args->forks[i]), NULL);
		i++;
	}
	return (1);
}
