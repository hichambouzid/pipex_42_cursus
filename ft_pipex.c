/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibouzid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 10:36:36 by hibouzid          #+#    #+#             */
/*   Updated: 2024/02/26 19:04:35 by hibouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

int main(int ac, char **av, char **envp)
{
	t_pipe p;
	
	p.cmd1 = ft_split(av[1], ' ');	
	p.cmd2 = ft_split(av[3], ' ');
	p.env = ft_parce_env(envp);
	if (ft_parce_cmd(p.cmd1, p.cmd2, p.env) == -1)
	{
		ft_pustr_fd("command not found\n", 2);
		exit(-1);
	}
	p.fd = open(av[1], O_RDONLY);
	

}