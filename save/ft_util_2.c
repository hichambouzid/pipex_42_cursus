/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_util_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibouzid <hibouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:11:24 by hibouzid          #+#    #+#             */
/*   Updated: 2024/03/09 15:34:03 by hibouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

char	*ft_strdup(char *s1)
{
	int		i;
	char	*str;

	i = 0;
	i = ft_strlen(s1);
	str = malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = 0;
	return (str);
}

char	*ft_same_arg(char **ptr, char *cmd, int index)
{
	char	*tmp;
	char	*tmp1;

	tmp = ft_strjoin(ptr[index], "/");
	tmp1 = ft_strjoin(tmp, cmd);
	free(ptr[index]);
	free(tmp);
	ptr[index] = tmp1;
	return (ptr[index]);
}

char	*ft_chose_path(char *path, char *envp)
{
	if (!access(path, F_OK | X_OK))
		return (path);
	else
		return (envp);
}

void	ft_first_check(char *av1, char *av2)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (av1[i])
	{
		if (av1[i] && av1[i] != ' ' && av1[i] != '\t')
			break ;
		i++;
	}
	while (av2[j])
	{
		if (av2[j] && av2[j] != ' ' && av2[j] != '\t')
			break ;
		j++;
	}
	if (ft_strlen(av2) == j || ft_strlen(av1) == i)
	{
		ft_putstr_fd("command not found\n", 2);
		exit(-1);
	}
}
