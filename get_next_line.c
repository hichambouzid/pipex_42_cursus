/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibouzid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 14:51:10 by hibouzid          #+#    #+#             */
/*   Updated: 2024/03/15 16:45:37 by hibouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

char	*get_read(char *ptr, int fd)
{
	int		i;
	char	*str;

	i = 1;
	str = malloc(sizeof(char) * (BUFFER_SIZE) + 1);
	if (!str)
		return (NULL);
	str[0] = 0;
	while (ft_check(str, '\n') == -1 && i != 0)
	{
		i = read(fd, str, BUFFER_SIZE);
		if (i < 0)
		{
			free(str);
			free(ptr);
			return (NULL);
		}
		str[i] = 0;
		ptr = ft_strjoin(ptr, str);
		if (i == 0)
			exit(-1);
	}
	free(str);
	return (ptr);
}

char	*ft_cut(char *ptr)
{
	int		i;
	char	*str;

	i = 0;
	str = NULL;
	if (!ptr)
		return (NULL);
	while (ptr[i] && ptr[i] != '\n')
		i++;
	if (ptr[i] == '\n')
		i++;
	if (!ptr[i])
	{
		free(ptr);
		return (NULL);
	}
	str = ft_strdup(ptr + i);
	free(ptr);
	return (str);
}

char	*ft_line(char *ptr)
{
	int		i;
	char	*str;

	i = 0;
	if (!ptr)
		return (NULL);
	while (ptr[i] && ptr[i] != '\n')
		i++;
	if (i == 0 && !ptr[0])
		return (NULL);
	if (ptr[i] == '\n')
		i++;
	str = malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (ptr[i] && ptr[i] != '\n')
	{
		str[i] = ptr[i];
		i++;
	}
	if (ptr[i] != 0)
		str[i++] = '\n';
	str[i] = 0;
	return (ft_freee(str, ptr));
}

char	*get_next_line(int fd)
{
	static char	*ptr;
	char		*str;
	char		*tmp;

	tmp = 0;
	str = 0;
	if (fd == -1 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!ptr)
	{
		ptr = ft_strdup("");
		tmp = ptr;
	}
	if (ptr)
	{
		ptr = get_read(ptr, fd);
		str = ft_line(ptr);
		ptr = ft_cut(ptr);
	}
	if (tmp)
		free(tmp);
	free(ptr);
	return (str);
}
