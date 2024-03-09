/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibouzid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 12:39:05 by hibouzid          #+#    #+#             */
/*   Updated: 2024/03/08 22:50:35 by hibouzid         ###   ########.fr       */
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
