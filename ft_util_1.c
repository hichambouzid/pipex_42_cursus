/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_util_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibouzid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 21:39:15 by hibouzid          #+#    #+#             */
/*   Updated: 2024/03/16 22:03:29 by hibouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

int ft_strleen(char **ptr)
{
	int i;

	i = 0;
	while (ptr[i])
		i++;
	// printf("---> %d\n", i);
	return (i);
}

int ft_parce_cmd(char **cmd, char **env)
{
	if (ft_cmd_valid(env, cmd) >= 0)
		return (0);
	else
		return (-1);
}

char **ft_parce_env(char **env)
{
	int i;
	int index;
	char *tmp;
	char **tab;

	index = ft_index(env, "PATH=");
	if (index < 0)
		return (NULL);
	tab = ft_split(env[index] + 5, ':');
	i = 0;
	while (tab[i])
	{
		tmp = tab[i];
		tab[i] = ft_strjoin(tab[i], "/");
		free(tmp);
		i++;
	}
	return (tab);
}

int ft_index(char **envp, char *str)
{
	int i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], str, ft_strlen(str)))
			return (i);
		i++;
	}
	return (-1);
}

int ft_strncmp(char *s1, char *s2, int n)
{
	int i;

	i = 0;
	while ((s1[i] && s2[i]) && i < n)
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}
