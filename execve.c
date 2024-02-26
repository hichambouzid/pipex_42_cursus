/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibouzid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 11:21:31 by hibouzid          #+#    #+#             */
/*   Updated: 2024/02/26 18:31:20 by hibouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

int main()
{
	char *argc[] = {"ns","/sbin/", NULL};
	char *nvp[] = {NULL};
	printf("-----------> %d\n", execve("/bin/ls", argc, nvp));
	// int i = access("/bin/fsck", R_OK | X_OK | F_OK);
	// printf("---------> %d\n", F_OK);
	// printf("---------> %d\n", i);
	// execve("/bin/ls", argc[1], nvp);
	return (1);
}