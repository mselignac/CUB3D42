/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mseligna <mseligna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 15:53:58 by mseligna          #+#    #+#             */
/*   Updated: 2022/04/12 15:53:58 by mseligna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

static void	init_vars(t_data *data, double ray[2])
{
	data->ray_vars.delta_dist[0] = fabs(1.0 / ray[0]);
	data->ray_vars.delta_dist[1] = fabs(1.0 / ray[1]);
	data->ray_vars.map_pos[0] = floor(data->check.pos_i);
	data->ray_vars.map_pos[1] = floor(data->check.pos_j);
	if (ray[0] < 0)
		data->ray_vars.step[0] = -1;
	else
		data->ray_vars.step[0] = 1;
	if (ray[1] < 0)
		data->ray_vars.step[1] = -1;
	else
		data->ray_vars.step[1] = 1;
	if (ray[0] < 0)
		data->ray_vars.side_dist[0] = (data->check.pos_i
				- data->ray_vars.map_pos[0]) * data->ray_vars.delta_dist[0];
	else
		data->ray_vars.side_dist[0] = (data->ray_vars.map_pos[0] + 1.0
				- data->check.pos_i) * data->ray_vars.delta_dist[0];
	if (ray[1] < 0)
		data->ray_vars.side_dist[1] = (data->check.pos_j
				- data->ray_vars.map_pos[1]) * data->ray_vars.delta_dist[1];
	else
		data->ray_vars.side_dist[1] = (data->ray_vars.map_pos[1] + 1.0
				- data->check.pos_j) * data->ray_vars.delta_dist[1];
}

static int	check_hit(t_data *data, double ray[2])
{
	if (data->ray_vars.side_dist[0] < data->ray_vars.side_dist[1])
	{
		data->ray_vars.side_dist[0] += data->ray_vars.delta_dist[0];
		data->ray_vars.map_pos[0] += data->ray_vars.step[0];
		if (ray[0] > 0)
			data->tex.orientation = 'N';
		else
			data->tex.orientation = 'S';
	}
	else
	{
		data->ray_vars.side_dist[1] += data->ray_vars.delta_dist[1];
		data->ray_vars.map_pos[1] += data->ray_vars.step[1];
		if (ray[1] > 0)
			data->tex.orientation = 'E';
		else
			data->tex.orientation = 'W';
	}
	return (data->map[data->ray_vars.map_pos[0]]
		[data->ray_vars.map_pos[1]] == '1');
}

void	run_dda(t_data *data, int i, double ray[2])
{
	int	hit;

	init_vars(data, ray);
	hit = 0;
	while (!hit)
		hit = check_hit(data, ray);
	if (data->tex.orientation == 'N' || data->tex.orientation == 'S')
		data->tex.wall_dist = (data->ray_vars.map_pos[0] - data->check.pos_i
				+ (1 - data->ray_vars.step[0]) / 2) / ray[0];
	else
		data->tex.wall_dist = (data->ray_vars.map_pos[1] - data->check.pos_j
				+ (1 - data->ray_vars.step[1]) / 2) / ray[1];
	data->depth_buffer[i] = data->tex.wall_dist;
	if (data->tex.orientation == 'N' || data->tex.orientation == 'S')
		data->tex.wall_x = data->check.pos_j
			+ data->tex.wall_dist * ray[1];
	else
		data->tex.wall_x = data->check.pos_i
			+ data->tex.wall_dist * ray[0];
	data->tex.wall_x -= floor(data->tex.wall_x);
	if (data->tex.wall_dist > 0)
		data->tex.line_height = data->res_y / data->tex.wall_dist;
	else
		data->tex.line_height = 2147483647;
	draw_line_textured(data, i);
}

void	raycasting(t_data *data)
{
	int		i;
	double	camera_x;
	double	ray[2];

	i = 0;
	while (i < data->res_x)
	{
		camera_x = 2.0 * i / data->res_x - 1;
		ray[0] = data->dir[0] + data->cam_plane[0] * camera_x;
		ray[1] = data->dir[1] + data->cam_plane[1] * camera_x;
		run_dda(data, i, ray);
		i++;
	}
}
