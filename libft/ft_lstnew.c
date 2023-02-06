/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eablak <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 10:01:45 by eablak            #+#    #+#             */
/*   Updated: 2022/10/16 12:18:07 by eablak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*yeni;

	yeni = malloc(sizeof(t_list));
	if (!yeni)
		return (0);
	yeni->content = content;
	yeni->next = NULL;
	return (yeni);
}
