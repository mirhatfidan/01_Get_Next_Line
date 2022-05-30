/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfidan <mfidan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 13:05:48 by mfidan            #+#    #+#             */
/*   Updated: 2022/03/24 11:58:39 by mfidan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	int		len;
	char	*ptr;

	if (!s1)
	{
		s1 = (char *)malloc(1 * sizeof(char));
		s1[0] = '\0';
	}
	if (!s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	ptr = (char *)malloc(sizeof(char) * len + 1);
	if (!ptr)
		return (NULL);
	j = 0;
	i = -1;
	while (s1[++i])
		ptr[i] = s1[i];
	while (s2[j])
		ptr[i++] = s2[j++];
	ptr[i] = '\0';
	free(s1);
	return (ptr);
}

char	*ft_strchr(char *s, int c)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i++;
	}
	return (NULL);
}

size_t	ft_strlen(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

//Okunan dosyanın 1. satırını yeni dizi üretim içerisine yazar
static char	*ft_one_line(char *str)
{
	char	*oneline;
	int		i;

	i = 0;
	if (!str[i])
		return (NULL);

	// \n görene kadar 1. satırdaki karakterleri sayar
	while (str[i] && str[i] != '\n')
		i++;

	// \n ve NULL icin iki tane fazla yer ayırır.
	oneline = (char *)malloc(sizeof(char) * (i + 2));
	if (!oneline)
		return (NULL);
	i = 0;

	//yeni oluşturulan dizinin 0. indisinden itibaren içerisine yazmaya başlar
	while (str[i] && str[i] != '\n')
	{
		oneline[i] = str[i];
		i++;
	}

	// 1. satırın son elemanına geldiyse girer ve sonuna \n koyar
	if (str[i] == '\n')
	{
		oneline[i] = str[i];
		i++;
	}
	//dizinin sonuna NULL koyar
	oneline[i] = '\0';
	//1. satırı geri döner
	return (oneline);
}
//bir sonraki satıra gecer.
static char	*ft_remain(char *str)
{
	char	*remain;
	int		i;
	int		j;

	i = 0;

	// satırdaki dizinin eleman sayısını sayar
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

	//1. satırın boyutundan itibaren yenidiziye atar.
	//dizi 3 elenanlı ise 4. elemndan itibaren yeni diziye atar
	while (str[i])
		remain[j++] = str[i++];
	remain[j] = '\0';
	free(str);
	return (remain);
}

//dosya oku
//dosyadaki okudugu karakterleri geri döner
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
//Ana fonksiyon
char	*get_next_line(int fd)
{
	static char	*str;
	char		*oneline;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	//Dosyadaki bütün satırları okur
	str = ft_read_file(str, fd);
	if (!str)
		return (NULL);
	//1. satırı geri göner
	oneline = ft_one_line(str);
	//1. satırı diziden çıkarır. 2. satıra geçer
	str = ft_remain(str);
	//oluşturulan 1. diziyi geri döner
	return (oneline);
}

#include <stdio.h>
#include <fcntl.h>
int	main(void)
{
	char	*line;
	int		i;
	int		fd1;

	fd1 = open("metin.txt", O_RDONLY);

	i = 1;
	while (i <= 5)
	{
		line = get_next_line(fd1);
		printf("line [%02d]: %s", i, line);
		free(line);
		i++;
	}
	close(fd1);

	return (0);
}
