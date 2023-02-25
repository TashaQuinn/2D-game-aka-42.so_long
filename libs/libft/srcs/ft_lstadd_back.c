#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*iterator;

	if (lst == NULL || new == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	iterator = *lst;
	while (iterator -> next != NULL)
		iterator = iterator -> next;
	iterator -> next = new;
}
