/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 17:26:04 by niguinti          #+#    #+#             */
/*   Updated: 2019/01/31 15:15:19 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int		ft_power(int nb, int pow)
{
	int cpy;

	cpy = nb;
	if (pow == 0)
		return (1);
	while (pow > 1)
	{
		nb = nb * cpy;
		pow--;
	}
	return (nb);
}

void	ft_bits_decale(int **a, int dec)
{
	int		j;

	j = 0;
	while ((*a)[j] != -1)
	{
		(*a)[j] = (*a)[j] << dec;
		j++;
	}
}

void	ft_print_map(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
	{
		ft_putstr(tab[i]);
		ft_putchar('\n');
		i++;
	}
}

void	ft_write_to_tab(char ***tab, t_tetri *lst, int i, int j)
{
	int cpy_j;
	int i_tet;
	int j_tet;

	i_tet = 0;
	while ((lst->tetri)[i_tet])
	{
		cpy_j = j;
		j_tet = 0;
		while ((lst->tetri)[i_tet][j_tet])
		{
			if (((lst->tetri)[i_tet][j_tet]) == '#' && (*tab)[i][cpy_j] == '.')
				(*tab)[i][cpy_j] = 'A' + lst->id;
			cpy_j++;
			j_tet++;
		}
		i++;
		i_tet++;
	}
	i = 0;
}

int		main(int ac, char **av)
{
	t_tetri *lst;
	t_map	*map;
	int		i;

	lst = NULL;
	if (ac != 2)
	{
		ft_putstr("usage: fillit input_file\n");
		return (0);
	}
	if (!check_map(open(av[1], O_RDONLY), &lst))
	{
		ft_putstr("error\n");
		free_all_tetriminos(lst);
		return (0);
	}
	map = ft_resolv_tetris(&lst, ft_tetris_nbr(lst));
	ft_print_map(map->map);
	i = 0;
	while (map->map[i])
		free(map->map[i++]);
	free(map->map);
	free(map);
	free_all_tetriminos(lst);
	return (0);
}
