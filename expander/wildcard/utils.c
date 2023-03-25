/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 19:22:31 by eablak            #+#    #+#             */
/*   Updated: 2023/03/25 12:59:38 by mmesum           ###   ########.fr       */
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

int	files_count(char **files)
{
	int	i;

	i = 0;
	if (files[0] == 0)
		return (0);
	while (files[i])
		i++;
	return (i);
}

int	files_w_dot_count(char **files)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (files[0] == 0)
		return (0);
	while (files[i])
	{
		if (files[i][0] != '.')
			count++;
		i++;
	}
	return (count);
}
