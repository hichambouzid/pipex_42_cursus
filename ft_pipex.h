/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibouzid <hibouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 21:39:40 by hibouzid          #+#    #+#             */
/*   Updated: 2024/03/16 23:53:29 by hibouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PIPEX_H
# define FT_PIPEX_H
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct ft_pipex
{
	int		i;
	int		index;
	int		fd1;
	char	**cmd;
	int		fd2;
	char	**env;
	int		f;
	pid_t	f1;
	pid_t	f2;
	char	***tab_cmd;
	char	**paths;
	char	*path;
	char	**envp;

}			t_pipe;

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 12112123
# endif

int			ft_putstr_fd(char *s, int fd);
int			ft_strcmp(char *s1, char *s2);
char		*ft_strjoin(char *s1, char *s2);
char		*ft_strdup(char *str);
int			ft_strlen(char *str);
int			ft_strleen(char **ptr);
int			ft_parce_cmd(char **cmd, char **envp);
char		**ft_split(char const *s, char c);
char		**ft_alloc(char **ptr, const char *s, char c, int e);
char		**ft_free(int index, char **ptr);
int			ft_count(char const *s, char c);
int			is_separator(char s, char c);
int			ft_strncmp(char *s1, char *s2, int n);
int			ft_index(char **envp, char *str);
char		**ft_parce_env(char **env);
char		**get_all_path(int number);
int			ft_cmd_valid(char **env, char **cmd);
void		ft_error(char *str, int exi);
char		***ft_free_cmd(int len, char ***tab_cmd);
char		*ft_chose_path(int number, char **env, char **cmd);
void		ft_parce_all(int ac, char **av, char **envp, t_pipe *p);
void		ft_process(t_pipe *p, int in, int *fd);
char		***fill_tab_cmd(int len, char ***tab_cmd, char **av);
void		ft_first_check(char *av1, char *av2);

// part bonus
void		ft_here_doc(int ac, char **av, char **envp);
char		*get_read(char *ptr, int fd);
char		*ft_cut(char *ptr);
char		*ft_freee(char *str, char *ptr);
char		*ft_line(char *ptr);
char		*get_next_line(int fd);
int			ft_check(char *str, char c);

#endif
