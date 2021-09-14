/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymori <ymori@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 02:41:06 by ymori             #+#    #+#             */
/*   Updated: 2021/09/14 20:32:15 by ymori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	sig_handler(int signo, siginfo_t *siginfo, void *oact)
{
	static unsigned char	recived_char;
	static int				bit_i;
	static pid_t			client_pid;

	(void)oact;
	if (!client_pid)
		client_pid = siginfo->si_pid;
	if (signo == SIGUSR1)
		recived_char |= (1 << bit_i);
	if (bit_i == 7)
	{
		if (recived_char == 0x04)
		{
			kill(client_pid, SIGUSR1);
		}
		else
		{
			write(STDOUT_FILENO, &recived_char, 1);
			recived_char = 0;
			bit_i = 0;
			kill(client_pid, SIGUSR2);
		}
	}
	else
		bit_i++;
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
	act.sa_flags = SA_SIGINFO;
	sigemptyset(&act.sa_mask);
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	while (1)
		pause();
	return (0);
}
