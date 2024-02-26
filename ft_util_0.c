/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_util_0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibouzid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 13:08:54 by hibouzid          #+#    #+#             */
/*   Updated: 2024/02/25 15:36:16 by hibouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

int ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

int ft_index(char **envp, char *str)
{
	int i;

	i = 0;
	while (envp[i])
	{
		if (ft_strcmp(envp[i], "PATH") == 0)
			return (i);
		i++;
	}
	return (-1);
}

char **ft_parce_env(char **envp)
{
	int i;
	int index;
	char **tab;

	index = ft_index(envp, "PATH");
	i = 0;
	if (index == -1)
		return (NULL);
	while (envp[index][i])
	{
		if (is_separator(envp[index][i], '/'))
			break;
		i++;
	}
	tab = ft_split(envp[index] + i, ':');
	return (tab);
}