/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_node_wildcard.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 19:22:17 by eablak            #+#    #+#             */
/*   Updated: 2023/03/22 06:39:26 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

int quotes_control(char *command)
{
	int i = 0;
	int start = 0,end = 0;
	while(command[i])
	{
		if (command[i] == '\'' || command[i] == '"')
		{
			start = i;
			i++;
			while(command[i] != '\'' && command[i] != '"')
				i++;
			end = i;
		}
		i++;
	}
	while(start < end)
	{
		if (command[start] == '*')
			return (0);
		start++;
	}
	return (1);
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

void add_command_to_arg(t_command *command,char **files)
{
	if (files == NULL)
		return ;
	int count_files = files_count(files);
	int total_arg = count_files - 1 + command->argument_count;
	char **new_args = malloc(sizeof(char*) * (total_arg + 1));
	int i = 1;
	int k = 0;
	while(i < count_files)
	{
		new_args[k] = ft_strdup(files[i]);
		i++;
		k++;
	}
	int j = 0;
	while(j < command->argument_count)
	{
		new_args[k] = ft_strdup(command->arguments[j]);
		k++;
		j++;
	}
	new_args[k] = NULL;
	command->argument_count = total_arg;
	//free(command->arguments); // içindekileri de freele
	command->arguments = new_args;
}

void	handle_forcommand(t_command *command)
{
	char		**files;
	char		buf[1024];
	static char	*prefix;
	int count;
	int index = 0;


	fix_str(command->command);
	if (quotes_control(command->command) == 1)
	{
		char *str = delete_quote(command->command);
		if (is_asterisk(str) && asterisk_slash(str) == 0)
		{
			files = just_asterisk(str);

			int count_files = files_count(files);
			if (files[0] == NULL)
				return;
				if(files[0] != NULL)
				command->command = files[0];
			add_command_to_arg(command,files);
		}
		else if (asterisk_slash(str) == 1)
		{
			count = 0;
			count = countWildcard(NULL, str,&count);
			if (count >= 1)
			{
				char **command_files = malloc(sizeof(char *) * (count + 1));
				expandWildcard(NULL,str,command_files,&index);
				command_files[index] = NULL;
				if(command_files == NULL)
					return;
					command->command = command_files[0];
					add_command_to_arg(command,command_files);
			}
		}
		free(str);

	}
}

void	handle_forarg(t_command *command)
{
	char	**match_files;
	int		i;
	int count;

	i = 0;
	count = 0;
	while (i < command->argument_count)
	{
		if (quotes_control(command->arguments[i]) == 1)
		{
			char *str = delete_quote(command->arguments[i]);
			if (is_asterisk(str)
				&& asterisk_slash(str) == 0)
			{
				fix_str(str);
				match_files = just_asterisk(str);
				match_files = sort_files(match_files, str);
				match_arg_files(match_files, command, i);
			}
			if (asterisk_slash(str) == 1)
			{
				countWildcard(NULL, str,&count);
				if (count >= 1)
				{
					int index = 0;
					char **arg_files = malloc(sizeof(char *) * (count + 1));
					expandWildcard(NULL,str,arg_files,&index);
					arg_files[count] = NULL;

					match_arg_files(arg_files,command,i);
				}
			}
			free(str);
		}
		i++;
	}
}

void	handle_node_wildcard(t_node *node)
{
	if(node->command->command[0] == '/')
		return;
	int i = 0;
	while(node->command->arguments[i])
	{
		if(node->command->arguments[i][0] == '/')
			return;
		i++;
	}
	handle_forcommand(node->command);
	handle_forarg(node->command);
}
