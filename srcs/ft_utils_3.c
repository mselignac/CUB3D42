/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mseligna <mseligna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 15:52:55 by mseligna          #+#    #+#             */
/*   Updated: 2022/04/19 16:44:52 by mseligna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

static void	texture_init_2(t_data *data)
{
	data->tex.image[0].addr
		= mlx_get_data_addr(data->tex.image[0].img,
			&data->tex.image[0].bbp,
			&data->tex.image[0].line_length,
			&data->tex.image[0].endian);
	data->tex.image[1].addr
		= mlx_get_data_addr(data->tex.image[1].img,
			&data->tex.image[1].bbp,
			&data->tex.image[1].line_length,
			&data->tex.image[1].endian);
	data->tex.image[2].addr
		= mlx_get_data_addr(data->tex.image[2].img,
			&data->tex.image[2].bbp,
			&data->tex.image[2].line_length,
			&data->tex.image[2].endian);
	data->tex.image[3].addr
		= mlx_get_data_addr(data->tex.image[3].img,
			&data->tex.image[3].bbp,
			&data->tex.image[3].line_length,
			&data->tex.image[3].endian);
}

void	texture_init(t_data *data)
{
	if (data->tex.t[0] == NULL)
		ft_error(data, 0);
	data->tex.image[0].img = mlx_xpm_file_to_image(data->vars.mlx,
			data->tex.t[0], &(data->tex.image[0].width),
			&(data->tex.image[0].height));
	if (data->tex.image[0].img == NULL || data->tex.t[1] == NULL)
		ft_error(data, 0);
	data->tex.image[1].img = mlx_xpm_file_to_image(data->vars.mlx,
			data->tex.t[1], &(data->tex.image[1].width),
			&(data->tex.image[1].height));
	if (data->tex.image[1].img == NULL || data->tex.t[2] == NULL)
		ft_error(data, 0);
	data->tex.image[2].img = mlx_xpm_file_to_image(data->vars.mlx,
			data->tex.t[2], &(data->tex.image[2].width),
			&(data->tex.image[2].height));
	if (data->tex.image[2].img == NULL || data->tex.t[3] == NULL)
		ft_error(data, 0);
	data->tex.image[3].img = mlx_xpm_file_to_image(data->vars.mlx,
			data->tex.t[3], &(data->tex.image[3].width),
			&(data->tex.image[3].height));
	if (data->tex.image[3].img == NULL)
		ft_error(data, 0);
	texture_init_2(data);
}

int	skip_spaces(t_data *data, int n)
{
	while (data->line[n] && data->line[n] == ' ')
		n++;
	return (n);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while ((s1[i] != '\0' || s2[i] != '\0') && i < n)
	{
		if (s1[i] != s2[i] || s1[i] == '\0')
		{
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		}
		i++;
	}
	return (0);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
