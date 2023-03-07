#ifndef EXECUTE_H
# define EXECUTE_H
# include "../minishell.h"
int	echo(char **args, char **option);
int	cd(char *args, char **env);
int	pwd(char **env);
int	print_env(char **env);
int	export(char **args, char **env);
int	unset(char **env, char **args);
int	get_env_len(char *env);
#endif
