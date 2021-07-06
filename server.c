#include <unistd.h>
#include <stdio.h>
#include <signal.h>

#include "libft/libft.h"


int	main(void)
{
	pid_t	pid;

	pid = getpid();
	ft_putnbr_fd(pid, STDOUT_FILENO);
	
	return (0);
}
