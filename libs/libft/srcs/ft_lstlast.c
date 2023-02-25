#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*iterator;

	iterator = lst;
	if (lst == NULL)
		return (NULL);
	while (iterator -> next != NULL)
		iterator = iterator -> next;
	return (iterator);
}
