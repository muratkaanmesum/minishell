/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 13:52:33 by mmesum            #+#    #+#             */
/*   Updated: 2023/02/11 07:48:12 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	my_alpha(char c)
{
	if (c != 60 && c != 62 && c != 124 && c != ' ' && c != '&')
		return (1);
	return (0);
}

int	is_redirection(char c)
{
	if (c == '<' || c == '>' || c == '|' || c == '&')
		return (1);
	return (0);
}

void	define_character(char *str, int *i, int *count)
{
	int	counter;

	if (my_alpha(str[*i]))
	{
		*count += 1;
		while (my_alpha(str[*i]) && str[*i] != '\0')
		{
			if (str[*i] == '"' || str[*i] == '\'')
			{
				*i += 1;
				while (str[*i] != '\0')
				{
					if (str[*i] == '"' || str[*i] == '\'')
						break ;
					*i += 1;
				}
			}
			*i += 1;
		}
	}
	if (is_redirection(str[*i]))
	{
		*count += 1;
		counter = 0;
		while (is_redirection(str[*i]) && str[*i] != '\0')
		{
			*i += 1;
			counter++;
			if (counter == 2)
				break ;
		}
	}
}

int	get_token_count(char *str)
{
	int	*i;
	int	*count;
	int	j;
	int	t_count;

	j = 0;
	t_count = 0;
	count = &t_count;
	i = &j;
	while (str[*i] != '\0')
	{
		define_character(str, i, count);
		if (str[*i] == ' ')
		{
			while (str[*i] == ' ' && str[*i] != '\0')
				*i += 1;
		}
	}
	return (*count);
}

t_token	*lexer(char *str)
{
	char	*t_str;

	t_str = ft_strtrim(str, " ");
	printf("%d\n", get_token_count(t_str));
	return (NULL);
}
