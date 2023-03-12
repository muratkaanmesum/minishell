// #include "wildcard.h"

// int	is_match(char *file, char *str)
// {
// 	// printf("gelen dosya %s\n", file);
// 	// printf("gelen str: %s\n", str);
// 	if (is_left_side(str, 0) == 1)
// 	{
// 		printf("left de %s\n", str);
// 		//is_file_lef(file, str);
// 	}
// 	if (is_middle(str, 0) == 1)
// 		printf("ortda %s\n", str);
// 	if (is_right_side(str, 0) == 1)
// 		printf("right da %s\n", str);
// 	return (1);
// }

// int	get_dir_count(char *path)
// {
// 	char			buf[1024];
// 	DIR				*d;
// 	struct dirent	*dir;
// 	int				i;

// 	i = 0;
// 	d = opendir(path); //gelen pwd için
// 	if (d)
// 	{
// 		while ((dir = readdir(d)) != NULL)
// 			if (dir->d_type == DT_DIR)
// 				i++;
// 		closedir(d);
// 	}
// 	free(dir);
// 	return (i);
// }

// char	**get_only_files(char *path)
// {
// 	DIR				*d;
// 	struct dirent	*dir;
// 	int				count;
// 	char			**files;
// 	int				i;
// 	int				j;

// 	count = get_dir_count(path);
// 	files = (char **)malloc(sizeof(char *) * (count + 1));
// 	d = opendir(path); //gelen pwd için
// 	if (d)
// 	{
// 		i = 0;
// 		while ((dir = readdir(d)) != NULL)
// 			if (dir->d_type == DT_DIR)
// 			{
// 				files[i] = dir->d_name;
// 				i++;
// 			}
// 		closedir(d);
// 	}
// 	free(dir);
// 	files[i] = NULL;
// 	return (files);
// }

// /*

// 	1) files'ları getirmek için path'im getcwd+prefix
// 	2) gelen dosyaları tut
// 	3) prefix açıldıktan sonra sufix'te onu sil
// 	4) aynı fonskiyonu gelen dosyalar bitene kadar yeni pprefix ve suffixle çağırıcam 
// 														-> SUFİX null olana kadar
// */

// // char	**add_to_arr(char *str)
// // {
// // 	static char	*str[128];
// // 	static int	i;

// // 	i = 0;
// // 	return (0);
// // }

// char	*find_prefix(char *suffix)
// {
// 	int		i;
// 	char	*prefix;

// 	i = 0;
// 	while (suffix[i] != '\0' && suffix[i] != '/')
// 		i++;
// 	if (suffix[i] == '/')
// 		i++;
// 	prefix = malloc(sizeof(char) * (i + 1));
// 	i = 0;
// 	while (suffix[i] != '\0' && suffix[i] != '/')
// 	{
// 		prefix[i] = suffix[i];
// 		i++;
// 	}
// 	if (suffix[i] == '/')
// 		prefix[i++] = '/';
// 	prefix[i] = '\0';
// 	return (prefix);
// }

// // char	*cut_pre(char *prefix, char *suffix)
// // {
// // 	prefix = find_prefix(suffix);
// // 	printf("kesilecek prefix %s\n", prefix);
// // 	return (NULL);
// // }

// char	*edit_prefix(char *prefix)
// {
// 	char	*new_prefix;
// 	int		i;

// 	i = 0;
// 	while (prefix[i] != '\0')
// 		i++;
// 	if (prefix[i - 1] == '/')
// 		new_prefix = malloc(sizeof(char) * (i));
// 	else
// 		return (prefix);
// 	i = 0;
// 	while (prefix[i] != '/')
// 	{
// 		new_prefix[i] = prefix[i];
// 		i++;
// 	}
// 	new_prefix[i] = '\0';
// 	return (new_prefix);
// }

// char	*cut_suffix(char *suffix)
// {
// 	int	i;

// 	i = 0;
// 	while (suffix[i] != '/' && suffix[i] != '\0')
// 		i++;
// 	if (suffix[i] == '\0')
// 		return (NULL);
// 	else if (suffix[i + 1] == '\0')
// 		return (NULL);
// 	return (&suffix[i + 1]);
// }
// char	*edit_new_file(char *file)
// {
// 	int		i;
// 	char	*new_file;
// 	int		j;

// 	i = 0;
// 	while (file[i])
// 		i++;
// 	new_file = malloc(sizeof(char) * (i + 2));
// 	new_file[0] = '/';
// 	j = 1;
// 	i = 0;
// 	while (file[i])
// 	{
// 		new_file[j] = file[i];
// 		i++;
// 		j++;
// 	}
// 	new_file[j] = '\0';
// 	return (new_file);
// }
// int	get_files_count(char *path)
// {
// 	char			buf[1024];
// 	DIR				*d;
// 	struct dirent	*dir;
// 	int				i;

// 	i = 0;
// 	d = opendir(path); //gelen pwd için
// 	if (d)
// 	{
// 		while ((dir = readdir(d)) != NULL)
// 			i++;
// 		closedir(d);
// 	}
// 	free(dir);
// 	return (i);
// }
// char	**get_all_files(char *path)
// {
// 	DIR				*d;
// 	struct dirent	*dir;
// 	int				count;
// 	char			**files;
// 	int				i;
// 	int				j;

// 	count = get_files_count(path);
// 	files = (char **)malloc(sizeof(char *) * (count + 1));
// 	d = opendir(path); //gelen pwd için
// 	if (d)
// 	{
// 		i = 0;
// 		while ((dir = readdir(d)) != NULL)
// 		{
// 			files[i] = dir->d_name;
// 			i++;
// 		}
// 		closedir(d);
// 	}
// 	free(dir);
// 	files[i] = NULL;
// 	return (files);
// }

// char	**command_file(char *prefix, char *suffix, char *path)
// {
// 	char **new_files;
	
// 	if (suffix == NULL)
// 		return (NULL);
// 	if (ft_strchr(suffix, '/') != NULL)
// 		new_files = get_only_files(path);
// 	else
// 		new_files = get_all_files(path);
// 	prefix = find_prefix(suffix);
// 	prefix = edit_prefix(prefix);
// 	new_files = take_file(new_files, prefix);
// 	printf("\n");
// 	print_files(new_files);
// 	printf("\n");

// 	int i = 0;
// 	char *cut_suffix_char;
// 	while (new_files[i])
// 	{
// 		cut_suffix_char = cut_suffix(suffix);
// 		new_files[i] = edit_new_file(new_files[i]);
// 		char *new_path = ft_strjoin(path, new_files[i]);
// 		command_file(new_files[i], cut_suffix_char, new_path);
// 		i++;
// 	}

// 	return (NULL);
// }