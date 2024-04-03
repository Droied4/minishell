/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_archly.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 19:17:12 by deordone          #+#    #+#             */
/*   Updated: 2024/04/02 17:11:53 by deordone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**convert_to_dchar(t_env *lst_env)
{
	int		i;
	char	**new;
	t_env	*tmp;

	new = (char **)malloc(sizeof(char *) * ((ft_lstenv_size(lst_env))) + 1);
	if (!new)
		return (NULL);
	tmp = lst_env;
	while (tmp->next)
	{
		i = 0;
		new[i] = ft_strdup(tmp->line);
		i++;
		tmp = tmp->next;
	}
	new[i] = NULL;
	return (new);
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
			if (ft_strchr(tmp->line, (int) '='))
				ft_dprintf(STDOUT_FILENO,"%s=%s\n", tmp->var_name, tmp->var_content);
			tmp = tmp->next;
		}
	}
	else if (2 == i)
	{
		while (tmp)
		{
			ft_dprintf(STDOUT_FILENO, "declare -x %s=", tmp->var_name);
			if (!tmp->var_content)
				ft_dprintf(STDOUT_FILENO, "\"%s\"\n", "");
			else if (tmp->var_content && tmp->var_content[0] == '\"')
				ft_dprintf(STDOUT_FILENO, "%s\n", tmp->var_content);
			else
				ft_dprintf(STDOUT_FILENO, "\"%s\"\n", tmp->var_content);
			tmp = tmp->next;
		}
	}
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
		free((*lst)->var_content);
		free(*lst);
		*lst = temp;
	}
	*lst = NULL;
	return (0);
}

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

void	free_matrix(char **allsplit)
{
	int i;

	i = 0;
	while (allsplit[i])
	{
		free(allsplit[i]);
		i++;
	} 
	free(allsplit);
	allsplit = NULL;
}
