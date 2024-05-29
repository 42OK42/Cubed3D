#include "../incl/cubed3D.h"

void	extension_check(char *str) //checks the string starting from the right to make sure it matches the extension
{
	int	strlen;
	int	extlen;
	int	i;
	char *extension;

	extension = ".cub";
	i = 1;
	strlen = ft_strlen(str);
	extlen = ft_strlen(extension);
	while (strlen - i > -1 && extlen - i > -1)
	{
		if (str[strlen - i] == extension[extlen - i])
		{
			if (extlen - i == 0)
				break ;
			i++;
		}
		else
			error_exit("wrong extension");
	}
}

int		args_check(int argc, char **argv)
{
	if (argc != 2)
		error_exit("Wrong number of arguments");
	extension_check(argv[1]);
	return (0);
}

