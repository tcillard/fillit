/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 19:09:44 by niguinti          #+#    #+#             */
/*   Updated: 2019/01/31 15:19:41 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>
#include <stdlib.h>

int		ft_getline(char **line, char **str)
{
	size_t	i;
	char	*tmp;

	tmp = NULL;
	i = 0;
	if ((*str)[0] == '\n')
	{
		if (!(*line = ft_strdup("\n"))
			|| !(tmp = ft_strsub(*str, 1, ft_strlen(*str) - 1)))
			return (-1);
		free(*str);
		*str = tmp;
		return (1);
	}
	while ((*str)[i] != '\n' && (*str)[i] != '\0')
		i++;
	if (!(*line = ft_strsub(*str, 0, i)))
		return (-1);
	if (((*str)[i] && !(tmp = ft_strsub(*str, i + 1, ft_strlen(*str) - i)))
		|| (!tmp && !(tmp = ft_strdup(""))))
		return (-1);
	free(*str);
	*str = tmp;
	return (1);
}

int		ft_lstfree(int fd, t_gnl **lst)
{
	t_gnl *nlst;

	nlst = *lst;
	while ((*lst)->fd != fd && *lst)
	{
		nlst = *lst;
		*lst = (*lst)->next;
	}
	if (*lst && (*lst)->fd == fd)
	{
		free((*lst)->str);
		nlst->next = (*lst)->next;
		(*lst)->next = NULL;
		free(*lst);
		*lst = NULL;
	}
	return (1);
}

t_gnl	*ft_newtgnl(int fd)
{
	t_gnl *lst;

	lst = NULL;
	if (!(lst = malloc(sizeof(t_gnl))))
		return (NULL);
	lst->fd = fd;
	if (!(lst->str = ft_strnew(0)))
		return (NULL);
	lst->next = NULL;
	return (lst);
}

t_gnl	*ft_verify_fd(int fd, t_gnl *lst)
{
	while (lst->next && lst->fd != fd)
		lst = lst->next;
	if (lst->fd == fd)
		return (lst);
	if (!(lst->next = ft_newtgnl(fd)))
		return (NULL);
	lst = lst->next;
	return (lst);
}

int		get_next_line(const int fd, char **line)
{
	static t_gnl	*lst = NULL;
	t_gnl			*nlst;
	char			buf[BUFF_SIZE + 1];
	int				tmp;
	char			*swp;

	if ((fd < 0 || !line) || (!lst && !(lst = ft_newtgnl(fd)))
			|| (!(nlst = ft_verify_fd(fd, lst))))
		return (-1);
	while ((tmp = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[tmp] = '\0';
		if (!(swp = ft_strjoin(nlst->str, buf)))
			return (-1);
		free(nlst->str);
		if ((nlst->str = swp) && ft_strchr(buf, '\n'))
			break ;
	}
	if (tmp < 0 || !ft_getline(line, &nlst->str))
		return (-1);
	if (**line == '\n' && !(**line = '\0'))
		return (1);
	if (tmp == 0 && (!(**line) && !(*(nlst->str))) && ft_lstfree(fd, &lst))
		return (0);
	return (1);
}
