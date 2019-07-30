/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 13:15:12 by niguinti          #+#    #+#             */
/*   Updated: 2019/02/01 13:06:09 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# include "libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

typedef struct	s_tetri
{
	int				id;
	char			**tetri;
	struct s_tetri	*next;
}				t_tetri;

typedef struct	s_map
{
	int			i;
	int			j;
	char		**map;
}				t_map;
void			ft_start_piece_j(char **tetri, int *i);
t_tetri			*add_tetris(char **tab, t_tetri **lst);
int				check_map(int fd, t_tetri **lst);
int				check_tetris(char **tab);
void			free_all_tetriminos(t_tetri *lst);
void			*free_dpoint(char **p);
void			ft_bits_decale(int **a, int dec);
int				ft_check(char ***tetri, t_map **map, int size);
void			ft_del_one(t_map **map, t_tetri *lst);
void			ft_del_tab(char ***tab, int size);
char			**ft_move_tetri(char **tetri);
int				ft_power(int nb, int pow);
char			**ft_realloc_tab(int size, char **tab);
int				ft_resolv_tab(t_tetri *lst, t_map **map, int size);
int				ft_tetris_nbr(t_tetri *lst);
t_map			*ft_resolv_tetris(t_tetri **lst, int nb_tetri);
void			ft_start_piece(char **tetri, int *i, int *j);
int				*ft_tab_bin(char **tab);
void			ft_write_tetri(char ***new_tetri, char **tetri, int i, int j);
void			ft_write_to_tab(char ***tab, t_tetri *lst, int i, int j);
int				check_cnt(char *buf);
char			**tab_init(char *buf);
#endif
