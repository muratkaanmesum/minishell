/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eablak <eablak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 12:46:11 by mmesum            #+#    #+#             */
/*   Updated: 2023/03/28 15:53:05 by eablak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

void	expander(t_node *head)
{
	t_env	*variables;

	variables = get_env_variables(head->execute->env);
	handle_node_env(head, variables);
	wildcard(head);
	free_env(variables);
}
