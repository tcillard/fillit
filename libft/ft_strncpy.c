/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 15:46:40 by niguinti          #+#    #+#             */
/*   Updated: 2018/11/23 14:16:31 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	char *pdst;

	pdst = dst;
	while (*src && len)
	{
		*pdst++ = *src++;
		len--;
	}
	while (len)
	{
		*pdst++ = '\0';
		len--;
	}
	return (dst);
}
