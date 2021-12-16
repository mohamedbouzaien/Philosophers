/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouzaie <mbouzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 21:40:19 by mbouzaie          #+#    #+#             */
/*   Updated: 2021/12/03 22:03:13 by mbouzaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct s_p
{
	int             i;
	pthread_mutex_t mutex;
}               t_p;

int     ft_strlen(char *str)
{
	int     i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	*go1(void *pp)
{
	char *str;
	int		i = 0;
	t_p		*ppp;

	ppp = (t_p *)pp;

	str = "thread 1: coucou ça va? \n";
	pthread_mutex_lock(&ppp->mutex);
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
	pthread_mutex_unlock(&ppp->mutex);
	return (NULL);
}

int		main()
{
	pthread_t	thread_id1;
	pthread_t	thread_id2;
	t_p			p;
	t_p			*pp;

	pp = malloc(sizeof(t_p) * 1);
	pp = &p;
	p.i = 3;
	pthread_mutex_init(&p.mutex, NULL);			// obligatoire de init le mutex
    pthread_create(&thread_id1, NULL, go1, (void *)pp);
    pthread_create(&thread_id2, NULL, go1, (void *)pp);
	sleep(1);
}