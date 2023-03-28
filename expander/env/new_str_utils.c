/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_str_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eablak <eablak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 14:34:42 by eablak            #+#    #+#             */
/*   Updated: 2023/03/28 15:51:19 by eablak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../expander.h"

void	double_quotes_op(t_new_str *new, char *str, char *new_str)
{
	if (new->outside_double == 1)
	{
		new->i = new->keep + 1;
		while (str[new->i] != '\0' && str[new->i] != '"')
		{
			new_str[new->j] = str[new->i];
			new->j++;
			new->i++;
		}
		if (str[new->i] != '\0')
			new->i++;
	}
	else
	{
		new->i = new->keep;
		new->i++;
		while (str[new->i] && str[new->i] != '"')
		{
			new_str[new->j] = str[new->i];
			new->j++;
			new->i++;
			if (str[new->i] == '"')
				new->i++;
		}
	}
}

void	double_quotes(t_new_str *new, char *str, char *new_str)
{
	if (str[new->i] == '"' && ft_strchr(&str[new->i + 1], '"') != NULL)
	{
		new->outside_double = 0;
		new->keep = new->i;
		if (str[new->i] != '\0')
			new->i++;
		while (str[new->i] && str[new->i] != '"')
		{
			if (str[new->i] != '\0' && str[new->i] == '\'')
				new->outside_double = 1;
			if (str[new->i] != '\0')
				new->i++;
		}
		if (str[new->i] != '\0')
			double_quotes_op(new, str, new_str);
	}
}

void	single_quotes_op(t_new_str *new, char *str, char *new_str)
{
	if (new->outside_single == 1)
	{
		new->i = new->keep + 1;
		while (str[new->i] != '\'' && str[new->i] != '\0')
		{
			new_str[new->j] = str[new->i];
			new->j++;
			new->i++;
		}
		if (str[new->i] != '\0')
			new->i++;
	}
	else
	{
		new->i = new->keep;
		new->i++;
		while (str[new->i] != '\'' && str[new->i])
		{
			new_str[new->j] = str[new->i];
			new->j++;
			new->i++;
			if (str[new->i] == '\'' || str[new->i] == '"')
				new->i++;
		}
	}
}

void	single_quotes(t_new_str *new, char *str, char *new_str)
{
	if (str[new->i] == '\'' && ft_strchr(&str[new->i + 1], '\'') != NULL)
	{
		new->outside_single = 0;
		new->keep = new->i;
		new->i++;
		while (str[new->i] != '\'' && str[new->i])
		{
			if (str[new->i] == '"')
				new->outside_single = 1;
			new->i++;
		}
		single_quotes_op(new, str, new_str);
	}
}
