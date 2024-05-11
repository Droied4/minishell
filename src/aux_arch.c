/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_arch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 12:37:44 by avolcy            #+#    #+#             */
/*   Updated: 2024/05/10 20:48:43 by avolcy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int error_name_variable(char *str)
{
    ft_dprintf(2, "PongShell : export: `%s': not a valid identifier\n", str);
    return (1);
}

int is_correct_name(char *name)
{
    int i;

    i = 0;
    if (name[i] == '=' || ft_isdigit(name[i]))
        return (error_name_variable(name));
    while (name[i] && name[i] != '=')
    {
        if (ft_isalnum(name[i]) || name[i]== '_')
            i++;
        else
            return (error_name_variable(name));
    }
    return (0);    
}

char	**convert_env_dchar(t_env *lst_env, char **env)
{
	int		i;
	char	**new;
	t_env	*tmp;

	if (!lst_env)
		lst_env = create_lst_env(env);
	new = (char **)malloc(sizeof(char *) * ((ft_lstenv_size(lst_env))) + 1);
	if (!new)
		return (NULL);
	tmp = lst_env;
	i = 0;
	while (tmp->next)
	{
		new[i] = ft_strdup(tmp->line);
		i++;
		tmp = tmp->next;
	}
	new[i] = NULL;
	return (new);
}
