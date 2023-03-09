#include "wildcard.h"

int	get_path_count(void)
{
	char			buf[1024];
	DIR				*d;
	struct dirent	*dir;
	int				i;

	i = 0;
	getcwd(buf, 1024);
	d = opendir(buf); //gelen pwd için
	if (d)
	{
		while ((dir = readdir(d)) != NULL)
			i++;
		closedir(d);
	}
	free(dir);
	return (i);
}

char	**get_files(void)
{
	char			buf[1024];
	DIR				*d;
	struct dirent	*dir;
	int				count;
	char			**files;
	int				i;

	getcwd(buf, 1024);
	count = get_path_count();
	files = (char **)malloc(sizeof(char *) * (count + 1));
	d = opendir(buf); //gelen pwd için
	if (d)
	{
		i = 0;
		while ((dir = readdir(d)) != NULL)
		{
			files[i] = dir->d_name;
			i++;
		}
		closedir(d);
	}
	free(dir);
	files[i] = NULL;
	return (files);
}

void	print_files(char **files)
{
	int	i;

	i = 0;
	if (files[0] == NULL)
		return ;
	while (files[i])
	{
		printf("%s\n", files[i]);
		i++;
	}
}

int	is_asterisk(char *str)
{
	if (ft_strchr(str, '*') != NULL && ft_strchr(str, '/') == NULL)
		return (1);
	return (0);
}

int	asterisk_slash(char *str)
{
	if (ft_strchr(str, '*') != NULL && ft_strchr(str, '/') != NULL)
		return (1);
	return (0);
}