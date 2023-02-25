#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*iterator;

	if (lst == NULL)
		return ;
	iterator = lst;
	while (iterator != NULL)
	{
		f(iterator -> content);
		iterator = iterator -> next;
	}
}
