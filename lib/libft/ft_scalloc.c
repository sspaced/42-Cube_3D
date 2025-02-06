#include "libft.h"
#include <stdio.h>

void	clear_all(t_list *list)
{
	// t_list *head;
	// t_list *temp;

	// head = list->next;
	// while (list && list != head)
	// {
	// 	free(list->content);
	// 	temp = list;
	// 	list = list->next;
	// 	free(temp);
	// }
	free(list->content);
	free(list);
}

void	*ft_scalloc(size_t nmemb, size_t size)
{
	char			*mem;
	static t_list	*alloc = NULL;
	size_t			i;

	if (nmemb == 0 && size == 0)
		clear_all(alloc);
	i = nmemb * size;
	if (i != 0 && (i / nmemb != size || i / size != nmemb))
		return (NULL);
	mem = (char *)malloc(nmemb * size);
	if (!mem)
		return (NULL);
	ft_bzero(mem, nmemb * size);
	ft_lstadd_back(&alloc, ft_lstnew((void*)mem));
	return (mem);
}
