#ifndef WILDCARD_H
# define WILDCARD_H

# include "../../minishell.h"
# include <dirent.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <unistd.h>

void	handle_node_wildcard(t_node *node);
int		is_asterisk(char *str);
int		asterisk_slash(char *str);
void	handle_arg_asterisk(t_command *command, int index);
void	handle_command_asterisk(t_command *command);
int		get_path_count(void);
char	**get_files(void);
#endif