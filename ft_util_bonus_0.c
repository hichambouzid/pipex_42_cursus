/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*
								 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibouzid <hibouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 21:32:59 by hibouzid          #+#    #+#             */
/*   Updated: 2024/03/08 15:55:05 by hibouzid         ###   ########.fr       */
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

void ft_close(int **tabfd, int fd1, int fd2)
{
	int i;
	int j;

	i = 0;
	while (tabfd[i])
	{
		j = 0;
		while (j < 2)
		{
			if (tabfd[i][j] != fd1 && tabfd[i][j] != fd2)
				close(tabfd[i][j]);
			j++;
		}
		i++;
	}
}
