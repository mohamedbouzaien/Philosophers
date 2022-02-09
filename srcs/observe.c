/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouzaie <mbouzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 17:58:34 by mbouzaie          #+#    #+#             */
/*   Updated: 2022/02/09 14:50:40 by mbouzaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philosophers.h"

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

static void	observe_eating(t_args *args)
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
			usleep(100);
			i++;
		}
		if (n / args->number == args->eat_n && n % args->number == 0)
		{
			pthread_mutex_lock(&args->death_m);
			pthread_mutex_lock(&(args->write_m));
			args->finish = 1;
			pthread_mutex_unlock(&(args->write_m));
			pthread_mutex_unlock(&args->death_m);
		}
	}
}

void	observe(t_args *args)
{
	int	i;

	while (!args->finish && args->number)
	{
		i = 0;
		while (i < args->number && !args->finish)
		{
			pthread_mutex_lock(&args->death_m);
			if (get_time() - args->start_t - args->philos[i].last_eat_t > \
				(uint64_t)args->die_t)
			{
				pthread_mutex_lock(&(args->write_m));
				args->finish = 1;
				pthread_mutex_unlock(&(args->write_m));
				print_action(get_time(), &args->philos[i], " died\n");
			}
			pthread_mutex_unlock(&args->death_m);
			i++;
		}
		observe_eating(args);
	}
}
