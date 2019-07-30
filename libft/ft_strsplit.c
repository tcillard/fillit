/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 21:07:26 by niguinti          #+#    #+#             */
/*   Updated: 2018/11/21 14:38:14 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	**ft_strsplit(const char *s, char c)
{
	int		words;
	char	**tab;
	int		i;
	int		j;

	if (!s)
		return (0);
	i = 0;
	words = ft_count_words(s, c);
	if (!(tab = (char **)malloc(sizeof(char *) * (words + 1))))
		return (NULL);
	while (i < words)
	{
		while (*s == c && *s)
			s++;
		j = 0;
		while (s[j] != c && s[j])
			j++;
		if (!(tab[i] = (char *)malloc(sizeof(char) * j)))
			return (NULL);
		ft_strncpy(tab[i++], s, j);
		s += j;
	}
	tab[i] = 0;
	return (tab);
}
