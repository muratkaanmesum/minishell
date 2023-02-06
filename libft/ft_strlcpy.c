/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eablak <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 13:54:07 by eablak            #+#    #+#             */
/*   Updated: 2022/10/13 14:20:43 by eablak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	char			*ptr;
	unsigned int	x;

	x = 0;
	ptr = (char *)src;
	if (dstsize != 0)
	{
		while (x < (dstsize - 1) && src[x] != '\0')
		{
			dst[x] = ptr[x];
			x++;
		}
		dst[x] = '\0';
	}
	while (src[x])
		x++;
	return (x);
}
