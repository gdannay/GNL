/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 19:25:50 by gdannay           #+#    #+#             */
/*   Updated: 2017/11/20 12:25:51 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char		*get_line(t_lst *tmp)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	while (tmp->txt[i] != '\n' && tmp->txt[i] != '\0')
		i++;
	if ((new = (char *)malloc(sizeof(char) * (i + 1))) == NULL)
		return (NULL);
	while (j < i)
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

	txt = NULL;
	while ((ret = read(fd, buff, BUFF_SIZE)) > 0)
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

int				get_next_line(const int fd, char **line)
{
	static t_lst	*lst = NULL;
	t_lst			*tmp;
	char			*tmptxt;

	tmp = lst;
	if (fd < 0)
		return (-1);
	while (tmp && tmp->fd != fd)
		tmp = tmp->next;
	if (tmp == NULL)
	{
		tmp = lst;
		while (tmp && tmp->next != NULL)
			tmp = tmp->next;
		if ((tmp = new_fd(fd, &lst, tmp)) == NULL)
			return (-1);
	}
	*line = get_line(tmp);
	if (!(ft_strcmp(tmp->txt, "\0")) && !(ft_strcmp(*line, "\0")))
		return (0);
	tmptxt = tmp->txt;
	tmp->txt = ft_strsub(tmptxt,
			(unsigned int)(ft_strlen(*line) + 1), ft_strlen(tmp->txt));
	free(tmptxt);
	return (1);
}
