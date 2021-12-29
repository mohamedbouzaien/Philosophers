/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouzaie <mbouzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 16:32:02 by mbouzaie          #+#    #+#             */
/*   Updated: 2021/12/29 00:37:35 by mbouzaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>

# define RIGHT	0
# define LEFT	1

struct	s_args;

typedef struct s_philo
{
	int				id;
	int				eat_n;
	uint64_t		last_eat_t;
	pthread_t		thread;
	pthread_mutex_t	*fork_r;
	pthread_mutex_t	*fork_l;
	struct s_args	*args;

}	t_philo;

typedef struct s_args
{
	int				number;
	int				die_t;
	int				eat_t;
	int				sleep_t;
	int				eat_n;
	int				finish;
	uint64_t		start_t;
	pthread_mutex_t	write_m;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	death_m;
} t_args;

int		ft_atoi(const char *str);
void	print_action(uint64_t timestamp, t_philo *philo, char *action);

#endif