/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibouzid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 11:21:31 by hibouzid          #+#    #+#             */
/*   Updated: 2024/02/25 15:58:11 by hibouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

int main()
{
	char *argc[] = {"ls", "-l", NULL};
	char *nvp[] = {NULL};
	execve("/bin/ls", argc, nvp);
	// execve("/bin/ls", argc[1], nvp);
	// perror("execve");
	return (1);
}