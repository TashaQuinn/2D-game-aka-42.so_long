#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*mem;
	t_list	*tmp;

	tmp = NULL;
	while (lst)
	{
		mem = ft_lstnew((*f)(lst->content));
		if (mem == NULL)
		{
			ft_lstclear(&tmp, (*del));
			return (NULL);
		}
		ft_lstadd_back(&tmp, mem);
		lst = lst->next;
	}
	return (tmp);
}
