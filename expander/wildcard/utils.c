/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eablak <eablak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 19:22:31 by eablak            #+#    #+#             */
/*   Updated: 2023/03/21 20:31:56 by eablak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

void	print_files(char **files)
{
	int	i;

	i = 0;
	if (files[0] == NULL || files == NULL)
	{
		printf("dosya yok\n");
		return ;
	}
	while (files[i])
	{
		printf("%s\n", files[i]);
		i++;
	}
}

int	is_asterisk(char *str)
{
	if (ft_strchr(str, '*') != NULL && ft_strchr(str, '/') == NULL)
		return (1);
	return (0);
}

int	asterisk_slash(char *str)
{
	if (ft_strchr(str, '*') != NULL && ft_strchr(str, '/') != NULL)
		return (1);
	return (0);
}
