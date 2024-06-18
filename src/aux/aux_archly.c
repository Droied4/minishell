/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_archly.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 19:17:12 by deordone          #+#    #+#             */
/*   Updated: 2024/06/18 12:42:20 by avolcy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_lstenv_size(t_env *lst)
{
	int	count;

	count = 0;
	if (!lst)
		return (count);
	while (lst != NULL)
	{
		count++;
		lst = lst->next;
	}
	return (count++);
}

void	free_matrix(char ***allsplit)
{
	int	i;

	i = 0;
	if (!*allsplit)
		return ;
	while ((*allsplit)[i])
	{
		free((*allsplit)[i]);
		(*allsplit)[i] = NULL;
		i++;
	}
	free(*allsplit);
	*allsplit = NULL;
}

int	ft_del_env(t_env **lst)
{
	t_env	*temp;

	if (!lst)
		return (-1);
	while (*lst)
	{
		temp = (*lst)->next;
		free((*lst)->line);
		free((*lst)->var_name);
		if ((*lst)->var_content)
			free((*lst)->var_content);
		free(*lst);
		*lst = temp;
	}
	*lst = NULL;
	return (0);
}

void	print_lst_env_export(t_env *lst)
{
	while (lst)
	{
		if (found_equal(lst->line, '=') && lst->var_content)
			ft_dprintf(STDOUT_FILENO, "declare -x %s=\"%s\"\n", lst->var_name,
				lst->var_content);
		else if (found_equal(lst->line, '=') && !lst->var_content)
			ft_dprintf(STDOUT_FILENO, "declare -x %s=\"\"\n", lst->var_name);
		else
			ft_dprintf(STDOUT_FILENO, "declare -x %s\n", lst->var_name);
		lst = lst->next;
	}
}

void	print_lst_env(t_env *lst, int i)
{
	t_env	*tmp;

	if (!lst)
		return ;
	tmp = lst;
	if (1 == i)
	{
		while (tmp)
		{
			if (tmp->line && ft_strchr(tmp->line, (int) '='))
				ft_dprintf(STDOUT_FILENO, "%s=%s\n", tmp->var_name,
					tmp->var_content);
			tmp = tmp->next;
		}
	}
	else if (2 == i)
		print_lst_env_export(lst);
}
