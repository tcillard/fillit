/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcillard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/19 02:38:29 by tcillard          #+#    #+#             */
/*   Updated: 2019/02/01 13:06:36 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int		*ft_tab_bin(char **tab)
{
	int		i;
	int		j;
	int		*a;

	i = 0;
	while (tab[i])
		i++;
	if (!(a = malloc(sizeof(int) * (i + 1))))
		return (0);
	i = -1;
	while (tab[++i])
	{
		a[i] = 0;
		j = 0;
		while (tab[i][j])
		{
			if (tab[i][j] != '.')
			{
				a[i] = a[i] + ft_power(2, j);
			}
			j++;
		}
	}
	a[i] = -1;
	return (a);
}

int		ft_check(char ***tetri, t_map **map, int size)
{
	int		*a;
	int		*b;
	int		cpy_i;
	int		u;

	a = ft_tab_bin(*tetri);
	b = ft_tab_bin((*map)->map);
	u = 0;
	ft_bits_decale(&a, (*map)->j);
	cpy_i = (*map)->i;
	while (b[cpy_i] != -1 && a[u] != 0 && a[u] != -1)
	{
		if (a[u] > ft_power(2, size) || ((a[u] & b[cpy_i]) != 0))
		{
			free(a);
			free(b);
			return (0);
		}
		++u && ++cpy_i;
	}
	cpy_i = (a[u] == -1 || a[u] == 0 ? 1 : 0);
	free(a);
	free(b);
	return (cpy_i);
}

void	ft_del_one(t_map **map, t_tetri *lst)
{
	int		i;
	int		j;

	i = 0;
	while (((*map)->map)[i])
	{
		j = 0;
		while (((*map)->map)[i][j])
		{
			if ((((*map)->map)[i][j]) == ('A' + lst->id))
				(((*map)->map)[i][j]) = '.';
			j++;
		}
		i++;
	}
}

int		ft_resolv_tab(t_tetri *lst, t_map **map, int size)
{
	int i;
	int j;
	int ret;

	i = -1;
	if (lst == NULL)
		return (1);
	while (((*map)->map)[++i])
	{
		j = -1;
		while (((*map)->map)[i][++j])
		{
			(*map)->i = i;
			(*map)->j = j;
			if ((ret = ft_check(&(lst->tetri), map, size)))
			{
				ft_write_to_tab(&((*map)->map), lst, i, j);
				if (ft_resolv_tab(lst->next, map, size))
					return (1);
				else
					ft_del_one(map, lst);
			}
		}
	}
	return (0);
}

t_map	*ft_resolv_tetris(t_tetri **lst, int nb_tetri)
{
	t_map	*map;
	int		size;
	int		i;

	i = 0;
	size = 2;
	while (size * size < nb_tetri * 4)
		size++;
	if (!(map = malloc(sizeof(t_map))))
		return (0);
	map->map = NULL;
	if (!(map->map = ft_realloc_tab(size, map->map)))
		return (0);
	ft_del_tab(&(map)->map, size);
	i = 0;
	while (!(ft_resolv_tab(*lst, &map, size)))
	{
		size++;
		if (!(map->map = ft_realloc_tab(size, map->map)))
			return (0);
		ft_del_tab(&(map)->map, size);
		i++;
	}
	return (map);
}
