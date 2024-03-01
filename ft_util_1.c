/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_util_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibouzid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:23:26 by hibouzid          #+#    #+#             */
/*   Updated: 2024/02/29 16:43:40 by hibouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

int	ft_putstr_fd(char *s, int fd)
{
	return (write(fd, s, ft_strlen(s)));
}

int	ft_parce_cmd(char **cmd1, char **cmd2, char **env)
{
	if (ft_cmd_valid_exist(env, cmd1) >= 0 && ft_cmd_valid_exist(env,
			cmd2) >= 0)
		return (0);
	else
	{
		ft_free(ft_strleen(cmd1), cmd1);
		ft_free(ft_strleen(cmd2), cmd2);
		ft_free(ft_strleen(env), env);
		return (-1);
	}
}

int	ft_strleen(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
		i++;
	return (i);
}

char	**ft_add_to_last(char **ptr, char *cmd)
{
	int		len;
	char	**str;

	len = ft_strleen(ptr);
	str = malloc(sizeof(char *) * (len + 2));
	if (!str)
		return (NULL);
	str[len + 1] = 0;
	len = -1;
	while (ptr[++len])
		str[len] = ft_strdup(ptr[len]);
	str[len] = ft_strdup(cmd);
	free(cmd);
	ft_free(ft_strleen(ptr), ptr);
	return (str);
}

int	ft_cmd_valid_exist(char **ptr, char **cmd)
{
	int		i;
	char	*str;
	char	*str1;

	i = 0;
	while (ptr[i])
	{
		str1 = ft_strjoin(ptr[i], "/");
		str = ft_strjoin(str1, cmd[0]);
		if (!access(str, X_OK | F_OK))
		{
			free(str);
			free(str1);
			return (i);
		}
		else if (!access(cmd[0], X_OK | F_OK))
			return (i);
		i++;
	}
	free(str1);
	free(str);
	return (-1);
}

// int ft_parce_file1(t_pipe *p)
// {
// 	char *tmp;

// 	if (p->fd < 0)
// 	{
// 		ft_free(ft_strleen(p->cmd1), p->cmd1);
// 		ft_free(ft_strleen(p->cmd2), p->cmd2);
// 		ft_free(ft_strlen(p->env), p->env);
// 		return (-1);
// 	}
// 	else
// 	{
// 	}
// }