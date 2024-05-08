/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_arch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 12:37:44 by avolcy            #+#    #+#             */
/*   Updated: 2024/05/08 13:53:37 by avolcy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//variable name has to be one of those alphanum || digit || _
// check if var_name is ?NULL
// ❗️ function that add text to the content of a var 
// ❗️ export test=hola -> export test+=same export ="holasame"
// a function that fix the tokens correctly for the export to export all passed variable

int error_name_variable(char *variable_name)
{
    ft_dprintf(2, "PongShell : export: `%s': not a valid identifier", variable_name);
    return (1);
}

int is_correct(char *name)
{
    int i;

    i = 0;
    if (ft_isdigit(name[i]))
        return (error_name_variable(name));
    while (name[i])
    {
        if (ft_isalnum(name[i]) || name[i]== '_')
            i++;
        else
            return (0);
    }
    return (1);    
}

char	**convert_to_dchar(t_env *lst_env, char **env)
{
	int		i;
	char	**new;
	t_env	*tmp;

	if (!lst_env)
		return (env);//create_it or return the normal one ????
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
	//if (lst_env)
	//	ft_del_env(&lst_env);
	return (new);
}
