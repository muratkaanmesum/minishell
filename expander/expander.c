/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 12:46:11 by mmesum            #+#    #+#             */
/*   Updated: 2023/03/29 19:06:04 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

void	expander(t_node *head)
{
	t_env	*variables;

	variables = get_env_variables(head->execute->env);
	handle_node_env(head, variables);
	wildcard(head);
	delete_all_quotes(head);
	free_env(variables);
}
