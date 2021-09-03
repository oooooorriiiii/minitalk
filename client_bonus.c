#include "minitalk.h"

void	connection_terminate(pid_t server_pid)
{
	int		i;

	i = 8;
	while (i--)
	{
		usleep(50);
		kill(server_pid, SIGUSR2);
	}
	exit(0);
}

void	send_bit(char *s, pid_t pid)
{
	static int				i = 8;
	static unsigned char	c;
	static char				*str;
	static pid_t			server_pid;

	if (pid < 0 || pid > PID_MAX)
	{
		ft_putstr_fd("pid: ", STDOUT_FILENO);
		ft_putnbr_fd(pid, STDOUT_FILENO);
		ft_putstr_fd(" is invalid", STDOUT_FILENO);
		exit(0);
	}
	if (s)
	{
		str = s;
		server_pid = pid;
		c = *str;
	}
	if (!i)
	{
		i = 8;
		c = *(++str);
		if (!c)
			connection_terminate(server_pid);
	}
	if (c && (c >> --i & 1))
		kill(server_pid, SIGUSR1); // if c = 1, send SIGUSR1
	else if (c)
		kill(server_pid, SIGUSR2); // if c = 0, send SIGUSR2
}

void	sig_handler(int signo, siginfo_t *siginfo, void *oact)
{
	static int	bytes;

	(void)siginfo;
	(void)oact;
	if (signo == SIGUSR1)
	{
		ft_putstr_fd("\rReceive Acks: ", STDOUT_FILENO);
		ft_putnbr_fd(++bytes, STDOUT_FILENO);
	}
	send_bit(0, 0);
}

int	main(int argc, char **argv)
{
	struct sigaction	act;

	if (argc != 3)
	{
		ft_putstr_fd("Argument Error", STDOUT_FILENO);
		return (0);
	}
	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = sig_handler;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	send_bit(argv[2], ft_atoi(argv[1]));
	while (1)
	{
		pause();
	}
	return (0);
}