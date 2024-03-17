/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parce_all.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibouzid <hibouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 01:53:04 by hibouzid          #+#    #+#             */
/*   Updated: 2024/03/17 00:08:48 by hibouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

char	**get_all_path(int number)
{
	char	**paths;

	paths = malloc(sizeof(char *) * (number + 1));
	if (!paths)
		return (NULL);
	paths[number] = 0;
	return (paths);
}

void	ft_error(char *str, int exi)
{
	ft_putstr_fd(str, 2);
	exit(exi);
}

void	ft_parce_all(int ac, char **av, char **envp, t_pipe *p)
{
	p->i = ac - 3;
	p->env = ft_parce_env(envp);
	p->tab_cmd = malloc(sizeof(char *) * (p->i + 1));
	p->tab_cmd[p->i] = NULL;
	p->tab_cmd = fill_tab_cmd(ac - 3, p->tab_cmd, av);
	p->paths = get_all_path(ac - 3);
	p->i = 0;
	while (p->i < ac - 3)
	{
		p->f = ft_cmd_valid(p->env, p->tab_cmd[p->i]);
		if (p->f == -1)
		{
			ft_free_cmd(p->i - 1, p->tab_cmd);
			ft_free(p->i - 1, p->paths);
			if (!p->env)
				free(p->env);
			if (p->env)
				ft_free(ft_strleen(p->env), p->env);
			ft_error("Command not found\n", -1);
		}
		else
			p->paths[p->i] = ft_chose_path(p->f, p->env, p->tab_cmd[p->i]);
		p->i++;
	}
}

char	*ft_chose_path(int number, char **env, char **cmd)
{
	int		i;
	char	*tmp;

	if (number == 1)
	{
		return (ft_strdup(cmd[0]));
	}
	i = 0;
	while (env[i])
	{
		tmp = ft_strjoin(env[i], cmd[0]);
		if (!access(tmp, X_OK | F_OK))
			return (tmp);
		else
			free(tmp);
		i++;
	}
	return (NULL);
}

char	***ft_free_cmd(int len, char ***tab_cmd)
{
	while (len >= 0)
	{
		if (tab_cmd[len])
			ft_free(ft_strleen(tab_cmd[len]), tab_cmd[len]);
		len--;
	}
	free(tab_cmd);
	return (NULL);
}
