#include "wildcard.h"

int	is_match(char *file, char *str)
{
	// printf("gelen dosya %s\n", file);
	// printf("gelen str: %s\n", str);
	if (is_left_side(str, 0) == 1)
	{
		printf("left de %s\n", str);
		//is_file_lef(file, str);
	}
	if (is_middle(str, 0) == 1)
		printf("ortda %s\n", str);
	if (is_right_side(str, 0) == 1)
		printf("right da %s\n", str);
	return (1);
}

int	get_files_count(char *path)
{
	char			buf[1024];
	DIR				*d;
	struct dirent	*dir;
	int				i;

	i = 0;
	getcwd(path, 1024);
	d = opendir(path); //gelen pwd için
	if (d)
	{
		while ((dir = readdir(d)) != NULL)
			if (dir->d_type == DT_DIR)
			{
				i++;
			}
		closedir(d);
	}
	free(dir);
	return (i);
}

char	**get_only_files(char *path)
{
	char			buf[1024];
	DIR				*d;
	struct dirent	*dir;
	int				count;
	char			**files;
	int				i;
	int				j;

	getcwd(buf, 1024);
	if (path != NULL)
	{
		i = 0;
		while (buf[i])
			i++;
		buf[i] = '/';
		i++;
		j = 0;
		while (path[j])
		{
			buf[i] = path[j];
			i++;
			j++;
		}
		buf[i] = '\0';
	}
	printf("pathim :%s\n", buf);
	count = get_files_count(buf);
	files = (char **)malloc(sizeof(char *) * (count + 1));
	d = opendir(buf); //gelen pwd için
	if (d)
	{
		i = 0;
		while ((dir = readdir(d)) != NULL)
			if (dir->d_type == DT_DIR)
			{
				files[i] = dir->d_name;
				i++;
			}
		closedir(d);
	}
	free(dir);
	files[i] = NULL;
	getchar();
	return (files);
}

/*

	1) files'ları getirmek için path'im getcwd+prefix
	2) gelen dosyaları tut
	3) prefix açıldıktan sonra sufix'te onu sil
	4) aynı fonskiyonu gelen dosyalar bitene kadar yeni pprefix ve suffixle çağırıcam 
														-> SUFİX null olana kadar
*/

// char	**add_to_arr(char *str)
// {
// 	static char	*str[128];
// 	static int	i;

// 	i = 0;
// 	return (0);
// }

char	*find_prefix(char *suffix)
{
	int		i;
	char	*prefix;

	i = 0;
	while (suffix[i] != '\0' && suffix[i] != '/')
		i++;
	if (suffix[i] == '/')
		i++;
	prefix = malloc(sizeof(char) * (i + 1));
	i = 0;
	while (suffix[i] != '\0' && suffix[i] != '/')
	{
		prefix[i] = suffix[i];
		i++;
	}
	if (suffix[i] == '/')
		prefix[i++] = '/';
	prefix[i] = '\0';
	return (prefix);
}

// char	*cut_pre(char *prefix, char *suffix)
// {
// 	prefix = find_prefix(suffix);
// 	printf("kesilecek prefix %s\n", prefix);
// 	return (NULL);
// }

char	*edit_prefix(char *prefix)
{
	char	*new_prefix;
	int		i;

	i = 0;
	while (prefix[i] != '\0')
		i++;
	if (prefix[i - 1] == '/')
		new_prefix = malloc(sizeof(char) * (i));
	else
		return (prefix);
	i = 0;
	while (prefix[i] != '/')
	{
		new_prefix[i] = prefix[i];
		i++;
	}
	new_prefix[i] = '\0';
	free(prefix);
	return (new_prefix);
}

char	*cut_suffix(char *suffix)
{
	int		i;
	char	*new_suffix;

	i = 0;
	while (suffix[i] != '/')
		i++;
	new_suffix = malloc(sizeof(char) * (i + 1));
	i = 0;
	while (suffix[i] != '/')
	{
		new_suffix[i] = suffix[i];
		i++;
	}
	free(suffix);
	return (new_suffix);
}

char	**command_file(char *prefix, char *suffix)
{
	char **new_files;
	new_files = get_only_files(prefix);
	print_files(new_files);
	// if suffix
	// 	== NULL return (prefix);
	prefix = find_prefix(suffix);
	prefix = edit_prefix(prefix);
	//new_files = get_only_files(prefix);
	new_files = take_file(new_files, prefix);
	int i = 0;

	while (new_files[i])
	{
		command_file(new_files[i], cut_suffix(suffix));
		i++;
	}

	return (NULL);
}