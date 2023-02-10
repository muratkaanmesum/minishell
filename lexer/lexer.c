/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 13:52:33 by mmesum            #+#    #+#             */
/*   Updated: 2023/02/10 19:56:48 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pass_inside_quotes(char *str, int *i, char kontrol)
{
	while (str[*i] != kontrol && str[*i] != '\0')
		*i = *i + 1;
}

int	find_redirection(char *str)
{
	if (ft_strncmp(str, ">>", 2) == 0)
		return (1);
	if (ft_strncmp(str, ">", 1) == 0)
		return (2);
	if (ft_strncmp(str, "<", 1) == 0)
		return (3);
	if (ft_strncmp(str, "<<", 2) == 0)
		return (4);
	if (ft_strncmp(str, "|", 1) == 0)
		return (5);
	return (0);
}
/*
	int		i;
	char	kontrol;
	int		count;

	count = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			kontrol = str[i];
			i++;
			pass_inside_quotes(str, &i, kontrol);
		}
		if (str[i] == ' ' || find_redirection(&str[i]) != 0)
		{
			while (find_redirection(&str[i]) != 0)
				i++;
			while (str[i] == ' ')
				i++;
			count++;
		}
		i++;
	}
	return (count);*/
int	handle_command_line(char *str, int i)
{
	int		j;
	char	control;
	int		count;

	count = 1;
	j = 0;
	while (j < i)
	{
		if (str[j] == '"' || str[j] == '\'')
		{
			control = str[i];
			i++;
			pass_inside_quotes(str, &i, control);
			i++;
		}
		if (str[j] == ' ')
		{
			count++;
			while (str[j] == ' ')
				j++;
		}
		j++;
	}
	return (count);
}
int	get_token_count(char *str)
{
	int		i;
	char	kontrol;
	int		count;

	count = 0;
	i = 0;
	while (str[i] != '\0')
	{
		while (find_redirection(&str[i]) == 0 && !(str[i] == '"'
				|| str[i] == '\'') && str[i] != '\0' && str[i] != ' ')
			i++;
		if (str[i] == '"' || str[i] == '\'')
		{
			kontrol = str[i];
			i++;
			pass_inside_quotes(str, &i, kontrol);
			i++;
		}
		if (str[i] == ' ' || find_redirection(&str[i]) != 0 || str[i] == '\0')
		{
			if (find_redirection(&str[i]) != 0)
			{
				while (find_redirection(&str[i]) != 0)
					i++;
				count++;
			}
			if (str[i] == ' ')
			{
				while (str[i] == ' ')
					i++;
				if (find_redirection(&str[i]) == 0)
					count++;
				else
					while (find_redirection(&str[i]) != 0)
						i++;
			}
		}
	}
	return (count);
}
//grep"asd"asd"asddasd"asd asd<test
t_token	*lexer(char *str)
{
	char	*t_str;

	t_str = ft_strtrim(str, " ");
	printf("%d\n", get_token_count(t_str));
	return (NULL);
}
