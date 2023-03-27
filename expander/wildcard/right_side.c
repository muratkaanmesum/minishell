/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   right_side.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eablak <eablak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 19:22:29 by eablak            #+#    #+#             */
/*   Updated: 2023/03/27 17:10:13 by eablak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

void	rightside_count_prcss(char **files, t_files *f_arg, char *str)
{
	while (files[f_arg->i][f_arg->j] == str[f_arg->k]
		&& files[f_arg->i][f_arg->j] != '\0' && str[f_arg->k] != '\0')
	{
		f_arg->j++;
		f_arg->k++;
		if (files[f_arg->i][f_arg->j] == '\0' && str[f_arg->k] == '\0')
			f_arg->count++;
	}
	f_arg->k = 0;
}

void	right_side_files_count(char **files, char *str, t_files *f_arg)
{
	clean_files_operators(f_arg);
	f_arg->count = 0;
	while (files[f_arg->i])
	{
		f_arg->j = 0;
		while (files[f_arg->i][f_arg->j])
		{
			if (files[f_arg->i][f_arg->j] == str[f_arg->k])
				rightside_count_prcss(files, f_arg, str);
			if (files[f_arg->i][f_arg->j] != '\0')
				f_arg->j++;
		}
		f_arg->i++;
	}
}

void	right_side_opt(char **files, char *str, t_files *f_arg)
{
	while (files[f_arg->i][f_arg->j] == str[f_arg->k]
		&& files[f_arg->i][f_arg->j] != '\0' && str[f_arg->k] != '\0')
	{
		f_arg->j++;
		f_arg->k++;
		if (files[f_arg->i][f_arg->j] == '\0' && str[f_arg->k] == '\0')
		{
			f_arg->new_files[f_arg->t] = ft_strdup(files[f_arg->i]);
			f_arg->t++;
		}
	}
	f_arg->k = 0;
}

char	**right_side_files(char **files, char *str, t_files *f_arg)
{
	clean_files_operators(f_arg);
	right_side_files_count(files, str, f_arg);
	f_arg->new_files = malloc(sizeof(char *) * (f_arg->count + 1));
	clean_files_operators(f_arg);
	while (files[f_arg->i])
	{
		f_arg->j = 0;
		while (files[f_arg->i][f_arg->j])
		{
			if (files[f_arg->i][f_arg->j] == str[f_arg->k])
				right_side_opt(files, str, f_arg);
			if (files[f_arg->i][f_arg->j] != '\0')
				f_arg->j++;
		}
		f_arg->i++;
	}
	free_double_ptr(files);
	f_arg->new_files[f_arg->t] = NULL;
	return (f_arg->new_files);
}
