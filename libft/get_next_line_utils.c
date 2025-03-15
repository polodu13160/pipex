/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 18:37:39 by pauldepetri       #+#    #+#             */
/*   Updated: 2025/02/11 16:48:37 by pde-petr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

int	size_char_in_text(char *text, int ascii)
{
	int	i;

	i = 0;
	if (ascii == 0)
	{
		while (text[i])
			i++;
		return (i);
	}
	while (text[i] == ascii)
		i++;
	return (i);
}

char	*ft_charjoin(char *buf, char *malloc_tamp, size_t i)
{
	char	*malloc_join;
	size_t	j;

	j = 0;
	malloc_join = NULL;
	if (!malloc_tamp)
		malloc_join = malloc(2);
	else
		malloc_join = malloc(size_char_in_text(malloc_tamp, 0) + 2);
	if (!malloc_join)
	{
		free(malloc_tamp);
		return (NULL);
	}
	while (malloc_tamp && malloc_tamp[j])
	{
		malloc_join[j] = malloc_tamp[j];
		j++;
	}
	malloc_join[j++] = buf[i];
	if (buf[i] != '\n')
		buf[i] = 127;
	malloc_join[j] = '\0';
	free(malloc_tamp);
	return (malloc_join);
}

char	*line_by_line(char *buf, size_t i, int fd, char *malloc_tamp)
{
	int	rd;

	rd = -2;
	if (!buf[i])
		rd = read(fd, buf, BUFFER_SIZE);
	if (rd == -1)
	{
		free(malloc_tamp);
		return (NULL);
	}
	if (rd == 0)
		return (malloc_tamp);
	i = size_char_in_text(buf, 127);
	while (buf[i] && buf[i] != 127)
	{
		malloc_tamp = ft_charjoin(buf, malloc_tamp, i);
		if (malloc_tamp == NULL)
			return (NULL);
		if (buf[i++] == '\n')
		{
			buf[--i] = 127;
			return (malloc_tamp);
		}
	}
	return (line_by_line(buf, i, fd, malloc_tamp));
}
