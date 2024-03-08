/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_util_0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibouzid <hibouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 13:08:54 by hibouzid          #+#    #+#             */
/*   Updated: 2024/03/08 19:39:53 by hibouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	printf("---> s1%s\n", s1);
	printf("---> s2%s\n", s2);
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
		{
			return (s1[i] - s2[i]);
		}
		i++;
	}
			printf("----------\n");
	return (0);
}

int	ft_index(char **envp, char *str)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strcmp(envp[i], str) == 0)
			return (i);
		i++;
	}
	return (-1);
}

char	**ft_parce_env(char **envp)
{
	int		i;
	int		index;
	char	**tab;

	index = ft_index(envp, "PATH");
	i = 0;
	if (index == -1)
		return (NULL);
	while (envp[index][i])
	{
		if (is_separator(envp[index][i], '/'))
			break ;
		i++;
	}
	tab = ft_split(envp[index] + i, ':');
	return (tab);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		total;
	char	*ptr;
	int		i;
	int		j;

	if (!s1)
		s1 = ft_strdup("");
	total = ft_strlen(s1) + ft_strlen(s2);
	ptr = malloc(sizeof(char) * (total + 1));
	if (!ptr)
		return (NULL);
	ptr[total] = 0;
	i = 0;
	j = 0;
	while (s1[i])
	{
		ptr[i] = s1[i];
		i++;
	}
	while (s2[j])
		ptr[i++] = s2[j++];
	return (ptr);
}
