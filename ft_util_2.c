/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_util_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibouzid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 00:31:07 by hibouzid          #+#    #+#             */
/*   Updated: 2024/03/14 18:26:36 by hibouzid         ###   ########.fr       */
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
	while (env[i])
	{
		tmp = ft_strjoin(env[i], cmd[0]);
		if (!access(tmp, X_OK | F_OK))
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
