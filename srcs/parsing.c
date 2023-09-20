/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mseligna <mseligna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 15:53:38 by mseligna          #+#    #+#             */
/*   Updated: 2022/04/12 15:53:38 by mseligna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

static void	get_colors_2(t_data *data, int *tmp, int k, int *j)
{
	if (*tmp > 255)
		data->error = 1;
	if (k == 0)
		data->tex.r = *tmp;
	if (k == 1)
		data->tex.g = *tmp;
	if (k == 2)
		data->tex.b = *tmp;
	*j = 0;
	*tmp = 0;
}

static void	get_tmp(t_data *data, int *i, int *tmp, int *j)
{
	while (data->line[*i] >= '0' && data->line[*i] <= '9')
	{
		*tmp = (*tmp * 10) + (data->line[*i] - '0');
		(*i)++;
		(*j)++;
	}
}

static void	check_err(t_data *data, int i, int j, int k)
{
	if (((j > 3 || j == 0) || (data->line[i] != ',' && k < 2))
		|| (k == 2 && data->line[i] != '\0'))
			data->error = 1;
}

static unsigned int	get_colors(t_data *data, int i)
{
	int	tmp;
	int	j;
	int	k;

	j = 0;
	k = 0;
	tmp = 0;
	if (data->line[1] && data->line[1] != ' ')
		data->error = 1;
	while (data->line[i])
	{
		if (k == 3)
			break ;
		i = skip_spaces(data, i);
		get_tmp(data, &i, &tmp, &j);
		i = skip_spaces(data, i);
		check_err(data, i, j, k);
		get_colors_2(data, &tmp, k, &j);
		if (data->line[i] == ',')
			i++;
		k++;
	}
	if (k < 3)
		data->error = 1;
	return (hexa_color(data->tex.r, data->tex.g, data->tex.b));
}

void	ft_file_read(t_data *data, int i)
{
	while (i < 7)
	{
		skip_lines(data);
		if (!(ft_strncmp("NO", data->line, 2)) && data->tex.t[1] == NULL)
			data->tex.t[1] = get_tex(data, skip_spaces(data, 2));
		else if (!(ft_strncmp("SO", data->line, 2)) && data->tex.t[3] == NULL)
			data->tex.t[3] = get_tex(data, skip_spaces(data, 2));
		else if (!(ft_strncmp("WE", data->line, 2)) && data->tex.t[2] == NULL)
			data->tex.t[2] = get_tex(data, skip_spaces(data, 2));
		else if (!(ft_strncmp("EA", data->line, 2)) && data->tex.t[0] == NULL)
			data->tex.t[0] = get_tex(data, skip_spaces(data, 2));
		else if (!(ft_strncmp("F", data->line, 1)) && data->tex.floor_c == 0
			&& ft_strlen(data->line) > 2)
			data->tex.floor_c = get_colors(data, 2);
		else if (!(ft_strncmp("C", data->line, 1)) && data->tex.sky_c == 0
			&& ft_strlen(data->line) > 2)
			data->tex.sky_c = get_colors(data, 2);
		else if (i < 6)
			data->error = 1;
		i++;
		if (data->line != NULL && i < 7)
			free(data->line);
	}
	not_null(data);
}
