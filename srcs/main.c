/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mseligna <mseligna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 15:53:19 by mseligna          #+#    #+#             */
/*   Updated: 2022/04/12 15:53:19 by mseligna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

static void	vars_init_2(t_data *data)
{
	data->tex.image[0].img = NULL;
	data->tex.image[1].img = NULL;
	data->tex.image[2].img = NULL;
	data->tex.image[3].img = NULL;
	data->tex.t[0] = NULL;
	data->tex.t[1] = NULL;
	data->tex.t[2] = NULL;
	data->tex.t[3] = NULL;
	data->img = NULL;
	data->depth_buffer = NULL;
	data->vars.win = NULL;
	data->line = NULL;
	data->error = 0;
	data->skip = 0;
	data->res_x = 1000;
	data->res_y = 800;
	data->player = 0;
	data->input.forward = 0;
	data->input.back = 0;
	data->input.left = 0;
	data->input.right = 0;
	data->input.r_left = 0;
	data->input.r_right = 0;
}

static void	vars_init(t_data *data, char *argv)
{
	data->map = NULL;
	data->check.start_pos = 0;
	data->vars.size_line_max = 0;
	data->vars.size_map = 0;
	data->res_x = 0;
	data->res_y = 0;
	data->tex.r = 0;
	data->tex.g = 0;
	data->tex.b = 0;
	data->tex.floor_c = 0;
	data->tex.sky_c = 0;
	data->check.init_done = 0;
	data->check.s_pos_i = 0;
	data->check.s_pos_j = 0;
	data->check.s_direction = 0;
	vars_init_2(data);
	if (argv[ft_strlen(argv) - 1] != 'b'
		|| argv[ft_strlen(argv) - 2] != 'u'
		|| argv[ft_strlen(argv) - 3] != 'c'
		|| argv[ft_strlen(argv) - 4] != '.')
		ft_error(data, -2);
}

static void	direction_init(t_data *data)
{
	if (data->check.s_direction == 'N')
		data->check.pos_a = M_PI / 2;
	if (data->check.s_direction == 'S')
		data->check.pos_a = 3 * M_PI / 2;
	if (data->check.s_direction == 'E')
		data->check.pos_a = 0;
	if (data->check.s_direction == 'W')
		data->check.pos_a = M_PI;
}

static void	steps(t_data *data, char *argv)
{
	int	i;

	i = 0;
	ft_file_read(data, i);
	count_line(data, argv);
	parse_map(data);
	close(data->fd);
	check_empty(data);
	check_map(data);
	last_check(data);
	direction_init(data);
	texture_init(data);
	cam_init(data);
	input_loop(data);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
	{
		write (1, "Wrong number of arguments\n", 27);
		return (0);
	}
	data.vars.mlx = mlx_init();
	if (!data.vars.mlx)
	{
		write(2, "mlx pointer does not exist\n", 27);
		return (0);
	}
	vars_init(&data, argv[1]);
	data.fd = open(argv[1], O_RDONLY | O_DIRECTORY);
	if (data.fd != -1)
	{
		close(data.fd);
		ft_error(&data, -1);
	}
	data.fd = open(argv[1], O_RDONLY);
	if (data.fd == -1)
		ft_error(&data, -1);
	steps(&data, argv[1]);
	return (0);
}
