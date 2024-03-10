/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_util_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibouzid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 16:44:37 by hibouzid          #+#    #+#             */
/*   Updated: 2024/03/10 17:17:17 by hibouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

int	ft_child_proccess(t_pipe *p, int *pipfd, char **envp)
{
	if (dup2(pipfd[1], 1) == -1 || dup2(p->fd1, 0))
		return (ft_putstr_fd("Error has occured in dup\n", 2));
	p->index = ft_cmd_valid_exist(p->env, p->cmd1);
	p->env[p->index] = ft_same_arg(p->env, p->cmd1[0], p->index);
	close(pipfd[0]);
	close(p->fd1);
	p->path = ft_chose_path(p->env[p->index], p->cmd1[0]);
	execve(p->path, p->cmd1, envp);
	return (0);
}

int	ft_parent_proccess(t_pipe *p, int *pipfd, char **envp)
{
	if (dup2(pipfd[0], 0) == -1 || dup2(p->fd2, 1) == -1)
		return (ft_putstr_fd("Error has occured in dup\n", 2));
	p->index = ft_cmd_valid_exist(p->env, p->cmd2);
	p->env[p->index] = ft_same_arg(p->env, p->cmd2[0], p->index);
	p->path = ft_chose_path(p->env[p->index], p->cmd2[0]);
	close(pipfd[0]);
	close(pipfd[1]);
	execve(p->path, p->cmd2, envp);
	return (0);
}

void	mpipex(t_pipe p, char **av, char **envp)
{
	int		pipfd[2];
	pid_t	pp;

	pipe(pipfd);
	ft_first_check(av[2], av[3]);
	ft_parce_1(&p, av, envp);
	pp = fork();
	if (pp == 0)
		ft_child_proccess(&p, pipfd, envp);
	else
	{
		ft_parent_proccess(&p, pipfd, envp);
		wait(NULL);
	}
}

void	ft_parce_1(t_pipe *p, char **av, char **envp)
{
	p->cmd1 = ft_split(av[2], ' ');
	p->cmd2 = ft_split(av[3], ' ');
	p->env = ft_parce_env(envp);
	if (ft_parce_cmd(p->cmd1, p->cmd2, p->env) == -1)
	{
		ft_free(ft_strleen(p->cmd1), p->cmd1);
		ft_free(ft_strleen(p->cmd2), p->cmd2);
		ft_free(ft_strleen(p->env), p->env);
		ft_putstr_fd("command not found\n", 2);
		exit(-1);
	}
	if (p->fd1 < 0 || p->fd2 < 0)
	{
		ft_free(ft_strleen(p->cmd1), p->cmd1);
		ft_free(ft_strleen(p->cmd2), p->cmd2);
		ft_free(ft_strleen(p->env), p->env);
		exit(-1);
	}
}

int	ft_strncmp(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	while ((s1[i] && s2[i]) && i < n)
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}
