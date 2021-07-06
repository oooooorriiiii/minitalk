/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymori <ymori@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 22:28:10 by ymori             #+#    #+#             */
/*   Updated: 2021/05/02 13:38:30 by ymori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_nbr_printer(unsigned int un, int fd)
{
	if (un < 10)
		ft_putchar_fd(un + '0', fd);
	else
	{
		ft_nbr_printer(un / 10, fd);
		ft_nbr_printer(un % 10, fd);
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	un;

	if (n < 0)
	{
		un = -n;
		ft_putchar_fd('-', fd);
	}
	else
		un = n;
	ft_nbr_printer(un, fd);
}
