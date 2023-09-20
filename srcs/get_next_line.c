/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mseligna <mseligna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 15:53:07 by mseligna          #+#    #+#             */
/*   Updated: 2022/04/12 15:53:07 by mseligna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

char	*clean_line(char *save, char **line)
{
	char			*tmp;
	size_t			i;

	i = 0;
	while (save[i] && save[i] != '\n')
		i++;
	if (save[i] == '\n')
	{
		*line = ft_substr(save, 0, i);
		tmp = ft_strdup(save + i + 1);
		free(save);
		save = tmp;
	}
	else if (save[i] == '\0')
	{
		*line = ft_strdup(save);
		free(save);
		save = NULL;
	}
	return (save);
}

char	*ft_save(char *buffer, char *save)
{
	char			*tmp;

	if (save)
	{
		tmp = ft_strjoin(save, buffer);
		free(save);
		save = NULL;
		save = ft_strdup(tmp);
		free(tmp);
		tmp = NULL;
	}
	else
		save = ft_strdup(buffer);
	return (save);
}

static int	get_next_line_2(char **line, char **save_red, int fd)
{
	*line = ft_strdup("");
	free(save_red[fd]);
	save_red[fd] = NULL;
	return (0);
}

int	get_next_line(int fd, char **line)
{
	static char		*save_red[4096];
	int				r_return;
	char			buffer[BUFFER_SIZE + 1];

	r_return = 1;
	if (fd < 0 || BUFFER_SIZE < 1 || line == NULL || read(fd, buffer, 0) < 0)
		return (-1);
	while (r_return > 0)
	{
		r_return = read(fd, buffer, BUFFER_SIZE);
		if (r_return < 0)
			return (-1);
		buffer[r_return] = '\0';
		save_red[fd] = ft_save(buffer, save_red[fd]);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	if (save_red[fd] == 0)
		get_next_line_2(line, &save_red[fd], fd);
	save_red[fd] = clean_line(save_red[fd], line);
	if (save_red[fd] == 0 && r_return <= 0)
		return (r_return);
	return (1);
}
