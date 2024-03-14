/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parce_all.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibouzid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 01:53:04 by hibouzid          #+#    #+#             */
/*   Updated: 2024/03/14 15:52:55 by hibouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

char **get_all_PATH(int number)
{
	char **PATH;

	PATH = malloc(sizeof(char *) * (number + 1));
	if (!PATH)
		return (NULL);
	PATH[number] = 0;
	return (PATH);
}

void ft_error(char *str, int exi)
{
	ft_putstr_fd(str, 2);
	exit(exi);
}

void ft_parce_all(int ac, char **av, char **envp, t_pipe *p)
{

	p->i = ac - 3;
	p->env = ft_parce_env(envp);
	p->tab_cmd = malloc(sizeof(char *) * (p->i + 1));
	if (!p->tab_cmd)
		return;
	p->tab_cmd[p->i] = NULL;
	p->i = 0;
	while (p->i < ac - 3)
	{
		p->tab_cmd[p->i] = ft_split(av[p->i], ' ');
		p->i++;
	}
	p->PATH = get_all_PATH(ac - 3);
	p->i = 0;
	while (p->i < ac - 3)
	{
		p->f = ft_cmd_valid(p->env, p->tab_cmd[p->i]);
		if (p->f == -1)
		{
			ft_free_cmd(ac - 4, p->tab_cmd);
			ft_free(ft_strleen(p->PATH), p->PATH);
			ft_free(ft_strleen(p->env), p->env);
			ft_error("Command not found\n", -1);
		}
		else
			p->PATH[p->i] = ft_chose_path(p->f, p->env, p->tab_cmd[p->i]);
		p->i++;
	}
	return;
}

char *ft_chose_path(int number, char **env, char **cmd)
{
	int i;
	char *tmp;

	if (number == 1)
		return (ft_strdup(cmd[0]));
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

char ***ft_free_cmd(int len, char ***tab_cmd)
{
	while (len >= 0)
	{
		ft_free(ft_strleen(tab_cmd[len]), tab_cmd[len]);
		len--;
	}
	free(tab_cmd);
	return (NULL);
}
