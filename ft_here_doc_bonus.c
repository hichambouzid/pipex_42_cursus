/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibouzid <hibouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 12:39:05 by hibouzid          #+#    #+#             */
/*   Updated: 2024/03/09 22:21:48 by hibouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

char	*ft_get_buffer(char **av)
{
	t_pipe	pe;

	pe.buffer = 0;
	while (1)
	{
		ft_putstr_fd("pipe heredoc> ", 1);
		pe.line = get_next_line(0);
		pe.tmpr = pe.buffer;
		pe.buffer = ft_strjoin(pe.buffer, pe.line);
		if (pe.tmpr)
			free(pe.tmpr);
		if (ft_strcmp(pe.line, ft_strjoin(av[2], "\n")) == 0)
		{
			free(pe.line);
			break ;
		}
		else
			free(pe.line);
	}
	return (pe.buffer);
}

void	ft_parce_cmd2(t_pipe *p, char **av, char **envp)
{
	p->cmd1 = ft_split(av[3], ' ');
	p->cmd2 = ft_split(av[4], ' ');
	p->env = ft_parce_env(envp);
	if (ft_parce_cmd(p->cmd1, p->cmd2, envp) == -1)
	{
		ft_free(ft_strleen(p->cmd1), p->cmd1);
		ft_free(ft_strleen(p->cmd2), p->cmd2);
		ft_free(ft_strleen(p->env), p->env);
		ft_putstr_fd("command not found\n", 2);
		exit(-1);
	}
}

int	ft_child_proccess_doc(t_pipe *p, char **envp, int *pipfd, int *pipfd1)
{
	ft_putstr_fd(p->buffer, pipfd[1]);
	if (dup2(pipfd[0], 0) == -1 || dup2(pipfd1[1], 1) == -1)
		return (ft_putstr_fd("Error has occured in dup\n", 2));
	close(pipfd[1]);
	close(pipfd1[0]);
	p->index = ft_cmd_valid_exist(p->env, p->cmd1);
	p->env[p->index] = ft_same_arg(p->env, p->cmd1[0], p->index);
	p->path = ft_chose_path(p->env[p->index], p->cmd1[0]);
	if (execve(p->path, p->cmd1, envp) == -1)
		exit(-1);
	return (0);
}

int	ft_parent_proccess_doc(t_pipe *p, char **envp, int *pipfd, int *pipfd1)
{
	if (dup2(p->fd2, 1) == -1 || dup2(pipfd1[0], 0) == -1)
		return (ft_putstr_fd("Error has occured in dup\n", 2));
	close(pipfd1[1]);
	close(pipfd[1]);
	p->index = ft_cmd_valid_exist(p->env, p->cmd2);
	p->env[p->index] = ft_same_arg(p->env, p->cmd2[0], p->index);
	p->path = ft_chose_path(p->env[p->index], p->cmd2[0]);
	if (execve(p->path, p->cmd2, envp) == -1)
		exit(-1);
	return (0);
}
