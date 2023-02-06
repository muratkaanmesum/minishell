/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eablak <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 11:10:55 by eablak            #+#    #+#             */
/*   Updated: 2022/10/16 10:12:17 by eablak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_kelimeyaz(char *s, char c)
{
	size_t	i;
	char	*dizi;

	i = 0;
	while (s[i] != c && s[i])
		i++;
	dizi = (char *)malloc(i + 1);
	if (!dizi)
		return (0);
	i = 0;
	while (s[i] != c && s[i])
	{
		dizi[i] = s[i];
		i++;
	}
	dizi[i] = '\0';
	return (dizi);
}

static int	ft_kelimesayisi(char const *s, char c)
{
	int	i;
	int	sayi;
	int	bayrak;

	i = 0;
	sayi = 0;
	bayrak = 0;
	while (s[i])
	{
		if (s[i] == c)
			bayrak = 0;
		else if (s[i] != c && bayrak == 0)
		{
			bayrak = 1;
			sayi++;
		}
		i++;
	}
	return (sayi);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	int		j;
	int		i;
	int		kelime_sayisi;

	i = 0;
	j = 0;
	kelime_sayisi = ft_kelimesayisi(s, c);
	split = (char **)malloc(sizeof(char *) * kelime_sayisi + 1);
	if (!split)
		return (0);
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else if (s[i] != c)
		{
			split[j++] = ft_kelimeyaz((char *)&s[i], c);
			while (s[i] != c && s[i])
				i++;
		}
	}
	split[j] = 0;
	return (split);
}
