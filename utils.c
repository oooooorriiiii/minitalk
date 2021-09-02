#include "minitalk.h"

int	ft_atoi(const char *nptr)
{
	const char	*s;
	long		out;
	int			neg;

	s = nptr;
	out = 0;
	neg = 0;
	while (*s == '\t' || *s == '\n' || *s == '\v' || \
	*s == '\f' || *s == '\r' || *s == ' ')
		s++;
	if (*s == '-')
	{
		neg = 1;
		s++;
	}
	else if (*s == '+')
		s++;
	while ((*s >= '0' && *s <= '9') && *s != '\0')
	{
		out *= 10;
		out += *s++ - '0';
	}
	if (neg)
		return (-out);
	return (out);
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, sizeof(c));
}

void	ft_putstr_fd(char *s, int fd)
{
	size_t	i;

	if (s == NULL)
		return ;
	i = 0;
	while (s[i] != '\0')
	{
		write(fd, &s[i], sizeof(char));
		i++;
	}
}

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
