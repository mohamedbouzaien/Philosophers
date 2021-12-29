/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouzaie <mbouzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 17:49:55 by mbouzaie          #+#    #+#             */
/*   Updated: 2021/12/29 17:04:47 by mbouzaie         ###   ########.fr       */
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

void	ft_usleep(uint64_t time)
{
	uint64_t	start;

	start = get_time();
	while (get_time() - start < time)
		usleep(time / 10);
}

int	check_death(t_args *args)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(&args->death_m);
	if (args->finish)
		ret = 1;
	pthread_mutex_unlock(&args->death_m);
	return (ret);
}

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
	pthread_mutex_unlock(philo->fork_r);
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

void	*life_cycle(void *arg)
{
	t_philo	*philo;
	int ret_actions;
	int	ret_death;

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

void	observe_eating(t_args *args)
{
	int	i;
	int	n;

	if (args->eat_n != 0)
	{
		i = 0;
		n = 0;
		while (i < args->number && !args->finish)
		{
			pthread_mutex_lock(&args->death_m);
			n += args->philos[i].eat_n;
			pthread_mutex_unlock(&args->death_m);
			i++;
		}
		if (n / args->number == args->eat_n && n % args->number == 0)
		{
			pthread_mutex_lock(&args->death_m);
			args->finish = 1;
			pthread_mutex_unlock(&args->death_m);
		}
	}
}

void	observe(t_args *args)
{
	int	i;

	while (!args->finish)
	{
		i = 0;
		while (i < args->number && !args->finish)
		{
			pthread_mutex_lock(&args->death_m);
			if (get_time() - args->start_t - args->philos[i].last_eat_t > \
				(uint64_t)args->die_t)
			{
				args->finish = 1;
				print_action(get_time(), &args->philos[i], " died\n");
			}
			pthread_mutex_unlock(&args->death_m);
			i++;
		}
		observe_eating(args);
	}
}

int	create_threads(t_args *args)
{
	int	i;

	i = 0;
	printf("here\n");
	while (i < args->number)
	{
		if (pthread_create(&(args->philos[i].thread), NULL, life_cycle, &(args->philos[i])) != 0)
			return (0);
		i += 2;
	}
	i = 1;
	while (i < args->number)
	{
		if (pthread_create(&(args->philos[i].thread), NULL, life_cycle, &(args->philos[i])) != 0)
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

void	handle_exit(t_args *args)
{
	int		i;
	
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