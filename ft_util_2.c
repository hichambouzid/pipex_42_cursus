/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_util_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibouzid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 00:31:07 by hibouzid          #+#    #+#             */
/*   Updated: 2024/03/16 21:55:19 by hibouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

int ft_cmd_valid(char **env, char **cmd)
{
	int i;
	char *tmp;

	i = 0;
	if (!ft_strncmp(cmd[i], ".", 1) || !ft_strncmp(cmd[i], "./", 2))
		return (-1);
	if (!ft_strncmp(cmd[i], "/", 1) && access(cmd[0], X_OK | F_OK))
		return (-1);
	if (!access(cmd[0], F_OK | X_OK))
		return (1);
	while (env[i])
	{
		if (env)
			tmp = ft_strjoin(env[i], cmd[0]);
			
		if (tmp && !access(tmp, X_OK | F_OK))
		{
			free(tmp);
			return (0);
		}
		if (!access(cmd[0], X_OK | F_OK))
		{
			free(tmp);
			return (1);
		}
		free(tmp);
		i++;
	}
	return (-1);
}

char *ft_freee(char *str, char *ptr)
{
	if (*str == 0)
	{
		free(str);
		free(ptr);
		return (NULL);
	}
	return (str);
}

char ***fill_tab_cmd(int len, char ***tab_cmd, char **av)
{
	int i;

	i = 0;
	while (i < len)
	{
		tab_cmd[i] = ft_split(av[i], ' ');
		i++;
	}
	return (tab_cmd);
}

void ft_first_check(char *av1, char *av2)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (av1[i])
	{
		if (av1[i] && av1[i] != ' ' && av1[i] != '\t')
			break;
		i++;
	}
	while (av2[j])
	{
		if (av2[j] && av2[j] != ' ' && av2[j] != '\t')
			break;
		j++;
	}
	if (ft_strlen(av2) == j || ft_strlen(av1) == i)
	{
		ft_putstr_fd("Command not found\n", 2);
		exit(-1);
	}
}
