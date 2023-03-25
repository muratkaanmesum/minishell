/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_env_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eablak <eablak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 12:38:38 by kali              #+#    #+#             */
/*   Updated: 2023/03/25 22:12:50 by eablak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../expander.h"
//echo asd'"$USER"'asd'$PATH'
//asd"$USER"'asd'$PATH''
void	assign_env_value(char *new_str, char *env_value, int *index)
{
	int	i;

	i = 0;
	while (env_value[i] != '\0')
		new_str[(*index)++] = env_value[i++];
}

void	assign_default_values(int *i, int *in_quote, int *flag)
{
	*i = 0;
	*in_quote = 0;
	*flag = 0;
}

void	pass_env(char *str, int start_index, int *i)
{
	while (str[*i] != '\0' && str[*i] != '\'' && str[*i] != '"'
		&& str[*i] != ' ' && str[*i] != '*' && str[*i] != '.' && str[*i] != ':'
		&& str[*i] != '/' && str[*i] != ',' && (str[*i] != '$'
			|| *i == start_index))
		(*i)++;
}
