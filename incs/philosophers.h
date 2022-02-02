/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouzaie <mbouzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 16:32:02 by mbouzaie          #+#    #+#             */
/*   Updated: 2022/02/02 16:45:38 by mbouzaie         ###   ########.fr       */
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
}	t_args;

int			ft_atoi(const char *str);
int			ft_strlen(const char *str);
int			check_death(t_args *args);
int			init(t_args *args);
int			do_actions(t_philo *philo);
int			create_threads(t_args *args);
void		ft_usleep(uint64_t time);
void		*life_cycle(void *arg);
void		observe(t_args *args);
void		ft_putstr_fd(char *str, int fd);
void		ft_putchar_fd(char c, int fd);
void		putdown_forks(t_philo *philo);
void		print_action(uint64_t timestamp, t_philo *philo, char *action);
uint64_t	get_time(void);

#endif