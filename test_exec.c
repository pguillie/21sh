#include "shell.h"

int main(int ac, char **av)
{
	return (sh_execution(av + 1));
}
