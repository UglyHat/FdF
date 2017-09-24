/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpagot <rpagot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 16:08:32 by rpagot            #+#    #+#             */
/*   Updated: 2017/09/24 16:27:53 by rpagot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static	void				ft_set_pointsx(t_map *map)
{
	map->x1 = map->xn * map->widthx - map->yn * map->widthx;
	map->y1 = map->widthx * map->yn + map->xn * map->widthx
		- map->data[map->xn + (map->yn - 1) * map->sizex - 1] * 4;
	printf("%d\n", map->xn + (map->yn - 1) * (map->sizex));
	map->x2 = (map->xn + 1) * map->widthx - map->yn * map->widthx;
	map->y2 = map->widthx * map->yn + (map->xn + 1) * map->widthx 
		- map->data[map->xn + (map->yn - 1) * map->sizex] * 4;
}

static	void				ft_set_pointsy(t_map *map)
{
	map->x1 = map->xn * map->widthx - map->yn * map->widthx;
	printf("%d\n", map->xn + (map->yn) * (map->sizex) - 1);
	map->y1 = map->widthx * map->yn + map->xn * map->widthx - map->data[map->xn + (map->yn - 1) * map->sizex - 1] * 4;
	map->x2 = map->xn * map->widthx - (map->yn + 1) * map->widthx;
	map->y2 = map->widthx * (map->yn + 1) + map->xn * map->widthx - map->data[map->xn + map->yn * map->sizex - 1] * 4;
}

static	void				ft_draw_line(t_map *map)
{
	int		*addr;

	addr = (int *)map->addr;
	map->mx = abs(map->x2 - map->x1);
	map->my = -abs(map->y2 - map->y1);
	map->signx = map->x1 < map->x2 ? 1 : -1;
	map->signy = map->y1 < map->y2 ? 1 : -1;
	map->d = map->mx + map->my;
	while (map->x1 + map->y1 * map->width < map->width * map->length * 2)
	{
		addr[map->x1 + map->y1 * map->width * 2 - map->width] = 0x00FFFFFF;
		if (map->x1 + map->y1 * map->width == map->x2 + map->y2 * map->width)
			break ;
		map->d2 = map->d * 2;
		if (map->d2 >= map->my)
		{
			map->d += map->my;
			map->x1 += map->signx;
		}
		if (map->d2 <= map->mx)
		{
			map->d += map->mx;
			map->y1 += map->signy;
		}
	}
}

static	void				ft_draw_grid(t_map *map)
{
	while (map->yn < map->sizey + 1)
	{
		while (map->xn < map->sizex)
		{
			ft_set_pointsx(map);
			ft_draw_line(map);
			map->xn++;
		}
		map->xn = 1;
		map->yn++;
	}
	map->yn = 1;
	while (map->xn < map->sizex + 1)
	{
		while (map->yn < map->sizey)
		{
			ft_set_pointsy(map);
			ft_draw_line(map);
			map->yn++;
		}
		map->yn = 1;
		map->xn++;
	}
}

void						ft_map_display(t_map *map)
{
	int	bits_per_pixel;
	int	size_line;
	int	endian;
	int	*addr;

	map->widthx = map->width / (map->sizex + 1);
	printf("%d \n", map->widthx);
	if (!(map->win = mlx_new_window(map->mlx, map->length * 2, map->width * 2, "FdF")))
		return ;
	if (!(map->image = mlx_new_image(map->mlx, map->length * 2, map->width * 2)))
		return ;
	map->addr = mlx_get_data_addr(map->image, &bits_per_pixel,
			&size_line, &endian);
	addr = (int *)map->addr;
	ft_draw_grid(map);
	mlx_put_image_to_window(map->mlx, map->win, map->image, 0, 0);
	mlx_loop(map->mlx);
}
