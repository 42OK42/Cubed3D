#include "../incl/cubed3D.h"

void	perror_exit(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

void	error_exit(char *msg)
{
	ft_printf("%s\n", msg);
	exit(EXIT_FAILURE);
}
