/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eablak <eablak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 05:26:17 by eablak            #+#    #+#             */
/*   Updated: 2023/03/30 12:05:54 by eablak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../expander.h"

int	quotes_include_quotes(char *str, int *i, int key)
{
	char	itself;
	char	opposite;

	itself = '\0';
	if (str[*i] != '\0')
		*i += 1;
	if (key == 1)
	{
		itself = '\'';
		opposite = '"';
	}
	else if (key == 2)
	{
		itself = '"';
		opposite = '\'';
	}
	while (str[*i] != itself && str[*i])
	{
		if (str[*i + 1] == opposite)
			*i += 1;
		if (str[*i] == opposite)
			return (1);
		(*i)++;
	}
	return (0);
}

void	length_utils(char *str, int *i, int *minus_count, int *only_quotes)
{
	if (str[*i] == '\'')
	{
		if (quotes_include_quotes(str, i, 1))
		{
			(*minus_count)++;
			while (str[*i] != '\'')
				(*i)++;
		}
		else
			(*only_quotes)++;
	}
	else if (str[*i] == '"')
	{
		if (quotes_include_quotes(str, i, 2))
		{
			(*minus_count)++;
			while (str[*i] != '"')
				(*i)++;
		}
		else
			(*only_quotes)++;
	}
}

int	get_length(char *str)
{
	int	i;
	int	minus_count;
	int	only_qutoes;
	int	ret;

	assign_default_values(&i, &minus_count, &only_qutoes);
	ret = 0;
	while (str[i])
	{
		length_utils(str, &i, &minus_count, &only_qutoes);
		if (str[i] != '\0')
			i++;
	}
	ret = ft_strlen(str) - (minus_count * 2) + 1;
	return (ret);
}

char	*delete_quotes(char *str)
{
	char	*new_str;
	int		val;

	val = get_length(str);
	new_str = malloc(sizeof(char) * (val));
	get_new_str(new_str, str);
	free(str);
	return (new_str);
}

void	delete_all_quotes(t_node *node)
{
	int	i;

	if (node->command == NULL)
		return ;
	i = -1;
	node->command->command = delete_quotes(node->command->command);
	while (node->command->arguments[++i] != NULL)
	{
		node->command->arguments[i] = delete_quotes(
				node->command->arguments[i]);
	}
	i = -1;
	if (node->redirections == NULL)
		return ;
	while (node->redirections->infile[++i] != NULL)
		node->redirections->infile[i] = delete_quotes(
				node->redirections->infile[i]);
	i = -1;
	while (node->redirections->outfile[++i] != NULL)
		node->redirections->outfile[i] = delete_quotes(
				node->redirections->outfile[i]);
}
