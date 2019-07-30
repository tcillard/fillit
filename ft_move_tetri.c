/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move_tetri.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 17:23:52 by niguinti          #+#    #+#             */
/*   Updated: 2019/02/01 13:06:11 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	ft_start_piece_j(char **tetri, int *i)
{
	int	cpy_j;

	*i = 0;
	while (tetri[*i])
	{
		cpy_j = 0;
		while (tetri[*i][cpy_j])
		{
			if (tetri[*i][cpy_j] == '#')
				break ;
			cpy_j++;
		}
		if (tetri[*i][cpy_j] == '#')
			break ;
		*i = *i + 1;
	}
}

void	ft_start_piece(char **tetri, int *i, int *j)
{
	while (tetri[*i][*j])
	{
		*i = 0;
		while (tetri[*i] && *i < 3)
		{
			if (tetri[*i][*j] == '#')
				break ;
			*i = *i + 1;
		}
		if (tetri[*i][*j] == '#')
			break ;
		*j = *j + 1;
	}
	ft_start_piece_j(tetri, i);
}

void	ft_write_tetri(char ***new_tetri, char **tetri, int i, int j)
{
	int		cpy_i;
	int		cpy_j;
	int		a;
	int		b;

	a = 0;
	cpy_i = i;
	while (tetri[cpy_i])
	{
		b = 0;
		cpy_j = j;
		while (tetri[cpy_i][cpy_j])
		{
			(*new_tetri)[a][b] = tetri[cpy_i][cpy_j];
			b++;
			cpy_j++;
		}
		a++;
		cpy_i++;
	}
}

char	**ft_move_tetri(char **tetri)
{
	char	**new;
	int		j;
	int		i;
	int		malloc_j;

	malloc_j = 0;
	j = 0;
	i = 0;
	ft_start_piece(tetri, &i, &j);
	if (!(new = malloc(sizeof(char*) * (5 - i))))
		return (0);
	new[4 - i] = 0;
	while (malloc_j < (4 - i))
	{
		if (!(new[malloc_j] = malloc(sizeof(char) * (5 - j))))
			return (0);
		new[malloc_j][4 - j] = '\0';
		malloc_j++;
	}
	ft_write_tetri(&new, tetri, i, j);
	i = 0;
	return (new);
}

void	ft_del_tab(char ***tab, int size)
{
	int i;
	int j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			(*tab)[i][j] = '.';
			j++;
		}
		i++;
	}
}
