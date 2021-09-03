#include "minitalk.h"
#define BUFFER_SIZE 1024

int		checkpid(pid_t *pid, pid_t incomingpid)
{
	if (*pid == 0)
	{
		*pid = incomingpid;
		kill(incomingpid, SIGUSR1);
		return (1);
	}
	else if (*pid != incomingpid)
	{
		kill(incomingpid, SIGUSR2);
		return (1);
	}
	return (0); 
}

void	sig_handler(int signo, siginfo_t *siginfo, void *oact)
{
	static unsigned char	recived_char;
	static int				bit_i;
	static pid_t			pid;
	static int				buf_i;
	static char				buf[BUFFER_SIZE];

	(void)oact;
	if (checkpid(&pid, siginfo->si_pid))
		return ;
	printf("pid: %d\n", pid); //D
	if (signo == SIGUSR1)
		recived_char |= (1 << bit_i);
	if (bit_i == 7)
	{
		buf[buf_i] = recived_char;
		if (recived_char == '\4')
		{
			kill(pid, SIGUSR1);
			pid = 0;
		}
		else
			buf_i++;
		if (recived_char == '\4' || buf_i == BUFFER_SIZE)
		{
			write(STDOUT_FILENO, buf, buf_i);
			buf_i = 0;
		}
		recived_char = 0;
		bit_i = 0;
	}
	else
		buf_i++;
}

int	main(void)
{
	pid_t				pid;
	struct sigaction	act;

	pid = getpid();
	ft_putstr_fd("[PID] ", STDOUT_FILENO);
	ft_putnbr_fd(pid, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	act.sa_sigaction = sig_handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	while (1)
		pause();
	return (0);
}
