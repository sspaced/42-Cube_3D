/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lben-adi <lben-adi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 17:43:31 by lben-adi          #+#    #+#             */
/*   Updated: 2024/09/22 18:50:11 by lben-adi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*add;

	if (!lst || !new)
		return ;
	if (*lst)
	{
		add = ft_lstlast(*lst);
		(*add).next = new;
	}
	else
		*lst = new;
}
