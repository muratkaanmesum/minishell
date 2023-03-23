/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   right_side.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eablak <eablak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 19:22:29 by eablak            #+#    #+#             */
/*   Updated: 2023/03/23 22:04:22 by eablak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

int	is_right_side(char *str, int index)
{
	char	*new_str;
	int		count;

	count = 0;
	if (index != 0)
	{
		if (str[index - 1] == '*')
		{
			while (str[index] != '\0')
			{
				if (str[index] == '*')
					return (0);
				index += 1;
				count++;
			}
			if (count > 0)
				return (1);
			else
				return (0);
		}
	}
	return (0);
}

char	*right_side(char *str, int *index)
{
	char	*new_str;
	int		count;
	int		j;

	count = 0;
	if (*index != 0)
	{
		if (str[*index - 1] == '*')
		{
			while (str[*index] != '\0')
			{
				if (str[*index] == '*')
					return (NULL);
				*index += 1;
				count++;
			}
			new_str = malloc(sizeof(char) * (count + 1));
			*index -= count;
			j = 0;
			while (str[*index] != '\0')
			{
				new_str[j] = str[*index];
				j++;
				*index += 1;
			}
			new_str[j] = '\0';
		}
		return (new_str);
	}
	return (NULL);
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
			{
				while (files[f_arg->i][f_arg->j] == str[f_arg->k]
					&& files[f_arg->i][f_arg->j] != '\0'
					&& str[f_arg->k] != '\0')
				{
					f_arg->j++;
					f_arg->k++;
					if (files[f_arg->i][f_arg->j] == '\0'
						&& str[f_arg->k] == '\0')
						f_arg->count++;
				}
				f_arg->k = 0;
			}
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
			f_arg->new_files[f_arg->t] = files[f_arg->i];
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
	f_arg->new_files[f_arg->t] = NULL;
	return (f_arg->new_files);
}
