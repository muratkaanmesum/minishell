/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 13:52:33 by mmesum            #+#    #+#             */
/*   Updated: 2023/02/10 19:57:44 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int my_alpha(char c)
{
	if (c != 60 && c != 62 && c != 124 && c != ' ')
		return (1);
	return (0);
}

int	is_redirection(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return(1);
	return(0);
}


void define_character(char *str,int *i,int *count)
{
	if (my_alpha(str[*i]))
	{
		*count += 1;
		while(my_alpha(str[*i]) && str[*i] != '\0')
		{
			if(str[*i] == '"')
			{
				*i+=1;
				while(1)
				{
					if(str[*i] == '"')
						break;
					*i+=1;
				}
			}
			*i+=1;
		}
	}
	if (is_redirection(str[*i]))
	{
		*count += 1;
		int counter = 0;
		while(is_redirection(str[*i])&& str[*i] != '\0')
		{
			*i+=1;
			counter++;
			if (counter ==2)
				break;
		}
	}
}

int get_token_count(char *str)
{
	int *i;
	int *count;

	count = malloc(sizeof(int));
	i = malloc(sizeof(int));
	*count = 0;
	*i = 0;
	while (str[*i] != '\0')
	{
		define_character(str,i,count);
		if (str[*i] == ' ')
		{
			while(str[*i] == ' ' && str[*i] != '\0')
				*i+=1;
		}
	}
	return (*count);
}

//grep"asd"asd"asddasd"asd asd<test
t_token	*lexer(char *str)
{
	char	*t_str;

	t_str = ft_strtrim(str, " ");
	printf("%d\n", get_token_count(t_str));
	return (NULL);
}
