#include	"cub.h"

int	check_file_path(char *path)
{
	size_t	len;

	if (!path)
		return (0);
	len = strlen(path);
	if (len < 4)
		return (0);
	if (path[len - 4] != '.' || path[len - 3] != 'c' || 
		path[len - 2] != 'u' || path[len - 1] != 'b')
		return (0);
	return (1);
}