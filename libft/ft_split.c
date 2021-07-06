/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymori <ymori@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 18:02:41 by ymori             #+#    #+#             */
/*   Updated: 2021/05/02 14:36:31 by ymori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_words(char const *s, char c)
{
	size_t	s_i;
	size_t	word_i;

	s_i = 0;
	word_i = 0;
	while (s[s_i] != '\0')
	{
		while (s[s_i] == c && s[s_i] != '\0')
			s_i++;
		while (s[s_i] != c && s[s_i] != '\0')
			s_i++;
		word_i++;
	}
	return (word_i);
}

static void	fill_word(char *p, char const *s, size_t head, size_t tail)
{
	size_t	i;

	i = 0;
	while (head < tail)
		p[i++] = s[head++];
	p[i] = '\0';
}

static char	**set_str(char **p, char const *s, char c)
{
	size_t	s_i;
	size_t	p_i;
	size_t	word_head;

	s_i = 0;
	p_i = 0;
	while (s[s_i] != '\0')
	{
		while (s[s_i] == c)
			s_i++;
		if (s[s_i] == '\0')
			break ;
		word_head = s_i;
		while (s[s_i] != c && s[s_i] != '\0')
			s_i++;
		p[p_i] = (char *)malloc((s_i - word_head + 1) * sizeof(char));
		fill_word(p[p_i++], s, word_head, s_i);
	}
	p[p_i] = NULL;
	return (&p[0]);
}

char	**ft_split(char const *s, char c)
{
	char	**p;

	if (s == NULL)
		return (NULL);
	p = (char **)malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!p)
		return (NULL);
	return (set_str(p, s, c));
}
