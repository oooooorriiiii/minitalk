#include "minitalk.h"

int		g_ack_flag;

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
	static int				bit_i;
	static unsigned char	c;
	static char				*str;
	static pid_t			server_pid;

	if (s)
	{
		str = s;
		server_pid = pid;
		c = *str;
	}
	if (!bit_i)
	{
		bit_i = 8;
		c = *(++str);
		if (!c)
			connection_terminate(server_pid);
	}
	if (c && (c >> --bit_i & 1))
		kill(server_pid, SIGUSR1); // if c = 1, send SIGUSR1
	else if (c)
		kill(server_pid, SIGUSR2); // if c = 0, send SIGUSR2
}

void	is_ack_flag(int signo)
{
	if (signo == SIGUSR1)
		g_ack_flag = 1;
	else
		g_ack_flag = 0;
}

int		connection_check(pid_t server_pid)
{
	if (server_pid < 1 || server_pid > PID_MAX)
	{
		ft_putstr_fd("pid: ", STDOUT_FILENO);
		ft_putnbr_fd(server_pid, STDOUT_FILENO);
		ft_putstr_fd(" is invalid", STDOUT_FILENO);
		return (-1);
	}
	if (signal(SIGUSR1, is_ack_flag) == SIG_ERR
		|| signal(SIGUSR2, is_ack_flag) == SIG_ERR)
	{
		ft_putstr_fd("signal error\n", STDOUT_FILENO);
		return (-1);
	}
	if (kill(server_pid, SIGUSR1) == -1)
	{
		ft_putstr_fd("kill error\n", STDOUT_FILENO);
		return (-1);
	}
	if (g_ack_flag == 0)
	{
		ft_putstr_fd("connection error\n", STDOUT_FILENO);
		return (-1);
	}
	g_ack_flag = 0;
	return (1);	
}

void	sig_handler(int signo, siginfo_t *siginfo, void *oact)
{
	// static int	bytes;

	(void)siginfo;
	(void)oact;
	(void)signo;

	send_bit(0, 0);
}

int	main(int argc, char **argv)
{
	struct sigaction	act;
	int					server_pid;

	if (argc != 3)
	{
		ft_putstr_fd("Argument Error", STDOUT_FILENO);
		return (-1);
	}
	server_pid = ft_atoi(argv[1]);
	if (server_pid <= 0)
		return (-1);
	if (!connection_check(server_pid))
		return (-1);
	ft_putstr_fd("connected server\n", STDOUT_FILENO);
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = sig_handler;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	send_bit(argv[2],server_pid); 
	return (0);
}
