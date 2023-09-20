/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mseligna <mseligna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 15:53:13 by mseligna          #+#    #+#             */
/*   Updated: 2022/04/12 15:53:13 by mseligna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

static int	key_pressed(int keycode, t_data *data)
{
	if (keycode == 65307)
		ft_free(data);
	if (keycode == FORWARD)
		data->input.forward = 1;
	if (keycode == BACK)
		data->input.back = 1;
	if (keycode == LEFT)
		data->input.left = 1;
	if (keycode == RIGHT)
		data->input.right = 1;
	if (keycode == ROTATE_LEFT)
		data->input.r_left = 1;
	if (keycode == ROTATE_RIGHT)
		data->input.r_right = 1;
	return (0);
}

static int	key_released(int keycode, t_data *data)
{
	if (keycode == FORWARD)
		data->input.forward = 0;
	if (keycode == BACK)
		data->input.back = 0;
	if (keycode == LEFT)
		data->input.left = 0;
	if (keycode == RIGHT)
		data->input.right = 0;
	if (keycode == ROTATE_LEFT)
		data->input.r_left = 0;
	if (keycode == ROTATE_RIGHT)
		data->input.r_right = 0;
	return (0);
}

void	ft_fill_norm(t_data *data, char **frame, int i, int j)
{
	if (i == 0 || i == data->vars.size_map
		|| j == 0 || j == (int)data->vars.size_line_max - 1)
	{
		free_tab(frame);
		ft_error(data, 0);
	}
}

int	is_input(t_data *data)
{
	if (data->input.forward || data->input.back || data->input.left
		|| data->input.right || data->input.r_left || data->input.r_right)
		return (1);
	return (0);
}

void	input_loop(t_data *data)
{
	win_init(data);
	data->check.init_done = 1;
	data->vars.win = mlx_new_window(data->vars.mlx, data->res_x, data->res_y,
			"tHe BIndInG oF iSaAC : ANTiBIrtH");
	raycasting(data);
	mlx_put_image_to_window(data->vars.mlx, data->vars.win, data->img, 0, 0);
	mlx_loop_hook(data->vars.mlx, win_refresh, data);
	mlx_hook(data->vars.win, 33, 1L << 17, ft_free, data);
	mlx_hook(data->vars.win, 2, 1L << 0, key_pressed, data);
	mlx_hook(data->vars.win, 3, 1L << 1, key_released, data);
	mlx_loop(data->vars.mlx);
}
