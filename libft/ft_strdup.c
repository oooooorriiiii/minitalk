/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymori <ymori@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 02:14:19 by ymori             #+#    #+#             */
/*   Updated: 2021/01/29 00:47:10 by ymori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	len;
	char	*p;

	len = ft_strlen(s1) + 1;
	p = (char *)malloc(len * sizeof(char));
	if (p == NULL)
		return (NULL);
	ft_memcpy(p, s1, len);
	return (p);
}
