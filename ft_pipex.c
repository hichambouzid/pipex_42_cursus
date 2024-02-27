/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibouzid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 10:36:36 by hibouzid          #+#    #+#             */
/*   Updated: 2024/02/27 21:23:27 by hibouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"


void ft_parce_1(t_pipe *p, char **av, char **envp)
{
	p->cmd1 = ft_split(av[2], ' ');	
	p->cmd2 = ft_split(av[3], ' ');
	p->env = ft_parce_env(envp);
	if (ft_parce_cmd(p->cmd1, p->cmd2, p->env) == -1)
	{
		ft_putstr_fd("command not found\n", 2);
		exit(-1);
	}
	p->fd = open(av[1], O_RDONLY);
	if (p->fd < 0)
	{
		ft_free(ft_strleen(p->cmd1), p->cmd1);
		ft_free(ft_strleen(p->cmd2), p->cmd2);
		ft_free(ft_strleen(p->env), p->env);
		exit(-1);
	}
	p->buffer = ft_get_read_all(p->fd);
	p->cmd1 = ft_add_to_last(p->cmd1, p->buffer);
}

int main(int ac, char **av, char **envp)
{
	t_pipe p;
	
	if (ac > 2)
	
	ft_parce_1(&p, av, envp);
	// printf("%s\n", p.env[ft_cmd_valid_exist(p.env, p.cmd1)]);
	p.index = ft_cmd_valid_exist(p.env, p.cmd1);
	p.env[p.index] = ft_same_arg(p.env, p.cmd1[0], p.index);
	int i = execve(p.env[p.index], p.cmd1, envp);

}