/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 17:27:19 by niguinti          #+#    #+#             */
/*   Updated: 2019/01/31 15:16:06 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

t_tetri	*add_tetris(char **tab, t_tetri **lst)
{
	t_tetri			*nlst;
	t_tetri			*cpy;

	if (!(cpy = *lst) && !(*lst))
	{
		if (!(*lst = malloc(sizeof(t_tetri))))
			return (NULL);
		(*lst)->next = NULL;
		(*lst)->id = 0;
		(*lst)->tetri = ft_move_tetri(tab);
		free_dpoint(tab);
		return (*lst);
	}
	while (cpy->next != NULL)
		cpy = cpy->next;
	if (!(nlst = malloc(sizeof(t_tetri))))
		return (NULL);
	nlst->id = cpy->id + 1;
	nlst->tetri = ft_move_tetri(tab);
	free_dpoint(tab);
	cpy->next = nlst;
	nlst->next = NULL;
	return (nlst);
}

void	*free_dpoint(char **p)
{
	int i;

	i = 0;
	while (p[i])
	{
		free(p[i]);
		i++;
	}
	free(p[i]);
	free(p);
	return (NULL);
}

int		check_tetris(char **tab)
{
	int cnt;
	int i;
	int j;

	cnt = 0;
	i = -1;
	while (tab[++i] && (j = -1))
	{
		while (tab[i][++j])
		{
			if (tab[i][j] == '#' && j > 0 && tab[i][j - 1] && tab[i][j - 1] ==
					'#')
				cnt++;
			if (tab[i][j] == '#' && tab[i][j + 1] && tab[i][j + 1] == '#')
				cnt++;
			if (tab[i][j] == '#' && i > 0 && tab[i - 1] && tab[i - 1][j] == '#')
				cnt++;
			if (tab[i][j] == '#' && tab[i + 1] && tab[i + 1][j] == '#')
				cnt++;
		}
	}
	if (cnt == 6 || cnt == 8)
		return (1);
	free_dpoint(tab);
	return (0);
}

int		check_map(int fd, t_tetri **lst)
{
	char			buf[21];
	char			**tab;
	int				tmp;
	char			cmp;
	static int		bite = 0;

	cmp = 0;
	while ((tmp = read(fd, buf, 21)) > 0)
	{
		bite++;
		buf[tmp] = 0;
		cmp = buf[20];
		if ((cmp != '\0' && cmp != '\n') || !buf[0])
			return (0);
		if (!check_cnt(buf) || !(tab = tab_init(buf)))
			return (0);
		if (!check_tetris(tab))
			return (0);
		if (!add_tetris(tab, lst))
			return (0);
	}
	close(fd);
	if (cmp != '\0' || bite == 0)
		return (0);
	return (1);
}

void	free_all_tetriminos(t_tetri *lst)
{
	t_tetri	*cpy;
	int		i;

	while (lst)
	{
		i = -1;
		cpy = lst->next;
		free_dpoint(lst->tetri);
		lst->next = NULL;
		free(lst);
		lst = cpy;
	}
}
