/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mseligna <mseligna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 15:52:27 by mseligna          #+#    #+#             */
/*   Updated: 2022/04/12 15:52:27 by mseligna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

void	last_check(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (data->map[++i])
	{
		j = -1;
		while (data->map[i][++j])
		{
			if (data->map[i][j] == '0')
			{
				if (i == 0 || i == data->vars.size_map
					|| j == 0 || j == (int)data->vars.size_line_max - 1)
					ft_error(data, 2);
				if (data->map[i][j + 1] != '0' && data->map[i][j + 1] != '1')
					ft_error(data, 2);
				if (data->map[i][j - 1] != '0' && data->map[i][j - 1] != '1')
					ft_error(data, 2);
				if (data->map[i + 1][j] != '0' && data->map[i + 1][j] != '1')
					ft_error(data, 2);
				if (data->map[i - 1][j] != '0' && data->map[i - 1][j] != '1')
					ft_error(data, 2);
			}
		}
	}
}

void	ft_error(t_data *data, int code)
{
	write(2, "Error\n", 6);
	if (code == -1)
		write(2, "Invalid file\n", 14);
	else if (code == 0)
		write(2, "Invalid configuration\n", 22);
	else if (code == -2)
		write (1, "Wrong type of file, must be .cub\n", 34);
	else
	{
		close(data->fd);
		if (code == 1)
			write(2, "Invalid configuration\n", 22);
		if (code == 2)
			write(2, "Invalid map\n", 13);
		if (code == 3)
			write(2, "Memory allocation failed\n", 25);
	}
	ft_free(data);
}

static void	ft_free_2(t_data *data)
{
	if (data->depth_buffer)
		free(data->depth_buffer);
	if (data->tex.image[0].img != NULL)
		mlx_destroy_image(data->vars.mlx, data->tex.image[0].img);
	if (data->tex.image[1].img != NULL)
		mlx_destroy_image(data->vars.mlx, data->tex.image[1].img);
	if (data->tex.image[2].img != NULL)
		mlx_destroy_image(data->vars.mlx, data->tex.image[2].img);
	if (data->tex.image[3].img != NULL)
		mlx_destroy_image(data->vars.mlx, data->tex.image[3].img);
	if (data->img != 0)
		mlx_destroy_image(data->vars.mlx, data->img);
	if (data->check.init_done)
		mlx_destroy_window(data->vars.mlx, data->vars.win);
	if (data->vars.mlx)
	{
		mlx_destroy_display(data->vars.mlx);
		mlx_loop_end(&data->vars);
		free(data->vars.mlx);
	}
}

int	ft_free(t_data *data)
{
	int	i;

	i = 0;
	if (data->line != NULL)
		free(data->line);
	if (data->tex.t[0] != NULL)
		free(data->tex.t[0]);
	if (data->tex.t[1] != NULL)
		free(data->tex.t[1]);
	if (data->tex.t[2] != NULL)
		free(data->tex.t[2]);
	if (data->tex.t[3] != NULL)
		free(data->tex.t[3]);
	if (data->map != NULL)
	{
		while (data->map[i] != NULL)
		{
			free(data->map[i]);
			i++;
		}
		free(data->map);
	}
	ft_free_2(data);
	exit(EXIT_SUCCESS);
}
