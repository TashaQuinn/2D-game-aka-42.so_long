#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	if (fd > 0 && s != NULL)
	{
		i = 0;
		while (s[i] != '\0')
		{
			write(fd, &s[i], 1);
			i++;
		}
	}
}
