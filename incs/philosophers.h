/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouzaie <mbouzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 16:32:02 by mbouzaie          #+#    #+#             */
/*   Updated: 2021/12/21 13:41:22 by mbouzaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>

struct	s_args;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	pthread_mutex_t	fork;
	struct s_args	*args;

}	t_philo;

typedef struct s_args
{
	int				number;
	int				die_t;
	int				eat_t;
	int				sleep_t;
	int				eat_n;
	uint64_t		start_t;
	pthread_mutex_t	write_m;
	t_philo			**philos;
} t_args;

int	ft_atoi(const char *str);
void	print_action(int timestamp, int philo, char *action);

#endif