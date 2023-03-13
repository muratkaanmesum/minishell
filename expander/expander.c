/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 12:46:11 by mmesum            #+#    #+#             */
/*   Updated: 2023/03/13 12:28:33 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

void	expander(t_node *head, char **env)
{
	t_env	*variables;

	variables = get_env_variables(env);
	wildcard(head);
	handle_env(head, variables);
	free_env(variables);
}
