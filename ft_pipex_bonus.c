/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibouzid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 16:08:55 by hibouzid          #+#    #+#             */
/*   Updated: 2024/03/04 16:36:15 by hibouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"


int ft_child_proccess_doc(t_pipe *p, char **envp, int *pipfd, int *pipfd1)
{
	printf("---> %d\n", pipfd[0]);
	printf("---> %d\n", pipfd[1]);
	printf("---> %d\n", pipfd1[0]);
	printf("---> %d\n", pipfd1[1]);
	
	// printf("%s", p->buffer);
	ft_putstr_fd(p->buffer, pipfd[1]);
	if (dup2(pipfd[0], 0) == -1)
		return (ft_putstr_fd("Error has occured in dup\n", 2));
	printf("i'm here\n");
	if (dup2(pipfd1[1], 1) == -1)
		return (ft_putstr_fd("Error has occured in dup1\n", 2));
	p->index = ft_cmd_valid_exist(p->env, p->cmd1);
	p->env[p->index] = ft_same_arg(p->env, p->cmd1[0], p->index);
	p->path = ft_chose_path(p->env[p->index], p->cmd1[0]);
	execve(p->path, p->cmd1, envp);
	return (0);
}


int ft_parent_proccess_doc(t_pipe *p, char **envp, int *pipfd, int *pipfd1)
{
	(void)pipfd;
	if (dup2(p->fd2, 1) == -1 || dup2(pipfd1[0], 0) == -1)
		return (ft_putstr_fd("Error has occured in dup\n", 2));	
	p->index = ft_cmd_valid_exist(p->env, p->cmd2);
	p->env[p->index] = ft_same_arg(p->env, p->cmd2[0], p->index);
	p->path = ft_chose_path(p->env[p->index], p->cmd2[0]);
	execve(p->path, p->cmd2, envp);
	return (0);
}

void pipex_her_doc(char **envp, t_pipe p)
{
	int pipfd[2];
	int pipfd1[2];
	pid_t pp;

	pipe(pipfd);
	pipe(pipfd1);
	pp = fork();

	if (pp == 0)
		ft_child_proccess_doc(&p, envp, pipfd, pipfd1);
	else
	{
		ft_parent_proccess_doc(&p, envp, pipfd, pipfd1);
		wait(NULL);
	}
	
}

int main(int ac, char **av, char **envp)
{
	t_pipe pe;

	pe.buffer = 0;
	// printf("i'm herre\n");
	if (!ft_strcmp(av[1], "here_doc") && ac == 6)
	{
		pe.fd2 = open(av[5], O_CREAT | O_WRONLY | O_APPEND, 0777);
		if (pe.fd2 < 0)
			return (0);
		pe.buffer = ft_get_buffer(av);
		pipex_her_doc(envp, pe);
	}
}