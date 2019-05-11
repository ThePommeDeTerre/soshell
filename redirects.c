/* 
	redirects are handled in reverse order
	 2> >> > <
*/

#include "shell.h"

int redirects (int numargs, char* args[])
{
	// redirect STDOUT >
	if (numargs < 3)
		return numargs;

	if (strcmp(args[numargs-2], ">") == 0)
	{
		int fd=creat(args[numargs-1], S_IRUSR | S_IWUSR);
		if (fd < 0)
		{
			perror(NULL);
			return -1;	// indicar um erro
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
		args[numargs-2]=NULL;
		numargs=numargs-2;
	}

	// tratar do >>  open: O_WRONLY | O_APPEND
	if (numargs < 3)
		return numargs;

	if (strcmp(args[numargs-2], ">>") == 0)
	{
		int fd=creat(args[numargs-1], O_WRONLY | O_APPEND);
		if (fd < 0)
		{
			perror(NULL);
			return -1;
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
		args[numargs-2]=NULL;
		numargs=numargs-2;
	}

	// tratar do < open: O_RDONLY
	if (numargs < 3)
		return numargs;

	if(strcmp(args[numargs-2], "<") == 0)
	{
		int fd=creat(args[numargs-1], O_RDONLY);
		if (fd < 0)
		{
			perror(NULL);
			return -1;
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
		args[numargs-2]=NULL;
		numargs=numargs-2;
	}	

	if (numargs < 3)
		return numargs;

	if(strcmp(args[numargs-2], "2>") == 0)
	{
		int fd=creat(args[numargs-1], S_IRUSR);
		if (fd < 0)
		{
			perror(NULL);
			return -1;	// indicar um erro
		}
		dup2(fd, STDERR_FILENO);
		close(fd);
		args[numargs-2]=NULL;
		numargs=numargs-2;
	}

	return numargs;
}