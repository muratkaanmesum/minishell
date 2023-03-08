#include "wildcard.h"


void	command_file(void)
{
	printf("commanfd file\n");
}

void	handle_command_asterisk(t_command *command)
{
	//get_path();
	// if (is_asterisk(command->command) && asterisk_slash(command->command) == 0)
	// 	just_asterisk(command->command);
	// else if (is_asterisk(command->command) == 0
	// 		&& asterisk_slash(command->command))
	// 	command_file();
	//printf("handle command\n");
}

// void	take_file(char **files, char *command)
// {
// 	int		i;
// 	int		count;
// 	char	*find;
// 	int		j;

// 	i = 0;
// 	count = 0;
// 	while (command[i])
// 	{
// 		if (command[i] == '*')
// 		{
// 			i++;
// 			while (command[i] != '*')
// 			{
// 				i++;
// 				count++;
// 			}
// 			find = malloc(sizeof(char) * (count + 1));
// 			i -= count;
// 			j = 0;
// 			while (command[i] != '*')
// 			{
// 				find[j] = command[i];
// 				j++;
// 				i++;
// 			}
// 			find[j] = '\0';
// 			printf("find : %s\n", find);
// 			printf("dosya sayısı: %d\n", search_files_count(files, find));
// 			// printf("%d\n",i);
// 		}
// 		i++;
// 	}
// 	//printf("command: %s\n", command);
// }