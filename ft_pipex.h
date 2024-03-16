/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibouzid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD
/*   Created: 2024/03/12 21:39:40 by hibouzid          #+#    #+#             */
/*   Updated: 2024/03/15 16:27:38 by hibouzid         ###   ########.fr       */
=======
/*   Created: 2024/02/20 10:36:06 by hibouzid          #+#    #+#             */
/*   Updated: 2024/03/10 17:24:08 by hibouzid         ###   ########.fr       */
>>>>>>> edc993a (update some files)
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PIPEX_H
#define FT_PIPEX_H
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct ft_pipex
{
	int i;
	int index;
	int fd1;
	char **cmd;
	int fd2;
	char **env;
	int f;
	char ***tab_cmd;
	char **paths;
	char *path;
	char **envp;

} t_pipe;

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 12112123
#endif

int ft_putstr_fd(char *s, int fd);
int ft_strcmp(char *s1, char *s2);
char *ft_strjoin(char *s1, char *s2);
char *ft_strdup(char *str);
int ft_strlen(char *str);
int ft_strleen(char **ptr);
int ft_parce_cmd(char **cmd, char **envp);
char **ft_split(char const *s, char c);
char **ft_alloc(char **ptr, const char *s, char c, int e);
char **ft_free(int index, char **ptr);
int ft_count(char const *s, char c);
int is_separator(char s, char c);
int ft_strncmp(char *s1, char *s2, int n);
int ft_index(char **envp, char *str);
char **ft_parce_env(char **env);
char **get_all_path(int number);
int ft_cmd_valid(char **env, char **cmd);
void ft_error(char *str, int exi);
char ***ft_free_cmd(int len, char ***tab_cmd);
char *ft_chose_path(int number, char **env, char **cmd);
void ft_parce_all(int ac, char **av, char **envp, t_pipe *p);
void ft_process(t_pipe *p, int in, int *fd);
char ***fill_tab_cmd(int len, char ***tab_cmd, char **av);
void ft_first_check(char *av1, char *av2);

<<<<<<< HEAD
// part bonus
void ft_here_doc(int ac, char **av, char **envp);
char *get_read(char *ptr, int fd);
char *ft_cut(char *ptr);
char *ft_freee(char *str, char *ptr);
char *ft_line(char *ptr);
char *get_next_line(int fd);
int ft_check(char *str, char c);
=======
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
void		ft_dup(int in, int out, int **tab);
int			ft_child_proccess_doc(t_pipe *p, char **envp, int *pipfd,
				int *pipfd1);
int			ft_parent_proccess_doc(t_pipe *p, char **envp, int *pipfd,
				int *pipfd1);
>>>>>>> edc993a (update some files)

#endif
