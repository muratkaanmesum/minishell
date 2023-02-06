/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eablak <eablak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 18:20:58 by eablak            #+#    #+#             */
/*   Updated: 2022/10/16 14:53:38 by eablak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_check(long int n)
{
	long int	sayi;
	int			len;

	sayi = n;
	len = 0;
	if (sayi <= 0)
	{
		sayi *= -1;
		len++;
	}
	while (sayi > 0)
	{
		len++;
		sayi /= 10;
	}
	return (len);
}

static void	sayi_ata(char *dizi, int len, long int sayi)
{
	while (sayi > 0)
	{
		dizi[--len] = (sayi % 10) + '0';
		sayi /= 10;
	}
}

char	*ft_itoa(int n)
{
	int			len;
	char		*dizi;
	long int	sayi;

	len = ft_check(n);
	dizi = (char *)malloc(sizeof(char) * len + 1);
	if (dizi == 0)
		return (NULL);
	sayi = n;
	if (n == 0)
	{
		dizi[0] = '0';
		dizi[1] = '\0';
		return (dizi);
	}
	else if (n < 0)
		sayi *= -1;
	sayi_ata(dizi, len, sayi);
	dizi[len] = '\0';
	if (n < 0)
		dizi[0] = '-';
	return (dizi);
}
