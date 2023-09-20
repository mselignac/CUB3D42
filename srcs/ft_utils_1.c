/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mseligna <mseligna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 15:52:39 by mseligna          #+#    #+#             */
/*   Updated: 2022/04/12 15:52:39 by mseligna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

static size_t	len_numb(unsigned long long n, int base)
{
	size_t	i;

	i = 0;
	while (n)
	{
		n /= base;
		i++;
	}
	return (i);
}

char	*base_convert(unsigned long long n, char *base_figures, int l)
{
	char	*res;
	int		i;
	size_t	size;

	res = NULL;
	size = len_numb(n, l);
	res = (char *)malloc(sizeof(char) * (size + 1));
	i = 1;
	while (n != 0)
	{
		res[size - i++] = base_figures[n % l];
		n /= l;
	}
	res[size] = '\0';
	return (res);
}

unsigned int	hexa_color(int r, int g, int b)
{
	return (b + (g * 256) + (r * 256 * 256));
}

unsigned int	get_r(unsigned int rgb)
{
	return (rgb / (256 * 256));
}

unsigned int	mlx_get_pixel(t_image text, int x, int y)
{
	return (*(unsigned int *)(text.addr
		+ (x * text.bbp / 8 + y * text.line_length)));
}
