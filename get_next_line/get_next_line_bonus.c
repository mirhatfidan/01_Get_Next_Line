/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfidan <mirhatfidann@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 13:10:56 by mfidan            #+#    #+#             */
/*   Updated: 2022/03/22 13:11:16 by mfidan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*ft_one_line(char *str)
{
	char	*oneline;
	int		i;

	i = 0;
	if (!str[i])
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	oneline = (char *)malloc(sizeof(char) * (i + 2));
	if (!oneline)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		oneline[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{
		oneline[i] = str[i];
		i++;
	}
	oneline[i] = '\0';
	return (oneline);
}

static char	*ft_remain(char *str)
{
	char	*remain;
	int		i;
	int		j;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
	{
		free(str);
		return (NULL);
	}
	remain = (char *)malloc(sizeof(char) * (ft_strlen(str) - i));
	if (!remain)
		return (NULL);
	i++;
	j = 0;
	while (str[i])
		remain[j++] = str[i++];
	remain[j] = '\0';
	free(str);
	return (remain);
}

static char	*ft_read_file(char *str, int fd)
{
	char	*buff;
	int		cont;

	cont = 1;
	buff = (char *)malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	while (!ft_strchr(str, '\n') && cont != 0)
	{
		cont = read(fd, buff, BUFFER_SIZE);
		if (cont == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[cont] = '\0';
		str = ft_strjoin(str, buff);
	}
	free(buff);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*str[4096];
	char		*oneline;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	str[fd] = ft_read_file(str[fd], fd);
	if (!str[fd])
		return (NULL);
	oneline = ft_one_line(str[fd]);
	str[fd] = ft_remain(str[fd]);
	return (oneline);
}
