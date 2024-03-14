/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_util_bonus_0.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibouzid <hibouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 17:01:59 by hibouzid          #+#    #+#             */
/*   Updated: 2024/03/09 23:21:12 by hibouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

int	**ft_pipes(int ac)
{
	int	**tab;
	int	len;
	int	i;

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

void	ft_close(int **tabfd, int fd1, int fd2)
{
	int	i;
	int	j;

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

void	ft_dup(int in, int out, int **tab)
{
	if (dup2(in, 0) == -1 || dup2(out, 1) == -1)
	{
		perror("ERROR IN DUP\n");
		exit(-1);
	}
	ft_close(tab, in, out);
}
