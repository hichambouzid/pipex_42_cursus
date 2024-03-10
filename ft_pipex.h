/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibouzid <hibouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 10:36:06 by hibouzid          #+#    #+#             */
<<<<<<< Updated upstream
/*   Updated: 2024/03/09 23:19:53 by hibouzid         ###   ########.fr       */
=======
/*   Updated: 2024/03/04 22:11:17 by hibouzid         ###   ########.fr       */
>>>>>>> Stashed changes
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
	int		**tab;
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
int			ft_strncmp(char *s1, char *s2, int n);
void		ft_first_check(char *av1, char *av2);
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
<<<<<<< Updated upstream
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
void		ft_dup(int in, int out, int **tab);
int			ft_child_proccess_doc(t_pipe *p, char **envp, int *pipfd,
				int *pipfd1);
int			ft_parent_proccess_doc(t_pipe *p, char **envp, int *pipfd,
				int *pipfd1);
=======
char **ft_add_to_last(char **ptr, char *cmd);
char	*ft_get_read_all(int fd);
void ft_parce_1(t_pipe *p, char **av, char **envp);
char *ft_same_arg(char **ptr, char *cmd, int index);
char *ft_chose_path(char *path, char *envp);
int ft_child_proccess(t_pipe *p, int *pipfd, char **envp);
int ft_parent_proccess(t_pipe *p, int *pipfd, char **envp);
void ft_parce_cmd2(t_pipe *p, char **av, char **envp);
>>>>>>> Stashed changes

#endif
