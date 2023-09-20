/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mseligna <mseligna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 11:54:43 by mseligna          #+#    #+#             */
/*   Updated: 2022/04/13 11:54:44 by mseligna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

static int	get_tex_color(t_image tex, double u, double v)
{
	char			*ptr;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	ptr = tex.addr + (int)(v * tex.height) *tex.line_length
		+ (int)(u * tex.width)*(tex.bbp >> 3);
	if (tex.endian)
		r = (unsigned char)(*ptr);
	else
		r = (unsigned char)(*(ptr + 2));
	g = (unsigned char)(*(ptr + 1));
	if (tex.endian)
		b = (unsigned char)(*(ptr + 2));
	else
		b = (unsigned char)(*ptr);
	return ((r << 16) + (g << 8) + b);
}

static void	draw_init(t_data *data, t_image *text)
{
	data->vars.j = 0;
	data->vars.start = data->res_y / 2 - data->tex.line_height / 2;
	data->vars.end = data->res_y / 2 + data->tex.line_height / 2;
	if (data->tex.orientation == 'N')
		*text = data->tex.image[1];
	else if (data->tex.orientation == 'S')
		*text = data->tex.image[3];
	else if (data->tex.orientation == 'E')
		*text = data->tex.image[0];
	else if (data->tex.orientation == 'W')
		*text = data->tex.image[2];
}

static void	put_loop(t_data *data, t_image texture, int i)
{
	data->vars.color = get_tex_color(texture, data->tex.wall_x,
			((data->vars.j - data->vars.start) * 1.0)
			/ (data->vars.end - data->vars.start));
	my_mlx_pixel_put(data, i, data->vars.j++, data->vars.color);
}

void	draw_line_textured(t_data *data, int i)
{
	t_image	texture;

	draw_init(data, &texture);
	if (data->vars.start > 0)
		while (data->vars.j < data->vars.start)
			my_mlx_pixel_put(data, i, data->vars.j++, data->tex.sky_c);
	if (data->vars.end >= data->res_y)
		while (data->vars.j < data->res_y)
			put_loop(data, texture, i);
	else
		while (data->vars.j < data->vars.end)
			put_loop(data, texture, i);
	while (data->vars.j < data->res_y)
		my_mlx_pixel_put(data, i, data->vars.j++, data->tex.floor_c);
}
