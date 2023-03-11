/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_tokens_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 10:08:50 by kali              #+#    #+#             */
/*   Updated: 2023/03/11 10:10:17 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	pass_character(t_lexer_args *args)
{
	if (args->str[args->i] == '"' || args->str[args->i] == '\'')
	{
		args->i++;
		while (args->str[args->i] != '\0')
		{
			if (args->str[args->i] == '"' || args->str[args->i] == '\'')
				break ;
			args->i++;
		}
	}
	else
		args->i++;
}
