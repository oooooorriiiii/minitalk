/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymori <ymori@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 11:00:26 by ymori             #+#    #+#             */
/*   Updated: 2021/09/15 11:07:41 by ymori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

int	arg1_checker(char *s)
{
	size_t	i;
	size_t	digit_i;

	i = 0;
	digit_i = 0;
	while (s[i] != '\0')
	{
		if (ft_isdigit(s[i]))
			digit_i++;
		i++;
	}
	if (digit_i == ft_strlen(s))
		return (1);
	return (0);
}
