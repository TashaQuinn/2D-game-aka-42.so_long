#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*pointer;

	pointer = (char *)s + ft_strlen((char *)s);
	while (*pointer != (unsigned char)c)
	{
		if (pointer == (char *)s)
			return (NULL);
		pointer--;
	}
	return (pointer);
}
