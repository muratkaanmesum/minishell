/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   left_side.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eablak <eablak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 19:22:19 by eablak            #+#    #+#             */
/*   Updated: 2023/03/29 20:48:32 by eablak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

int	is_left_side(char *str, int index)
{
	int		count;

	count = 0;
	if (index == 0)
	{
		while (str[index] != '\0' && str[index] != '*')
		{
			count++;
			index += 1;
		}
		if (count > 0)
			return (1);
		else
			return (0);
	}
	return (0);
}

char	*left_side(char *str, int *index)
{
	int		count;
	char	*ret_str;
	int		j;

	count = 0;
	if (*index == 0)
	{
		while (str[*index] != '\0' && str[*index] != '*')
		{
			count++;
			*index += 1;
		}
		ret_str = malloc(sizeof(char) * (count + 1));
		*index -= count;
		j = 0;
		while (str[*index] != '\0' && str[*index] != '*')
		{
			ret_str[j] = str[*index];
			j++;
			*index += 1;
		}
		ret_str[j] = '\0';
		return (ret_str);
	}
	return (NULL);
}

void	left_side_files_count(char **files, char *str, t_files *f_arg)
{
	clean_files_operators(f_arg);
	f_arg->count = 0;
	while (files[f_arg->i])
	{
		f_arg->j = 0;
		while (str[f_arg->j])
		{
			if (files[f_arg->i][0] == str[0])
			{
				while (files[f_arg->i][f_arg->j] == str[f_arg->k]
					&& files[f_arg->i][f_arg->j] != '\0'
					&& str[f_arg->k] != '\0')
				{
					f_arg->j++;
					f_arg->k++;
				}
				if (str[f_arg->k] == '\0')
					f_arg->count++;
			}
			f_arg->k = 0;
			if (str[f_arg->j] != '\0')
				f_arg->j++;
		}
		f_arg->i++;
	}
}

void	left_side_option(char **files, char *str, t_files *f_arg)
{
	f_arg->j = 0;
	while (files[f_arg->i][f_arg->j] == str[f_arg->k]
		&& files[f_arg->i][f_arg->j] != '\0' && str[f_arg->k] != '\0')
	{
		f_arg->j++;
		f_arg->k++;
	}
	if (str[f_arg->k] == '\0')
	{
		f_arg->new_files[f_arg->t] = ft_strdup(files[f_arg->i]);
		f_arg->t++;
	}
}

char	**left_side_files(char **files, char *str, t_files *f_arg)
{
	left_side_files_count(files, str, f_arg);
	f_arg->new_files = malloc(sizeof(char *) * (f_arg->count + 1));
	clean_files_operators(f_arg);
	while (files[f_arg->i])
	{
		f_arg->k = 0;
		while (str[f_arg->k])
		{
			if (files[f_arg->i][0] == str[0])
				left_side_option(files, str, f_arg);
			if (str[f_arg->k] != '\0')
				f_arg->k++;
		}
		f_arg->i++;
	}
	free_double_ptr(files);
	f_arg->new_files[f_arg->t] = NULL;
	return (f_arg->new_files);
}
