#include "minitalk.h"

void	sig_handler(int sig, siginfo_t *siginfo, void *oact)
{
	static unsigned char	c;
	static int				cnt;
	static pid_t			pid;

	(void)oact;
	if (!pid)
		pid = siginfo->si_pid;
	c |= (sig == SIGUSR1);
	if (++cnt == 8)
	{
		if (c == 0)
		{
			pid = 0;
			return ;
		}
		write(STDOUT_FILENO, &c, sizeof(c));
		kill(pid, SIGUSR1); // Why is this necessary?
		// Maybe, I think that SIGUSR1 indicates that it has finished reading the last bit.
		c = 0;
		cnt = 0;
	}
	else
	{
		c <<= 1;
		kill(pid, SIGUSR2);
	}
}

int	main(void)
{
	struct sigaction	act;

	ft_putstr_fd("[PID] ", STDOUT_FILENO);
	ft_putnbr_fd(getpid(), STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = sig_handler;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	while (1)
	{
		pause();
	}
	return (0);
}
