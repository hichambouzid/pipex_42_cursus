#include "ft_pipex.h"



int main(int ac, char **av)
{
	int fd = open(av[1], O_RDONLY);
	printf("-----> %d\n", fd);
}