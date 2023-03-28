/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eablak <eablak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 15:08:20 by eablak            #+#    #+#             */
/*   Updated: 2023/03/27 16:03:22 by eablak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

void	sort_files_progres(char **files, char *str, t_sort *sort)
{
	if (str[sort->m] == '*')
		sort->m++;
	if (str[sort->m] == files[sort->i][sort->j])
	{
		sort->m++;
		sort->j++;
	}
	if (files[sort->i][sort->j] && files[sort->i][sort->j] != str[sort->m])
		sort->j++;
}

void	ret_sort_files(char **files, char *str, t_sort *sort)
{
	sort->i = 0;
	sort->m = 0;
	sort->j = 0;
	sort->x = 0;
	while (files[sort->i])
	{
		sort->m = 0;
		sort->j = 0;
		while (files[sort->i][sort->j])
			sort_files_progres(files, str, sort);
		if (str[sort->m] == '*')
			sort->m++;
		if (str[sort->m] == '\0')
			sort->sorted_files[sort->x++] = ft_strdup(files[sort->i]);
		sort->i++;
	}
	sort->sorted_files[sort->x] = NULL;
	free_double_ptr(files);
}

char	**sort_files(char **files, char *str, t_sort *sort)
{
	sort->i = 0;
	sort->m = 0;
	sort->j = 0;
	sort->count = 0;
	while (files[sort->i])
	{
		sort->m = 0;
		sort->j = 0;
		while (files[sort->i][sort->j])
			sort_files_progres(files, str, sort);
		if (str[sort->m] == '*')
			sort->m++;
		if (str[sort->m] == '\0')
			sort->count++;
		sort->i++;
	}
	sort->sorted_files = malloc(sizeof(char *) * (sort->count + 1));
	ret_sort_files(files, str, sort);
	return (sort->sorted_files);
}
