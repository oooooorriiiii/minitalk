/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymori <ymori@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 02:32:29 by user42            #+#    #+#             */
/*   Updated: 2021/09/11 01:17:59 by ymori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	receiver(int signo)
{
	static int	bit_i;
	static char	received_char;

	if (!(signo == SIGUSR1 || signo == SIGUSR2))
		ft_putstr_fd("Signal error\n", STDOUT_FILENO);
	if (signo == SIGUSR1)
		received_char |= (0x01 << bit_i);
	if (bit_i == 7)
	{
		write(STDOUT_FILENO, &received_char, 1);
		bit_i = 0;
		received_char = 0x00;
	}
	else
	{
		bit_i++;
	}
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
