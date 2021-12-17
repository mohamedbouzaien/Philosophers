/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouzaie <mbouzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 17:49:55 by mbouzaie          #+#    #+#             */
/*   Updated: 2021/12/17 20:14:38 by mbouzaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philosophers.h"
#include <stdio.h>

int	main(int ac, char **av)
{
	t_rules	rules;

	if (ac > 4)
	{
		rules.number = ft_atoi(av[1]);
		rules.die_t = ft_atoi(av[2]);
		rules.eat_t = ft_atoi(av[3]);
		rules.sleep_t = ft_atoi(av[4]);
		if (ac == 6)
			rules.eat_n = ft_atoi(av[5]);
	}
	print_action(300, 1, " has taken a fork\n");
}