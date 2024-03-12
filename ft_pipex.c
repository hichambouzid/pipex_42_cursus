/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibouzid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 10:36:36 by hibouzid          #+#    #+#             */
/*   Updated: 2024/03/12 14:10:32 by hibouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

int main(int ac, char **av, char **envp)
{
	t_pipe p;

	if (ac != 5)
		return (ft_putstr_fd("error in argument\n", 2));
	p.fd1 = open(av[1], O_RDONLY);
	if (p.fd1 < 0)
		return (ft_putstr_fd("no such file or directory\n", 2));
	p.fd2 = open(av[4], O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (p.fd2 < 0)
		return (ft_putstr_fd("no such file or directory\n", 2));
		pipex(p, av, envp);
}

// int main(int ac, char **av, char **envp)
// {
// 	ft_e(ac, av, envp);
// }