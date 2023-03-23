/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambiguous.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 16:16:13 by eablak            #+#    #+#             */
/*   Updated: 2023/03/23 11:07:45 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

void	take_one_file(t_node *node, int in_or, int index, int key)
{
	char	**files;
	int		count;

	// if (in_or == 1)
	// 	printf("BAS infile sonuc %s\n", node->redirections->infile[index]);
	// else if (in_or == 2)
	// 	printf("BAS outfile sonuc %s\n", node->redirections->outfile[index]);
	count = 0;
	if (key == 1 && in_or == 1)
	{
		files = get_files();
		files = take_file(files, node->redirections->infile[index]);
		count = files_count(files);
		if (count == 1)
		{
			free(node->redirections->infile[index]);
			node->redirections->infile[index] = files[0];
		}
	}
	else if (key == 1 && in_or == 2)
	{
		files = get_files();
		files = take_file(files, node->redirections->outfile[index]);
		count = files_count(files);
		if (count == 1)
		{
			free(node->redirections->outfile[index]);
			node->redirections->outfile[index] = files[0];
		}
	}
	else if (key == 2 && in_or == 1)
	{
		files = get_o_files();
		count = countWildcard(NULL, node->redirections->infile[index], &count);
		if (count == 1)
		{
			count = 0;
			expandWildcard(NULL, node->redirections->infile[index], files,
					&count);
			free(node->redirections->infile[index]);
			node->redirections->infile[index] = files[0];
		}
	}
	else if (key == 2 && in_or == 2)
	{
		files = get_o_files();
		count = countWildcard(NULL, node->redirections->outfile[index], &count);
		if (count == 1)
		{
			count = 0;
			expandWildcard(NULL, node->redirections->outfile[index], files,
					&count);
			free(node->redirections->outfile[index]);
			node->redirections->outfile[index] = files[0];
		}
	}
	// if (in_or == 1)
	// 	printf("SON infile sonuc %s\n", node->redirections->infile[index]);
	// else if (in_or == 2)
	// 	printf("SON outfile sonuc %s\n", node->redirections->outfile[index]);
}

void	is_ambiguous(t_node *node)
{
	int	i;

	i = 0;
	while (i < node->redirections->infile_count)
	{
		if (is_asterisk(node->redirections->infile[i]) == 1)
			take_one_file(node, 1, i, 1);
		if (asterisk_slash(node->redirections->infile[i]) == 1)
			take_one_file(node, 1, i, 2);
		i++;
	}
	i = 0;
	while (i < node->redirections->outfile_count)
	{
		if (is_asterisk(node->redirections->outfile[i]) == 1)
			take_one_file(node, 2, i, 1);
		if (asterisk_slash(node->redirections->outfile[i]) == 1)
			take_one_file(node, 2, i, 2);
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
