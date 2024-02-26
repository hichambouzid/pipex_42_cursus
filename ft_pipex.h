/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibouzid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 10:36:06 by hibouzid          #+#    #+#             */
/*   Updated: 2024/02/26 19:03:31 by hibouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PIPEX_H
#define FT_PIPEX_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

typedef struct variables
{
	char	**env;
	char	**cmd1;
	char	**cmd2;
	int		fd;
}t_pipe;

/*
* util functions
* used in parcing
*/

char **ft_split(char const *s, char c);
char **ft_alloc(char **ptr, const char *s, char c, int e);
char **ft_free(int index, char **ptr);
int ft_count(char const *s, char c);
int is_separator(char s, char c);
int ft_strcmp(char *s1, char *s2);
int ft_index(char **envp, char *str);
char *ft_strjoin(char *s1, char *s2);
int ft_strlen(char *str);
int ft_strleen(char **ptr);
void	ft_putstr_fd(char *s, int fd);

/*
* main functions 
* where we use system calls
*/
char **ft_parce_env(char **envp);
int ft_cmd_valid_exist(char **ptr, char **cmd);
int	ft_parce_cmd(char **cmd1, char **cmd2, char **anv);

#endif