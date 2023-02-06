/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eablak <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 10:10:22 by eablak            #+#    #+#             */
/*   Updated: 2022/10/16 10:10:23 by eablak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putchar(char c, int fd)
{
	write(fd, &c, 1);
}

static void	ft_putnbr(int nbr, int f)
{
	if (nbr == -2147483648)
	{
		ft_putchar('-', f);
		nbr = nbr / 10;
		ft_putnbr(-nbr, f);
		ft_putchar('8', f);
	}
	else if (nbr < 0)
	{
		ft_putchar('-', f);
		ft_putnbr(-nbr, f);
	}
	else
	{
		if (nbr > 9)
		{
			ft_putnbr(nbr / 10, f);
		}
		ft_putchar('0' + (nbr % 10), f);
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	ft_putnbr(n, fd);
}
