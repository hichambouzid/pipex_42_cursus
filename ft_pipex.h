/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibouzid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 10:36:06 by hibouzid          #+#    #+#             */
/*   Updated: 2024/02/25 15:32:33 by hibouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PIPEX_H
#define FT_PIPEX_H

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<fcntl.h>

char	**ft_split(char const *s, char c);
char	**ft_alloc(char **ptr, const char *s, char c, int e);
char	**ft_free(int index, char **ptr);
int		ft_count(char const *s, char c);
int		is_separator(char s, char c);
int		ft_strcmp(char *s1, char *s2);
int ft_index(char **envp, char *str);

char **ft_parce_env(char **envp);

#endif