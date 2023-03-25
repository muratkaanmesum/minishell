/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_node_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eablak <eablak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 18:33:35 by eablak            #+#    #+#             */
/*   Updated: 2023/03/23 14:17:23 by eablak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

int	quotes_control_return(char *command, int start, int end)
{
	while (start < end)
	{
		if (command[start] == '*')
			return (0);
		start++;
	}
	return (1);
}

int	quotes_control(char *command)
{
	int	i;
	int	start;
	int	end;

	i = 0;
	start = 0;
	end = 0;
	while (command[i])
	{
		if (command[i] == '\'' || command[i] == '"')
		{
			start = i;
			i++;
			while (command[i] != '\'' && command[i] != '"')
				i++;
			end = i;
		}
		i++;
	}
	return (quotes_control_return(command, start, end));
}

void	fix_str(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '*' && str[i + 1] == '*')
		{
			i++;
			continue ;
		}
		str[j] = str[i];
		i++;
		j++;
	}
	str[j] = '\0';
}

char	*delete_quote(char *str)
{
	char	*new_str;
	int		i;
	int		j;

	new_str = malloc(sizeof(char) * (get_length(str) + 1));
	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '"')
			i++;
		else
		{
			new_str[j] = str[i];
			i++;
			j++;
		}
	}
	new_str[j] = '\0';
	return (new_str);
}
