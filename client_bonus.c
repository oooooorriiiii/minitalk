/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymori <ymori@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 02:33:20 by user42            #+#    #+#             */
/*   Updated: 2021/09/14 22:27:27 by ymori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

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
	send_char(pid, 0x04);
}

void	sig_handler(int signo, siginfo_t *siginfo, void *oact)
{
	static int	send_byte;

	(void)siginfo;
	(void)oact;
	if (signo == SIGUSR2)
	{
		ft_putstr_fd("\rSended byte: ", STDOUT_FILENO);
		ft_putnbr_fd(++send_byte, STDOUT_FILENO);
	}
	if (signo == SIGUSR1)
	{
		ft_putstr_fd("\nSuccess\n", STDOUT_FILENO);
		exit(0);
	}
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
	if (server_pid <= 0 || server_pid > PID_MAX)
		return (-1);
	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = sig_handler;
	sigemptyset(&act.sa_mask);
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	transmitter(server_pid, argv[2]);
	return (0);
}
