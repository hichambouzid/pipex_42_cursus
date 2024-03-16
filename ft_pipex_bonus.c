/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibouzid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD
/*   Created: 2024/03/15 01:32:52 by hibouzid          #+#    #+#             */
/*   Updated: 2024/03/15 21:33:30 by hibouzid         ###   ########.fr       */
=======
/*   Created: 2024/03/01 16:08:55 by hibouzid          #+#    #+#             */
/*   Updated: 2024/03/11 13:49:14 by hibouzid         ###   ########.fr       */
>>>>>>> edc993a (update some files)
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

void write_in_pipe(char *limeter, int *fd)
{
<<<<<<< HEAD
	char *line;
	char *f;

	f = ft_strjoin(limeter, "\n");
	// printf("%d\n", fd[0]);
	// printf("%d\n", ft_strcmp(limeter, f));
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
	if (execve(p.paths[0], p.tab_cmd[0], p.env) == -1)
		ft_error("execve problem\n", -1);
=======
	p->cmd1 = ft_split(av[f], ' ');
	p->index = ft_cmd_valid_exist(p->env, p->cmd1);
	p->env[p->index] = ft_same_arg(p->env, p->cmd1[0], p->index);
	p->path = ft_chose_path(p->env[p->index], p->cmd1[0]);
	if (execve(p->path, p->cmd1, envp) == -1)
		exit(-1);
>>>>>>> edc993a (update some files)
	return (0);
}

int ft_child1(t_pipe p, int *fd11, int *fd00, int fd2)
{
<<<<<<< HEAD
	// (void)fd11
	close(fd11[1]);
	close(fd00[1]);
	if (dup2(fd00[0], 0) == -1 || dup2(fd2, 1) == -1)
		ft_error("error in dup\n", -1);
	close(fd11[0]);
	close(fd00[0]);
	close(fd2);
	// close(1);
	if (execve(p.paths[1], p.tab_cmd[1], p.env) == -1)
		ft_error("execve problem\n", -1);
	return (0);
}

void ft_here_doc(int ac, char **av, char **envp)
{
	t_pipe p;
	pid_t f1;
	pid_t f2;
	int fd[2][2];
=======
	int		pipfd[2];
	int		pipfd1[2];
	pid_t	pp;
>>>>>>> edc993a (update some files)

	ft_parce_all(ac - 1, av + 3, envp, &p);
	p.fd2 = open(av[ac - 1], O_CREAT | O_RDWR | O_APPEND, 0777);
	if (p.fd2 < 0)
		ft_error("cann't open the file\n", -1);
	if (pipe(fd[1]) == -1 || pipe(fd[0]) == -1)
		ft_error("pipe problem\n", -1);
	
	write_in_pipe(av[2], fd[1]);
	f1 = fork();
	if (f1 == 0)
		ft_child(p, fd[1], fd[0]);
	f2 = fork();
	if (f2 == 0)
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
	return;
}

int main(int ac, char **av, char **envp)
{
<<<<<<< HEAD
	if (ac < 5)
		ft_error("Invalide number of argument\n", -1);
	if (ac == 6 && !ft_strcmp("here_doc", av[1]))
		ft_here_doc(ac, av, envp);
	system("leaks pipex_bonus");
}
=======
	t_pipe	pip;
	pid_t	pp;

	pip.i = 2;
	while (pip.i < ac - 1)
	{
		pp = fork();
		if (pip.i == 2 && pp == 0)
			ft_dup(p->fd1, p->tab[0][1], p->tab);
		else if (pip.i == ac - 2 && pp == 0)
			ft_dup(p->tab[pip.i - 3][0], p->fd2, p->tab);
		else if (pp == 0)
			ft_dup(p->tab[pip.i - 3][0], p->tab[pip.i - 2][1], p->tab);
		ft_procces(p, av, pip.i, envp);
		pip.i++;
	}
	if (pp)
		wait(NULL);
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	t_pipe	pe;

	pe.buffer = 0;
	if (!ft_strcmp(av[1], "here_doc") && ac == 6)
	{
		pe.fd2 = open(av[5], O_CREAT | O_RDWR | O_APPEND, 0777);
		if (pe.fd2 < 0)
			return (0);
		pe.buffer = ft_get_buffer(av);
		ft_parce_1(&pe, (av + 1), envp);
		pipex_her_doc(envp, pe);
	}
	else if (ac >= 5)
	{
		pe.fd1 = open(av[1], O_RDONLY);
		if (pe.fd1 < 0)
			return (-1);
		pe.fd2 = open(av[ac - 1], O_RDWR | O_CREAT | O_TRUNC, 0777);
		if (pe.fd2 < 0)
			return (-1);
		pe.tab = ft_pipes(ac);
		pe.env = ft_parce_env(envp);
		ft_multiple_pips(&pe, envp, av, ac);
	}
	return (-1);
}
>>>>>>> edc993a (update some files)
