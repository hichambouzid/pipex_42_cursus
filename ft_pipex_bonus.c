/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibouzid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 01:32:52 by hibouzid          #+#    #+#             */
/*   Updated: 2024/03/17 17:17:40 by hibouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

void write_in_pipe(char *limeter, int *fd)
{
	char *line;
	char *f;

	f = ft_strjoin(limeter, "\n");
	while (1)
	{
		ft_putstr_fd("pipe heredoc> ", 1);
		line = get_next_line(0);
		ft_putstr_fd(line, fd[1]);
		if (!ft_strcmp(line, f))
		{
			free(line);
			break;
		}
		free(line);
	}
	free(f);
	return;
}

int ft_child(t_pipe p, int *fd11, int *fd00)
{
	close(fd11[1]);
	if (dup2(fd11[0], 0) == -1 || dup2(fd00[1], 1) == -1)
		ft_error("problem in dup function\n", -1);
	close(fd00[0]);
	close(fd00[1]);
	close(fd11[0]);
	if (!p.paths[0])
		p.paths[0] = p.tab_cmd[0][0];
	if (execve(p.paths[0], p.tab_cmd[0], p.env) == -1)
		ft_error("execve 1problem\n", -1);
	return (0);
}

int ft_child1(t_pipe p, int *fd11, int *fd00, int fd2)
{
	close(fd11[1]);
	close(fd00[1]);
	if (dup2(fd00[0], 0) == -1 || dup2(fd2, 1) == -1)
		ft_error("error in dup\n", -1);
	close(fd11[0]);
	close(fd00[0]);
	close(fd2);
	if (!p.paths[1])
		p.paths[1] = p.tab_cmd[1][0];
	if (execve(p.paths[1], p.tab_cmd[1], p.env) == -1)
		ft_error("execve 2problem\n", -1);
	return (0);
}

void ft_here_doc(int ac, char **av, char **envp)
{
	t_pipe p;
	int fd[2][2];

	ft_parce_all(ac - 1, av + 3, envp, &p);
	p.fd2 = open(av[ac - 1], O_CREAT | O_RDWR | O_APPEND, 0777);
	if (p.fd2 < 0)
		ft_error("cann't open the file\n", -1);
	if (pipe(fd[1]) == -1 || pipe(fd[0]) == -1)
		ft_error("pipe problem\n", -1);
	write_in_pipe(av[2], fd[1]);
	p.f1 = fork();
	if (p.f1 == 0)
		ft_child(p, fd[1], fd[0]);
	p.f2 = fork();
	if (p.f2 == 0)
		ft_child1(p, fd[1], fd[0], p.fd2);
	close(fd[0][1]);
	close(fd[0][0]);
	close(fd[1][1]);
	close(fd[0][0]);
	while (wait(NULL) > 0)
		;
	ft_free_cmd(1, p.tab_cmd);
	ft_free(ft_strleen(p.paths), p.paths);
	ft_free(ft_strleen(p.env), p.env);
}

int main(int ac, char **av, char **envp)
{
	if (ac < 5)
		ft_error("Invalide number of argument\n", -1);
	if (ac == 6 && !ft_strcmp("here_doc", av[1]))
		ft_here_doc(ac, av, envp);
}
