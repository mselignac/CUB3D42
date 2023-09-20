/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mseligna <mseligna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 15:54:03 by mseligna          #+#    #+#             */
/*   Updated: 2022/04/12 15:54:03 by mseligna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

static void	cam_init_2(t_data *data)
{
	if (data->cam_dir == 'S')
	{
		data->dir[0] = 1;
		data->cam_plane[1] = -0.66;
	}
	else
	{
		data->dir[0] = -1;
		data->cam_plane[1] = 0.66;
	}
	data->dir[1] = 0;
	data->cam_plane[0] = 0;
}

void	cam_init(t_data *data)
{
	if (data->cam_dir == 'E' || data->cam_dir == 'W')
	{
		data->dir[0] = 0;
		if (data->cam_dir == 'E')
		{
			data->dir[1] = 1;
			data->cam_plane[0] = 0.66;
		}
		else
		{
			data->dir[1] = -1;
			data->cam_plane[0] = -0.66;
		}
		data->cam_plane[1] = 0;
	}
	else
		cam_init_2(data);
}

int	win_refresh(t_data *data)
{
	if (is_input(data))
	{
		if (data->input.forward)
			move_player(data, -2, 1);
		if (data->input.back)
			move_player(data, 2, 1);
		if (data->input.left)
			move_player(data, -2, 2);
		if (data->input.right)
			move_player(data, 2, 2);
		if (data->input.r_left)
			rotate_player(data, 1);
		if (data->input.r_right)
			rotate_player(data, -1);
		if (data->img != 0)
			mlx_destroy_image(data->vars.mlx, data->img);
		data->img = mlx_new_image(data->vars.mlx,
				data->res_x, data->res_y);
		data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
				&data->line_length, &data->endian);
		raycasting(data);
		mlx_put_image_to_window(data->vars.mlx,
			data->vars.win, data->img, 0, 0);
	}
	return (0);
}

void	win_init(t_data *data)
{
	data->depth_buffer = ft_calloc(data->res_x, sizeof(double));
	data->img = mlx_new_image(data->vars.mlx, data->res_x, data->res_y);
	data->addr = mlx_get_data_addr(data->img,
			&data->bits_per_pixel, &data->line_length, &data->endian);
	if (data->check.init_done == 0)
	{
		data->check.pos_i = data->check.s_pos_i + 0.5;
		data->check.pos_j = data->check.s_pos_j + 0.5;
	}
}
