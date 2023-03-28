/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_new_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 13:55:26 by eablak            #+#    #+#             */
/*   Updated: 2023/03/28 15:21:40 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../expander.h"

void	assign_new_str(t_new_str *new, char *str, char *new_str)
{
	if ((str[new->i] == '\'' && str[new->i - 1] == '\'') || (str[new->i] == '"'
			&& str[new->i - 1] == '"'))
		new->i++;
	else
	{
		new_str[new->j] = str[new->i];
		new->j++;
		new->i++;
	}
}

void	get_new_str(char *new_str, char *str)
{
	t_new_str	*new;

	new = malloc(sizeof(t_new_str));
	new->i = 0;
	new->j = 0;
	new->outside_double = 0;
	new->outside_single = 0;
	while (str[new->i])
	{
		single_quotes(new, str, new_str);
		double_quotes(new, str, new_str);
		while (str[new->i] != '\0' && (str[new->i] == '\''
				|| str[new->i] == '"'))
			new->i++;
		if (str[new->i])
			assign_new_str(new, str, new_str);
		else
			break ;
	}
	new_str[new->j] = '\0';
	free(new);
}
