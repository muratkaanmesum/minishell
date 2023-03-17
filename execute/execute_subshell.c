#include "execute.h"

void	execute_subshell(t_node *node)
{
	int	pid;
	int	i;

	i = 0;
	pid = fork();
	if (pid == 0)
	{
		dup2(node->in_fd, 0);
		dup2(node->out_fd, 1);
		if (node->connection_count == 1)
			execute_node(node);
		else if (node->connection_count > 1)
		{
			while (i < node->connection_count)
			{
				exec_all(node->connections[i]);
				i++;
			}
		}
		close_all_fds(node->execute->top_node);
		print_all_fds(node->execute->top_node);
		exit(0);
	}
	waitpid(pid, &node->execute->last_exit_code, 0);
	printf("SUBSHELL ENDED WITH CODE: %d\n", node->execute->last_exit_code);
}
