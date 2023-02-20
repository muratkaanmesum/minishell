#include "../minishell.h"

int	get_token_count(t_token *tokens)
{
	int	get_count;

	get_count = 0;
	while (tokens->token != UNKNOWN)
	{
		if (tokens->token == AND || tokens->token == OR)
			get_count++;
		tokens++;
	}
	return (get_count + 1);
}
t_token	*get_token_array(t_token *token, int *i)
{
    int count = 0;
    
    while (token[*i].token != AND || token[*i].token != OR)
    {

		*i += 1;
    }
    
}
t_token	**split_token(t_token *tokens)
{
	t_token	**split;
	int		i;

	split = malloc(sizeof(t_token *) * get_token_count(tokens));
	i = 0;
	while (tokens[i].token != UNKNOWN)
	{
        
	}
}
// 0 cmd red file unknown
//1 test pipe test pipe unknown