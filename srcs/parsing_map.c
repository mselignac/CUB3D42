/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mseligna <mseligna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 15:53:33 by mseligna          #+#    #+#             */
/*   Updated: 2022/04/12 15:53:33 by mseligna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

static int	copy_map_2(t_data *data, int i, char **tmp_map)
{
	int	j;

	j = 0;
	while (data->map[i][j])
	{
		if (data->map[i][j] == 'N' || data->map[i][j] == 'S'
		|| data->map[i][j] == 'W' || data->map[i][j] == 'E')
		{
			data->check.s_pos_i = i;
			data->check.s_pos_j = j;
			data->check.s_direction = data->map[i][j];
			data->map[i][j] = '0';
			tmp_map[i][j] = '0';
		}
		else
			tmp_map[i][j] = data->map[i][j];
		j++;
	}
	while (j < (int)data->vars.size_line_max)
	{
		tmp_map[i][j] = ' ';
		j++;
	}
	return (j);
}

static char	**copy_map(t_data *data)
{
	char	**tmp_map;
	int		i;
	int		j;

	i = 0;
	tmp_map = malloc(sizeof(char *) * (data->vars.size_map + 2));
	if (!tmp_map)
		ft_error(data, 3);
	while (data->map[i] != NULL)
	{
		tmp_map[i] = NULL;
		tmp_map[i] = malloc(sizeof(char) * (data->vars.size_line_max + 1));
		if (!(tmp_map[i]))
		{
			free_tab(tmp_map);
			ft_error(data, 3);
		}
		j = copy_map_2(data, i, tmp_map);
		tmp_map[i][j] = '\0';
		i++;
	}
	tmp_map[i] = NULL;
	return (tmp_map);
}

void	secure_map(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == ' ')
				data->map[i][j] = '1';
			j++;
		}
		i++;
	}
}

void	check_map(t_data *data)
{
	char	**tmp;
	int		i;

	i = 0;
	tmp = copy_map(data);
	while (tmp[i])
		free(tmp[i++]);
	free(tmp);
	last_check(data);
	if (data->check.s_pos_i == 0 && data->check.s_pos_j == 0)
		ft_error(data, 2);
	if (data->error == 0)
		secure_map(data);
}
