/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conguyen <conguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 17:05:21 by conguyen          #+#    #+#             */
/*   Updated: 2021/12/07 09:06:31 by conguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_get_line(char **saved, char **line, int ret)
{
	int		c;
	char	*temp;

	if (ret == 0 && *saved == NULL)
		return (0);
	c = 0;
	while ((*saved)[c] != '\0' && (*saved)[c] != '\n')
		c++;
	if ((*saved)[c] == '\n')
	{
		*line = ft_strsub(*saved, 0, c);
		temp = ft_strdup(&((*saved)[c + 1]));
		free(*saved);
		*saved = temp;
	}
	else
	{
		*line = ft_strdup(*saved);
		ft_strdel(saved);
		return (0);
	}
	return (1);
}

static int	ft_save_buffer(char *buf, char **line, int ret, int fd)
{
	char		*temp;
	static char	*saved[MAX_FD];

	while (ret)
	{
		ret = read(fd, buf, BUFF_SIZE);
		if (ret < 0)
			return (-1);
		buf[ret] = '\0';
		if (saved[fd] != NULL)
		{
			temp = ft_strjoin(saved[fd], buf);
			free(saved[fd]);
			saved[fd] = temp;
		}
		else
			saved[fd] = ft_strdup(buf);
		if (ft_strchr(saved[fd], '\n') != NULL)
			break ;
	}
	return (ft_get_line(&saved[fd], line, ret));
}

int	get_next_line(const int fd, char **line)
{
	char		buf[BUFF_SIZE + 1];
	int			ret;

	if (fd < 0 || line == NULL || BUFF_SIZE <= 0)
		return (-1);
	ret = 1;
	return (ft_save_buffer(buf, line, ret, fd));
}
