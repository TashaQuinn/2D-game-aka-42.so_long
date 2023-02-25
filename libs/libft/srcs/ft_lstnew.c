#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*mem;

	mem = malloc(sizeof(t_list) * 1);
	if (mem == NULL)
		return (NULL);
	mem -> content = content;
	mem -> next = NULL;
	return (mem);
}
