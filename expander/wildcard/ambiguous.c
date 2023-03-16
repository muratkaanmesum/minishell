/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambiguous.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eablak <eablak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 16:16:13 by eablak            #+#    #+#             */
/*   Updated: 2023/03/16 18:03:06 by eablak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

void	take_one_file(char *red_file, int key)
{
	char	**files;
	int		count;

	count = 0;
	if (key == 1)
	{
		files = get_files();
		files = take_file(files, red_file);
		printf("eşleşen dosyalar\n");
		print_files(files);
	}
	else if (key == 2)
	{
		printf("burada\n");
		files = get_o_files();
		count = countWildcard(NULL, red_file, &count);
		printf("count %d\n", count);
	}
}

void	is_ambiguous(t_node *node)
{
	int	i;

	i = 0;
	while (i < node->redirections->infile_count)
	{
		if (is_asterisk(node->redirections->infile[i]) == 1)
			take_one_file(node->redirections->infile[i], 1);
		if (asterisk_slash(node->redirections->infile[i]) == 1)
			take_one_file(node->redirections->infile[i], 2);
		i++;
	}
	i = 0;
	while (i < node->redirections->outfile_count)
	{
		if (is_asterisk(node->redirections->outfile[i]) == 1)
			take_one_file(node->redirections->outfile[i], 1);
		if (asterisk_slash(node->redirections->outfile[i]) == 1)
			take_one_file(node->redirections->outfile[i], 2);
		i++;
	}
}

void	ambiguous(t_node *node)
{
	if (node->redirections != NULL)
	{
		is_ambiguous(node);
	}
}