/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_util_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibouzid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:23:26 by hibouzid          #+#    #+#             */
/*   Updated: 2024/02/26 18:55:22 by hibouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

void	ft_putstr_fd(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
}

int ft_parce_cmd(char **cmd1, char **cmd2, char **env)
{
	if (!ft_cmd_valid_exist(env, cmd1) && !ft_cmd_valid_exist(env, cmd2))
		return (0);
	else
	{
		ft_free(ft_strleen(cmd1), cmd1);
		ft_free(ft_strleen(cmd2), cmd2);
		ft_free(ft_strleen(env), env);
		return (-1);
	}
}

int ft_strleen(char **ptr)
{
	int i;

	i = 0;
	while (ptr[i])
	i++;
	return (i);
}

int ft_cmd_valid_exist(char **ptr, char **cmd)
{
	int		i;
	char	*str;

	i = 0;

	while (ptr[i])
	{
		str = ft_strjoin(ptr[i], cmd[i]);
		if (!access(str, X_OK | F_OK))
		{
			free(str);
			return (0);
		}
		i++;
	}
	free(str);
	return (-1);
}

