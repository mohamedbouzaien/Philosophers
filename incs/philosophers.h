/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouzaie <mbouzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 16:32:02 by mbouzaie          #+#    #+#             */
/*   Updated: 2021/12/17 20:11:14 by mbouzaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>

typedef struct s_rules
{
	int		number;
	int		die_t;
	int		eat_t;
	int		sleep_t;
	int		eat_n;
} t_rules;

int	ft_atoi(const char *str);
void	print_action(int timestamp, int philo, char *action);

#endif