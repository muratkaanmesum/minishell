/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eablak <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 15:49:49 by eablak            #+#    #+#             */
/*   Updated: 2022/10/16 13:44:52 by eablak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*dizi;

	c = (unsigned char)c;
	i = 0;
	dizi = (unsigned char *)s;
	while (i < n)
	{
		if (dizi[i] == c)
			return ((void *)dizi + i);
		i++;
	}
	return (0);
}
