/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouzaie <mbouzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 18:06:50 by mbouzaie          #+#    #+#             */
/*   Updated: 2021/12/17 20:14:20 by mbouzaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../incs/philosophers.h"

int	ft_isspace(int c)
{
	return (c == ' ' || c == '\t' || c == '\r' || c == '\v' || c == '\f' \
			|| c == '\n');
}

int	ft_atoi(const char *str)
{
	int					sign;
	unsigned long int	result;

	sign = 1;
	result = 0;
	while (ft_isspace(*str))
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	while ((*str != '\0') && (*str >= '0') && (*str <= '9'))
	{
		if ((result > 922337203685477580 || (result == 922337203685477580 \
				&& (*str - '0') > 7)) && sign == 1)
			return (-1);
		else if ((result > 922337203685477580 || \
			(result == 922337203685477580 && (*str - '0') > 8)) && sign == -1)
			return (0);
		result = (result * 10) + (*str - '0');
		str++;
	}
	return ((int)(result * sign));
}

void	ft_putchar_fd(char c, int fd)
{
	if (fd < 0)
		return ;
	write(fd, &c, 1);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_putstr_fd(char *str, int fd)
{
	int	i;

	i = ft_strlen(str);
	write(fd, str, i);
}

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

void	print_action(int timestamp, int philo, char *action)
{
	ft_putnbr_fd(timestamp, 1);
	ft_putchar_fd(' ', 1);
	ft_putnbr_fd(philo, 1);
	ft_putstr_fd(action, 1);
}
