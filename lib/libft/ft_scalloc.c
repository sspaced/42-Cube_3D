/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_scalloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lben-adi <lben-adi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 18:49:52 by elleroux          #+#    #+#             */
/*   Updated: 2025/02/24 14:28:37 by lben-adi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	clear_all(t_list *list)
{
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
	ft_lstadd_back(&alloc, ft_lstnew((void *)mem));
	return (mem);
}
