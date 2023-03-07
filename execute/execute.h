#ifndef EXECUTE_H
# define EXECUTE_H
# include "../minishell.h"
int	echo(char **args, char **option);
int	cd(char *args, char **env);
int	pwd(char **env);
int	print_env(char **env);
#endif
