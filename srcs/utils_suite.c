/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_suite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouzaie <mbouzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 17:55:59 by mbouzaie          #+#    #+#             */
/*   Updated: 2022/02/02 17:05:17 by mbouzaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philosophers.h"

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
		ft_putstr_fd("-2147483648", fd);
	else if (n < 0)
	{
		ft_putchar_fd('-', fd);
		ft_putnbr_fd(-n, fd);
	}
	else if (n >= 10)
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putchar_fd((n % 10) + 48, fd);
	}
	else
		ft_putchar_fd(n + 48, fd);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;
	size_t	n;

	i = 0;
	n = ft_strlen(s1);
	while (s1[i] && s1[i] == s2[i] && i < n)
		i++;
	if (i == n || n == 0)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	print_action(uint64_t timestamp, t_philo *philo, char *action)
{
	pthread_mutex_lock(&(philo->args->write_m));
	if (philo->args->finish != 1 || !ft_strcmp(action, " died\n"))
	{
		ft_putnbr_fd(timestamp - philo->args->start_t, 1);
		ft_putchar_fd(' ', 1);
		ft_putnbr_fd(philo->id, 1);
		ft_putstr_fd(action, 1);
		if (!ft_strcmp(action, " died\n") && philo->args->number == 1)
			pthread_mutex_unlock(&philo->args->forks[0]);
	}
	pthread_mutex_unlock(&(philo->args->write_m));
}

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
