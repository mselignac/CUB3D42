/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mseligna <mseligna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 15:53:25 by mseligna          #+#    #+#             */
/*   Updated: 2022/04/22 16:02:19 by mseligna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

static int	parse_map_2(t_data *data, int i)
{
	int	j;

	j = 0;
	while (data->line[j])
	{
		if ((data->line[j] == ' ' || data->line[j] == '1') && data->error != 1
			&& j < (int)data->vars.size_line_max)
			data->map[i][j] = data->line[j];
		else if (data->line[j] == '0' && data->error != 1)
			data->map[i][j] = '0';
		else if ((data->line[j] == 'N' || data->line[j] == 'S'
				|| data->line[j] == 'W' || data->line[j] == 'E')
			&& !data->error)
		{
			data->player++;
			data->cam_dir = data->line[j];
			data->map[i][j] = data->line[j];
		}
		else
			data->error = 1;
		j++;
	}
	return (j);
}

void	parse_map(t_data *data)
{
	int				i;
	unsigned int	j;
	int				ret;

	i = 0;
	ret = 1;
	while (ret != 0)
	{
		ret = get_next_line(data->fd, &data->line);
		data->map[i] = malloc(sizeof(char) * (data->vars.size_line_max + 1));
		if (!(data->map[i]))
			ft_error(data, 3);
		j = parse_map_2(data, i);
		while (j < data->vars.size_line_max)
			data->map[i][j++] = ' ';
		if (!data->error)
			data->map[i][j] = '\0';
		free(data->line);
		data->line = NULL;
		i++;
	}
	data->map[i] = NULL;
	if (data->error || data->player != 1)
		ft_error(data, 2);
}

static void	count_line_2(t_data *data, int i)
{
	while (i <= 5 + data->skip)
	{
		get_next_line(data->fd, &data->line);
		i++;
		free(data->line);
	}
}

void	count_line(t_data *data, char *file_name)
{
	int		i;
	int		ret;

	i = 0;
	ret = 1;
	while (ret != 0)
	{
		if (data->vars.size_line_max < ft_strlen(data->line))
			data->vars.size_line_max = ft_strlen(data->line);
		data->vars.size_map++;
		free(data->line);
		ret = get_next_line(data->fd, &data->line);
	}
	free(data->line);
	data->line = NULL;
	if (data->error)
		ft_error(data, 1);
	close(data->fd);
	data->map = malloc(sizeof(char *) * (data->vars.size_map + 2));
	if (!data->map)
		ft_error(data, 2);
	data->fd = open(file_name, O_RDONLY);
	if (data->fd == -1)
		ft_error(data, 1);
	count_line_2(data, i);
}

char	*get_tex(t_data *data, int s)
{
	return (ft_substr(data->line, s, ft_strlen(data->line) - s));
}
