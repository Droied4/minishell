/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 10:49:18 by avolcy            #+#    #+#             */
/*   Updated: 2023/11/07 17:37:30 by avolcy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//void	ft_del(void *element)
//{
//	char	*aux;
//	int		i;
//	i = 0;
//	aux = (char *)element;
//	while (element)
//	{
//		aux[i] = '\0';
//		i++;
//	}
//	free(element);
//}
//void	ft_del(void *element)
//{
//	free(element);
//}
//void	*ft_random(void *element)
//{
//	char	*aux;
//	char	*new_content;
//	int		i;
//	int		j;
//	aux = (char *)element;
//	i = 0;
//	j = 0;
//	if (aux[0] == '2' || aux[0] == '4')
//	{
//		new_content = ft_strdup("parell");
//		if (!new_content)
//			return (NULL);
//		while (new_content[i] != '\0')
//		{
//			aux[j] = new_content[i];
//			i++;
//			j++;
//		}
//	}
//	else
//	{
//		new_content = ft_strdup("senar");
//		if (!new_content)
//			return (NULL);
//		while (new_content[i] != '\0')
//		{
//			aux[j] = new_content[i];
//			i++;
//			j++;
//		}
//	}
//	aux[j] = '\0';
//	free(new_content);
//	return (element);
//}
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	void	*aux;
	t_list	*node;
	t_list	*newnode;

	node = 0;
	while (lst)
	{
		aux = f(lst->content);
		newnode = ft_lstnew(aux);
		if (!newnode)
		{
			free(aux);
			ft_lstclear(&node, del);
			return (NULL);
		}
		ft_lstadd_back(&node, newnode);
		lst = lst->next;
	}
	return (node);
}
//int main()
//{
//	t_list	*first;
//	t_list	*second;
//	t_list	*third;
//	t_list	*fourth;
//	t_list	*ptr;
//	t_list	*anterior;
//	char	*str1;
//	char	*str2;
//	char	*str3;
//	char	*str4;
//	str1 = ft_strdup("1 first");
//	str2 = ft_strdup("2 second");
//	str3 = ft_strdup("3 third");
//	str4 = ft_strdup("4 fourth");
//	first = ft_lstnew(str1);
//	second = ft_lstnew(str2);
//	third = ft_lstnew(str3);
//	fourth = ft_lstnew(str4);
//	first->next = second;
//	second->next = third;
//	third->next = fourth;
//	fourth->next = NULL;
//	ptr = first;
//	ft_lstmap(ptr, ft_random, ft_del);
//	while (ptr !=NULL)
//	{
//		ft_random(ptr->content);
//		//printf("lstmap predel: %s\n", ptr->content);
//		ft_del(ptr->content);
//		//printf("%s\n", ptr->content);
//		anterior = ptr;
//		ptr = ptr->next;
//		free(anterior);
//	}
//	return (0);
//}
