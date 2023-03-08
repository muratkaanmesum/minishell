#include "wildcard.h"

void	just_asterisk(char *command)
{
	int		count;
	char	**my_files;
	int		i;

	//gelen yıldızlının nasıl olduğuna bak ona uyumlu olan ilk dosyayı al
	my_files = get_files();
	count = get_path_count();
	i = 0;
	while (my_files[i])
	{
		printf("%i. %s\n", i + 1, my_files[i]);
		i++;
	}
}

void	command_file(void)
{
	printf("commanfd file\n");
}

void	handle_command_asterisk(t_command *command)
{
	//get_path();
	if (is_asterisk(command->command) && asterisk_slash(command->command) == 0)
		just_asterisk(command->command);
	else if (is_asterisk(command->command) == 0
			&& asterisk_slash(command->command))
		command_file();
	//printf("handle command\n");
}
