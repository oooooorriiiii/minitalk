#include "minitalk.h"

int	transmitter(pid_t pid, const char *massage)
{
	int	i;

	i = 0;
	while (*massage)
	{
		i = 0;
		while (i < 8)
		{
			if (*massage & (0x01 << i))
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			usleep(50);
			i++;
		}
		massage++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	pid_t	pid;

	if (argc != 3)
		return (-1);
	pid = ft_atoi(argv[1]);
	if (pid < 0 || pid > PID_MAX)
		return (-1);
	transmitter(pid, argv[2]);
	return (0);
}
