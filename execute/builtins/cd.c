#include "../execute.h"

void	change_pwd(char **env, char *buf, char *old_pwd_buff)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], "PWD=", 4) == 0)
		{
			free(env[i]);
			env[i] = ft_strjoin("PWD=", buf);
		}
		if (ft_strncmp(env[i], "OLDPWD=", 7) == 0)
		{
			free(env[i]);
			env[i] = ft_strjoin("OLDPWD=", old_pwd_buff);
		}
		i++;
	}
}

int	cd(char *args, t_node *node)
{
	char	buf[1024];
	char	old_pwd_buff[1024];

	getcwd(old_pwd_buff, 1024);
	if (chdir(args) == -1)
	{
		printf("cd: no such file or directory: %s\n", args);
		exit(1);
	}
	getcwd(buf, 1024);
	change_pwd(node->execute->env, buf, old_pwd_buff);
	return (1);
}
