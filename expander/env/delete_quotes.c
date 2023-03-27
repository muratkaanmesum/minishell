/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eablak <eablak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 05:26:17 by kali              #+#    #+#             */
/*   Updated: 2023/03/27 21:55:57 by eablak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../expander.h"

int	quotes_include_quotes(char *str, int *i, int key)
{
	char	itself;
	char	opposite;

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
		if (str[*i] == opposite)
			return (1);
		(*i)++;
	}
	return (0);
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
		if (str[i] == '\'')
		{
			if (quotes_include_quotes(str, &i, 1))
			{
				minus_count++;
				while (str[i] != '\'')
					i++;
			}
			else
				only_qutoes++;
		}
		else if (str[i] == '"')
		{
			if (quotes_include_quotes(str, &i, 2))
			{
				minus_count++;
				while (str[i] != '"')
					i++;
			}
			else
				only_qutoes++;
		}
		if (str[i] != '\0')
			i++;
	}
	ret = ft_strlen(str) - (minus_count * 2) + 1;
	return (ret);
}

void	get_new_str(char *new_str, char *str)
{
	int	i;
	int	keep;
	int	j;
	int	outside_double;
	int	outside_single;

	i = 0;
	j = 0;
	outside_double = 0;
	outside_double = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			outside_single = 0;
			keep = i;
			i++;
			while (str[i] != '\'' && str[i])
			{
				if (str[i] == '"')
					outside_single = 1;
				i++;
			}
			if (outside_single == 1)
			{
				i = keep + 1;
				while (str[i] != '\'')
				{
					new_str[j] = str[i];
					j++;
					i++;
					if (str[i] == '\'')
					{
						i++;
						break ;
					}
				}
			}
			else
			{
				i = keep;
				i++;
				while (str[i] != '\'' && str[i])
				{
					new_str[j] = str[i];
					j++;
					i++;
					if (str[i] == '\'' || str[i] == '"')
						i++;
				}
			}
		}
		if (str[i] == '"')
		{
			outside_double = 0;
			keep = i;
			i++;
			while (str[i] != '"' && str[i])
			{
				if (str[i] == '\'')
					outside_double = 1;
				i++;
			}
			if (outside_double == 1)
			{
				i = keep + 1;
				while (str[i] != '"')
				{
					new_str[j] = str[i];
					j++;
					i++;
					if (str[i] == '"')
					{
						i++;
						break ;
					}
				}
			}
			else
			{
				i = keep;
				i++;
				while (str[i] != '"' && str[i])
				{
					new_str[j] = str[i];
					j++;
					i++;
					if (str[i] == '"')
						i++;
				}
			}
		}
		if (str[i] && j < get_length(str))
		{
			new_str[j] = str[i];
			j++;
			i++;
		}
		else
			break ;
	}
	new_str[j] = '\0';
}

char	*delete_quotes(char *str)
{
	char	*new_str;
	int		i;
	int		j;
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

	i = -1;
	node->command->command = delete_quotes(node->command->command);
	while (node->command->arguments[++i] != NULL)
	{
		if (quotes_control(node->command->arguments[i]) == 1)
			node->command->arguments[i] = delete_quotes(node->command->arguments[i]);
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