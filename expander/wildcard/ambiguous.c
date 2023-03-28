/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambiguous.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eablak <eablak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 16:16:13 by eablak            #+#    #+#             */
/*   Updated: 2023/03/27 13:10:14 by eablak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

void	take_one_file_out_op(t_node *node, int in_or, int index, int key)
{
	char	**files;
	int		count;

	count = 0;
	if (key == 2 && in_or == 2)
	{
		files = get_o_files();
		count = count_wildcard(NULL, node->redirections->outfile[index],
				&count);
		if (count == 1)
		{
			count = 0;
			expand_wildcard(NULL, node->redirections->outfile[index], files,
				&count);
			free(node->redirections->outfile[index]);
			node->redirections->outfile[index] = files[0];
		}
	}
}

void	take_one_file_out(t_node *node, int in_or, int index, int key)
{
	char	**files;
	int		count;

	count = 0;
	if (key == 2 && in_or == 1)
	{
		files = get_o_files();
		count = count_wildcard(NULL, node->redirections->infile[index], &count);
		if (count == 1)
		{
			free(node->redirections->infile[index]);
			node->redirections->infile[index] = files[0];
		}
		else
			free_double_ptr(files);
	}
	take_one_file_out_op(node, in_or, index, key);
}

void	take_one_file_op(t_node *node, int in_or, int index, int key)
{
	char	**files;
	int		count;

	count = 0;
	if (key == 1 && in_or == 2)
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
}

void	take_one_file(t_node *node, int in_or, int index, int key)
{
	char	**files;
	int		count;

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
		else
			free_double_ptr(files);
	}
	take_one_file_op(node, in_or, index, key);
	take_one_file_out(node, in_or, index, key);
}

void	ambiguous(t_node *node)
{
	int	i;

	if (node->redirections != NULL)
	{
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
}
