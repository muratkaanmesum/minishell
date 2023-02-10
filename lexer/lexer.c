/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 13:52:33 by mmesum            #+#    #+#             */
/*   Updated: 2023/02/10 16:53:51 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pass_inside_quotes(char *str, int *i, char kontrol)
{
	while (str[*i] != kontrol)
		*i = *i + 1;
}

char	*find_redirection(char *str)
{
	char	*array;
	char	**redirections;
	int		j;
	int		i;

	array = "<< < >> > |";
	redirections = ft_split(array, ' ');
	i = 0;
	while (redirections[i] != 0)
	{
		j = 0;
		while (redirections[i][j] != '\0')
		{
			if (redirections[i][j] != str[j])
				break ;
			j++;
		}
		if (redirections[i][j] == '\0')
			return (redirections[i]);
		i++;
	}
	return (NULL);
}
//grep test < test.txt > test.txt
int	get_token_count(char *str)
{
	int		i;
	char	kontrol;
	int		count;
	char	*redirection;

	count = 1;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			kontrol = str[i];
			i++;
			pass_inside_quotes(str, &i, kontrol);
		}
		redirection = find_redirection(&str[i]);
		if (redirection != NULL)
		{
			count++;
			i += ft_strlen(redirection);
			if (str[i] != ' ' && str[i] != '\0')
			{
				count++;
				i++;
			}
		}
		if (str[i] == ' ')
		{
			count++;
			while (str[i] == ' ')
				i++;
		}
		i++;
	}
	return (count);
}
t_token	*lexer(char *str)
{
	char	*t_str;

	t_str = ft_strtrim(str, " ");
	printf("%d\n", get_token_count(t_str));
	return (NULL);
}
