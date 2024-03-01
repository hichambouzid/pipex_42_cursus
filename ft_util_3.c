/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_util_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibouzid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 16:44:37 by hibouzid          #+#    #+#             */
/*   Updated: 2024/02/29 20:56:51 by hibouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

int ft_child_proccess(t_pipe *p, int *pipfd, char **envp)
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

int ft_parent_proccess(t_pipe *p, int *pipfd, char **envp)
{
	if (dup2(pipfd[0], 0) == -1 || dup2(p->fd2, 1) == -1)
		return (ft_putstr_fd("Error has occured in dup\n", 2));
	p->index = ft_cmd_valid_exist(p->env, p->cmd2);
	p->env[p->index] = ft_same_arg(p->env, p->cmd2[0], p->index);
	p->path = ft_chose_path(p->env[p->index], p->cmd2[0]);
	close(pipfd[0]);
	close(pipfd[1]);
	// close(p->fd2)
	execve(p->path, p->cmd2, envp);
	return (0);
}
