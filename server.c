#include <unistd.h>
#include <stdio.h>
#include <signal.h>

#include "libft/libft.h"


void	receiver(int signo)
{
	static	size_t	i;
	static int	bit;
	static char	c;
	static char	buf[256];

	if (signo == SIGUSR1)
		c |= 1 << bit;
	if (i == 7)
	{
		//TODO: compute character
		c = 0;
		i = 0;
	}
	else
		i++;
}

int	main(void)
{
	pid_t	pid;

	pid = getpid();
	ft_putstr_fd("[PID] ", STDOUT_FILENO);
	ft_putnbr_fd(pid, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	while (1)
	{
		signal(SIGUSR1, receiver);
		signal(SIGUSR2, receiver);
	}
	return (0);
}
