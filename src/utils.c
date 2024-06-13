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

void	print_string_array(char **str_array)
{
	int	i;

	i = 0;
	while (str_array[i] != NULL)
	{
		printf("\nstrArr[%d] #%s#", i, str_array[i]);
		i++;
	}
	printf("\n");
}