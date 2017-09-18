#ifndef FDF_H
# define FDF_H

#include <mlx.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

#include "libft.h"

typedef struct	s_map
{
		void	*mlx;
		void	*win;
		void	*image;
		char	*addr;
		int		**data;

}				t_map;

t_map		*ft_parsemap(char *str);
void		ft_map_display(t_map *map);

#endif
