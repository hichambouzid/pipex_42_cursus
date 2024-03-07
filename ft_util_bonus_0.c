/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_util_bonus_0.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibouzid <hibouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 21:32:59 by hibouzid          #+#    #+#             */
/*   Updated: 2024/03/07 18:02:20 by hibouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

int **ft_pipes(int ac)
{
	int **tab;
	int len;
	int i;

	len = ac - 4;
	tab = malloc(sizeof(int *) * (len + 1));
	if (!tab)
	{
		ft_putstr_fd("ERROR\n", 2);
		exit(-1);
	}
	tab[len] = 0;
	i = 0;
	while (i < len)
	{
		tab[i] = malloc(sizeof(int) * 2);
		if (pipe(tab[i]) < 0)
			{
				ft_putstr_fd("ERROR\n", 2);
				exit(-1);
			}
		i++;
	}
	return (tab);
}
