/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 05:26:17 by kali              #+#    #+#             */
/*   Updated: 2023/03/25 12:43:01 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../expander.h"

void	count_inside_quotes(char *str, int *i, char c, int *count)
{
	*i = *i + 1;
	while (str[*i] != c)
	{
		(*count)++;
		(*i)++;
	}
}
void add_to_str(char *str, int *i, char *new_str, int *j)
{
	char c = str[*i];
	*i = *i + 1;
	while (str[*i] != c)
	{
		new_str[*j] = str[*i];
		(*j)++;
		(*i)++;
	}
}
int	get_length(char *str)
{
	int	i;
	int	count;
	int	single_quote;
	int	double_quote;

	double_quote = 0;
	single_quote = 0;
	count = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'')
			single_quote = !single_quote;
		else if (str[i] == '"')
			double_quote = !double_quote;
		if (single_quote == 1 || double_quote == 1)
		{
			count_inside_quotes(str, &i, str[i], &count);
			single_quote = 0;
			double_quote = 0;
		}
		else
			count++;
		i++;
	}
	return (count);
}

char	*delete_quotes(char *str)
{
	char	*new_str;
	int		i;
	int		j;
	int		double_quote;
	int		single_quote;

	double_quote = 0;
	single_quote = 0;
	new_str = malloc(sizeof(char) * (get_length(str) + 1));
	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'')
			single_quote = !single_quote;
		if (str[i] == '"')
			double_quote = !double_quote;
		if (single_quote == 1 || double_quote == 1)
		{
			add_to_str(str, &i, new_str, &j);
			single_quote = 0;
			double_quote = 0;
		}
		else
			new_str[j++] = str[i];
		i++;
	}
	new_str[j] = '\0';
	free(str);
	return (new_str);
}

void	delete_all_quotes(t_node *node)
{
	int	i;

	i = -1;
	node->command->command = delete_quotes(node->command->command);
	while (node->command->arguments[++i] != NULL)
	{
		if (quotes_control(node->command->arguments[i]) == 1)
			node->command->arguments[i] = delete_quotes(node->command->arguments[i],
														node);
	}
	i = -1;
	if (node->redirections == NULL)
		return ;
	while (node->redirections->infile[++i] != NULL)
		node->redirections->infile[i] = delete_quotes(node->redirections->infile[i]);
	i = -1;
	while (node->redirections->outfile[++i] != NULL)
		node->redirections->outfile[i] = delete_quotes(node->redirections->outfile[i]);
}
