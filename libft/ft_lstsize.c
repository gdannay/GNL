/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_size.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/21 16:49:53 by gdannay           #+#    #+#             */
/*   Updated: 2017/11/14 17:56:04 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

size_t	ft_lstsize(t_list *begin_list)
{
	t_list	*temp;
	size_t	i;

	i = 0;
	temp = begin_list;
	while (temp->next != NULL)
	{
		temp = temp->next;
		i++;
	}
	return (i);
}
