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

	i = 0;
	j = 0;
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

static t_lst	*new_fd(int fd, t_lst **lst, t_lst *tmp)
{
	t_lst	*new;
	char	*txt;
	char	buff[BUFF_SIZE];
	int		ret;
	char	*tmptxt;

	if (tmp)
		txt = ft_strdup(tmp->txt);
	else
		txt = NULL;
	while ((ret = read(fd, buff, BUFF_SIZE)) > 0 && check_str(txt) == 0)
	{
		buff[ret] = '\0';
		tmptxt = txt;
		txt = ft_strjoin(tmptxt, buff);
		free(tmptxt);
	}
	if ((new = (t_lst *)malloc(sizeof(t_list))) == NULL || ret == -1)
		return (NULL);
	new->next = NULL;
	new->txt = txt;
	new->fd = fd;
	if ((*lst) == NULL)
		(*lst) = new;
	else
		tmp->next = new;
	return (new);
}

static t_lst	*parsing_chain(t_lst *lst, int fd)
{
	t_lst *tmp;

	tmp = lst;
	while (tmp && tmp->fd != fd)
		tmp = tmp->next;
	return (tmp);
}

int				get_next_line(const int fd, char **line)
{
	static t_lst	*lst = NULL;
	t_lst			*tmp;
	char			*tmptxt;

	tmp = parsing_chain(lst, fd);
	if (tmp == NULL || (tmp && check_str(tmp->txt) == 0))
	{
		if ((tmp = new_fd(fd, &lst, tmp)) == NULL)
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
