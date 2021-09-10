/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymori <ymori@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 02:33:20 by user42            #+#    #+#             */
/*   Updated: 2021/09/11 02:01:21 by ymori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int		g_ack_flag;

void	send_char(pid_t pid, char c)
{
	int		i;

	i = 0;
	while (i < 8)
	{
		if (c & (1 << i))
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(50);
		i++;
	}
}

void	transmitter(pid_t pid, char *message)
{
	while (*message)
	{
		send_char(pid, *message);
		message++;
	}
	send_char(pid, '\0');
}

void	is_ack_flag(int signo)
{
	if (signo == SIGUSR1)
		g_ack_flag = 1;
	else
		g_ack_flag = 0;
}

int	connection_check(pid_t server_pid)
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
	static int	send_byte;
	(void)siginfo;
	(void)oact;
	if (signo == SIGUSR2) // finish sending bit.
	{
		ft_putstr_fd("\rSended byte: ", STDOUT_FILENO);
		ft_putnbr_fd(++send_byte, STDOUT_FILENO);
	}
	if (signo == SIGUSR1)
		ft_putstr_fd("\nsend success.\n", STDOUT_FILENO);
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
	if (server_pid <= 0 || server_pid > 99998)
		return (-1);
	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = sig_handler;
	sigemptyset(&act.sa_mask);
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	transmitter(server_pid, argv[2]);
	ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}
