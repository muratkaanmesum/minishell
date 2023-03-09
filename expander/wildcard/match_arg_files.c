#include "wildcard.h"

int files_count(char **files)
{
    int i = 0;
    if (files[0] == 0)
        return (0);
    while(files[i])
        i++;
    return (i);
}

void	match_arg_files(char **files,t_command *command,int i)
{
    int match_files_count = files_count(files);
    printf("file count %d\n",match_files_count);
    
	return ;
}