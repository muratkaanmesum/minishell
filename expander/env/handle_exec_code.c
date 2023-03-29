/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_exec_code.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 14:07:26 by mmesum            #+#    #+#             */
/*   Updated: 2023/03/29 19:08:10 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../expander.h"

int	get_str_count(char *str, char *env_value)
{
	int	i;
	int	count;
	int	in_quote;

	count = 0;
	i = 0;
	in_quote = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'')
			in_quote = !in_quote;
		if (str[i] == '$' && str[i + 1] == '?' && in_quote == 0)
		{
			count += ft_strlen(env_value);
			i++;
		}
		else
			count++;
		i++;
	}
	return (count);
}

char	*handle_exec_code(char *str, char *env_value)
{
	int		i;
	int		j;
	char	*new_str;
	int		in_quote;

	new_str = malloc(sizeof(char) * (get_str_count(str, env_value) + 1));
	assign_default_values(&i, &in_quote, &j);
	while (str[i] != '\0')
	{
		if (str[i] == '\'')
			in_quote = !in_quote;
		if (str[i] == '$' && str[i + 1] == '?' && in_quote == 0)
		{
			ft_strlcpy(new_str + j, env_value, ft_strlen(env_value) + 1);
			j += ft_strlen(env_value);
			i++;
		}
		else
			new_str[j++] = str[i];
		i++;
	}
	new_str[j] = '\0';
	free(str);
	return (new_str);
}

void	handle_exec_files(t_node *node, char *last_exec_code)
{
	int	i;

	i = -1;
	while (node->redirections->infile[++i] != NULL)
		node->redirections->infile[i] = handle_exec_code(
				node->redirections->infile[i], last_exec_code);
	i = -1;
	while (node->redirections->outfile[++i] != NULL)
		node->redirections->outfile[i] = handle_exec_code(
				node->redirections->outfile[i], last_exec_code);
}

void	handle_all_exec_code(t_node *node)
{
	int		i;
	char	*last_exec_code;

	last_exec_code = ft_itoa(node->execute->last_exit_code);
	i = -1;
	node->command->command = handle_exec_code(node->command->command,
			last_exec_code);
	while (node->command->arguments[++i] != NULL)
		node->command->arguments[i] = handle_exec_code(
				node->command->arguments[i], last_exec_code);
	i = -1;
	if (node->redirections == NULL)
	{
		free(last_exec_code);
		return ;
	}
	handle_exec_files(node, last_exec_code);
	free(last_exec_code);
}
