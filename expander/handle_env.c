#include "expander.h"

void	handle_node_env(t_node *node, t_env *env)
{
	enum e_token	env_loc;
}

void	assign_node_env(t_node *node, t_env *env)
{
	if (node->connection_count == 1)
		handle_node_env(node, env);
}
void	handle_env(t_node *node, char **env)
{
	t_env	*variables;

	variables = get_env_variables(env);
	assign_node_env(node, variables);
}
