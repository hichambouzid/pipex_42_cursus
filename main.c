/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibouzid <hibouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:51:15 by hibouzid          #+#    #+#             */
/*   Updated: 2024/03/08 15:51:59 by hibouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
// #include <sys/types.h>
// #include <sys/wait.h>
// #include <unistd.h>

// int	main(void)
// {
// 	int		i;
// 	pid_t	pid;

// 	for (i = 0; i < 3; i++)
// 	{
// 		pid = fork();
// 		if (pid == 0)
// 		{
// 			printf("Child %d with PID %d\n", i + 1, getpid());
// 			return (0);
// 		}
// 		else if (pid < 0)
// 		{ // Error handling
// 			perror("fork failed");
// 			return (1);
// 		}
// 	}
// 	for (i = 0; i < 3; i++)
// 	{
// 		wait(NULL);
// 	}
// 	printf("Parent process with PID %d\n", getpid());
// 	return (0);
// }
