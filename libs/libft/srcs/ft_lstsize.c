#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*iterator;
	int		i;

	i = 0;
	iterator = lst;
	while (iterator != NULL)
	{
		iterator = iterator -> next;
		i++;
	}
	return (i);
}
