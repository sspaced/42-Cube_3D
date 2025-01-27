#include <stdio.h>
#include "cube.h"

void	ft_putstr_fd(char *s, int fd)
{
	while (*s)
	{
		ft_putchar_fd(*s++, fd);
	}
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

int	main(int argc, char **argv)
{
	if (argc != 2)
		return (ft_putstr_fd("Invalid argument\n", 2), 0);	
	if (!parser(argv))
		return (0);
	return (0);
}
