/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eablak <eablak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 13:34:06 by eablak            #+#    #+#             */
/*   Updated: 2023/03/28 13:52:07 by eablak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../expander.h"

int	check_exec_val(char *str, int *i, char *new_str, int *index)
{
	if (str[*i + 1] != '\0' && str[*i + 1] == '?')
	{
		new_str[*index] = '$';
		(*index)++;
		(*i)++;
		return (1);
	}
	return (0);
}

void	pass_single_quote_add(char *str, int *i, char *new_str, int *index)
{
	new_str[(*index)++] = str[(*i)++];
	while (str[*i] != '\'' && str[*i] != '\0')
		new_str[(*index)++] = str[(*i)++];
	if (str[*i])
		new_str[(*index)++] = str[(*i)++];
}

int	handle_val(t_str *holder, char *str, char *new_str, char *env_value)
{
	if (check_exec_val(str, &(holder->i), new_str, &holder->index))
		return (1);
	holder->start_index = holder->i;
	holder->flag = 1;
	assign_env_value(new_str, env_value, &holder->index);
	pass_env(str, holder->start_index, &(holder->i));
	return (0);
}

void	change_str(char *str, char *env_value, char *new_str)
{
	t_str	*holder;

	holder = malloc(sizeof(t_str));
	assign_default_values(&holder->i, &holder->q_flag, &holder->flag);
	holder->index = 0;
	holder->start_index = 0;
	while (str[holder->i] != '\0')
	{
		if (str[holder->i] == '\'' && holder->q_flag == 0)
			pass_single_quote_add(str, &(holder->i), new_str, &holder->index);
		if (str[holder->i] == '"')
			holder->q_flag = !holder->q_flag;
		if (str[holder->i] == '$' && holder->flag == 0)
			if (handle_val(holder, str, new_str, env_value))
				continue ;
		if (str[holder->i] != '\0')
			new_str[(holder->index)++] = str[(holder->i)++];
	}
	new_str[(holder->index)] = '\0';
	free(holder);
}
