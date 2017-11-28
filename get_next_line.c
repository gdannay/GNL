/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 19:25:50 by gdannay           #+#    #+#             */
/*   Updated: 2017/11/21 20:17:27 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

void			free_tmp(t_lst **lst, t_lst *tmp)
{
	t_lst	*bef;
	t_lst	*nxt;

	bef = (*lst);
	nxt = tmp->next;
	if ((*lst) == tmp)
		(*lst) = (*lst)->next;
	else
	{
		while (bef && bef->next != tmp)
			bef = bef->next;
		if (nxt == NULL)
			bef->next = NULL;
		else
			bef->next = nxt;
	}
	free(tmp->txt);
	free(tmp);
}

static int		check_str(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

static char		*get_line(t_lst *tmp)
{
	int		i;
	int		j;
	char	*new;

	char	*txt;
	char	buff[BUFF_SIZE];
	int		ret;
	char	*tmptxt;
	i = 0;
	j = 0;
	while ((ret = read(fd, buff, BUFF_SIZE)) > 0 && check_str(txt) == 0)
	{
		buff[ret] = '\0';
		tmptxt = txt;
		txt = ft_strjoin(tmptxt, buff);
		free(tmptxt);
	}
	while (tmp->txt && tmp->txt[i] != '\n' && tmp->txt[i] != '\0')
		i++;
	if ((new = (char *)malloc(sizeof(char) * (i + 1))) == NULL)
		return (NULL);
	while (tmp->txt && j < i)
	{
		new[j] = tmp->txt[j];
		j++;
	}
	new[j] = '\0';
	return (new);
}

static t_lst	*new_fd(int fd, t_lst **lst)
{
	t_lst	*new;
	t_lst	*tmp;

	tmp = (*lst);
	while (tmp->next != NULL)
		tmp = tmp->next;
	if ((new = (t_lst *)malloc(sizeof(t_list))) == NULL)
		return (NULL);
	new->next = NULL;
	new->fd = fd;
	if ((*lst) == NULL)
		(*lst) = new;
	else
		tmp->next = new;
	return (new);
}

int				get_next_line(int fd, char **line)
{
	static t_lst	*lst = NULL;
	t_lst			*tmp;
	char			*tmptxt;

	tmp = lst;
	while (tmp && tmp->fd != fd)
		tmp = tmp->next;
	if (tmp == NULL)
	{
		if ((tmp = new_fd(fd, &lst) == NULL))
			return (-1);
	}
	*line = get_line(tmp);
	if (!(tmp->txt) || !(ft_strcmp(tmp->txt, "\0")) ||
			ft_strcmp(tmp->txt, "\0") == 3 || ft_strcmp(tmp->txt, "\0") == 16)
	{
		free_tmp(&lst, tmp);
		return (0);
	}
	tmptxt = tmp->txt;
	tmp->txt = ft_strsub(tmptxt, (ft_strlen(*line) + 1), ft_strlen(tmp->txt));
	free(tmptxt);
	return (1);
}
