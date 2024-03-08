/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibouzid <hibouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 10:36:06 by hibouzid          #+#    #+#             */
/*   Updated: 2024/03/08 15:55:51 by hibouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PIPEX_H
# define FT_PIPEX_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct variables
{
	char	**env;
	char	**cmd1;
	char	**cmd2;
	char	*tmpr;
	char	*buffer;
	int		fd1;
	int		fd2;
	int		index;
	int		i;
	char	*line;
	char	*path;
}			t_pipe;

# define SIZE_M 2147483647
# define BUFFER_SIZE 2147483647
/*
 * util functions
 * used in parcing
 */

char		**ft_split(char const *s, char c);
char		**ft_alloc(char **ptr, const char *s, char c, int e);
char		**ft_free(int index, char **ptr);
int			ft_count(char const *s, char c);
int			is_separator(char s, char c);
int			ft_strcmp(char *s1, char *s2);
int			ft_index(char **envp, char *str);
char		*ft_strjoin(char *s1, char *s2);
int			ft_strlen(char *str);
int			ft_strleen(char **ptr);
int			ft_putstr_fd(char *s, int fd);
char		*ft_strdup(char *s1);

// functions used in bonus part

int			ft_check(char *str, char c);
char		*ft_line(char *ptr);
char		*get_next_line(int fd);
char		*get_read(char *ptr, int fd);
char		*ft_get_buffer(char **av);

/*
 * main functions
 * where we use system calls
 */
char		**ft_parce_env(char **envp);
int			ft_cmd_valid_exist(char **ptr, char **cmd);
int			ft_parce_cmd(char **cmd1, char **cmd2, char **anv);
// int ft_parce_file1(t_pipe *p);
char		**ft_add_to_last(char **ptr, char *cmd);
void		ft_parce_1(t_pipe *p, char **av, char **envp);
char		*ft_same_arg(char **ptr, char *cmd, int index);
char		*ft_chose_path(char *path, char *envp);
int			ft_child_proccess(t_pipe *p, int *pipfd, char **envp);
int			ft_parent_proccess(t_pipe *p, int *pipfd, char **envp);
void		pipex(t_pipe p, char **av, char **envp);
int			**ft_pipes(int ac);
int			ft_multiple_pips(t_pipe *p, char **envp, char **av, int ac);
void		ft_close(int **tabfd, int fd1, int fd2);

#endif
