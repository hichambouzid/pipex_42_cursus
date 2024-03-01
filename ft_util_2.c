/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_util_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibouzid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:11:24 by hibouzid          #+#    #+#             */
/*   Updated: 2024/02/29 16:14:06 by hibouzid         ###   ########.fr       */
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

char	*ft_get_read_all(int fd)
{
	char	*str;
	char	*tmp;
	char	*v;
	int		i;

	tmp = malloc(sizeof(char) * SIZE_M);
	if (!tmp)
		return (NULL);
	str = 0;
	while (1)
	{
		i = read(fd, tmp, SIZE_M);
		tmp[i] = 0;
		if (i == 0)
		{
			free(tmp);
			return (str);
		}
		else if (i > 0)
		{
			v = str;
			str = ft_strjoin(str, tmp);
			if (v)
				free(v);
		}
	}
	return (NULL);
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

