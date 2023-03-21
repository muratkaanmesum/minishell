/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_to_arg.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eablak <eablak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 18:58:17 by eablak            #+#    #+#             */
/*   Updated: 2023/03/21 20:26:45 by eablak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

void	command_to_arg_files(t_command *command, char **new_args,
		int count_files, char **files)
{
	int	i;
	int	k;
	int	j;

	i = 1;
	k = 0;
	while (i < count_files)
	{
		new_args[k] = ft_strdup(files[i]);
		i++;
		k++;
	}
	j = 0;
	while (j < command->argument_count)
	{
		new_args[k] = ft_strdup(command->arguments[j]);
		k++;
		j++;
	}
	new_args[k] = NULL;
}

void	add_command_to_arg(t_command *command, char **files)
{
	char	**new_args;
	int		count_files;
	int		total_arg;

	if (files == NULL)
		return ;
	count_files = files_count(files);
	total_arg = count_files - 1 + command->argument_count;
	new_args = malloc(sizeof(char *) * (total_arg + 1));
	command_to_arg_files(command, new_args, count_files, files);
	command->argument_count = total_arg;
	command->arguments = new_args;
}
