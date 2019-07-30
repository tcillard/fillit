/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_array.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/19 16:12:08 by niguinti          #+#    #+#             */
/*   Updated: 2019/02/01 13:07:03 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int		check_cnt(char *buf)
{
	int i;
	int lines;
	int chars;
	int cnt;

	i = -1;
	lines = 0;
	chars = 0;
	cnt = 0;
	while (buf[++i] && i < 20)
	{
		if ((buf[i] == '\n' || !buf[i]) && chars == 4 && lines++ <= 4)
			chars = 0;
		else if (chars < 4 && (buf[i] == '\n' || !buf[i]))
			return (0);
		(buf[i] == '.' || buf[i] == '#') ? chars++ : chars;
		(buf[i] == '#') ? cnt++ : cnt;
	}
	if (cnt != 4 || lines != 4)
		return (0);
	return (1);
}

char	**tab_init(char *buf)
{
	int		i;
	int		j;
	int		k;
	char	**tab;

	i = -1;
	j = 0;
	k = 0;
	if (!(tab = malloc(sizeof(char *) * 5)) ||
			(tab[4] = 0))
		return (NULL);
	while (buf[++i])
		if (buf[i] == '\n' && !(k == 4 || k == 0))
			return (free_dpoint(tab));
		else if (buf[i] == '\n' && (j += 1))
			k = 0;
		else
		{
			if (k == 0 && !(tab[j] = malloc(sizeof(char) * 5)))
				return (free_dpoint(tab));
			tab[j][k] = buf[i];
			(k++ == 0) ? tab[j][4] = '\0' : k;
		}
	return (tab);
}

int		ft_tetris_nbr(t_tetri *lst)
{
	int i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

char	**ft_realloc_tab(int size, char **tab)
{
	int i;

	i = 0;
	if (tab != NULL)
	{
		while (tab[i])
		{
			free(tab[i]);
			i++;
		}
		free(tab);
	}
	if (!(tab = ft_memalloc(sizeof(char *) * size + 1)))
		return (0);
	tab[size] = 0;
	i = 0;
	while (i < size)
	{
		if (!(tab[i] = ft_memalloc(sizeof(char) * size + 1)))
			return (0);
		tab[i][size] = '\0';
		i++;
	}
	return (tab);
}
