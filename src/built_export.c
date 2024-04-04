/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 18:51:22 by avolcy            #+#    #+#             */
/*   Updated: 2024/04/04 19:12:14 by avolcy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*found_var(char *var, t_env *lst)
{
	size_t	len;
	t_env	*tmp;
	char	**line;

	len = 0;
	line = ft_split(var, '=');
	tmp = lst;
	while (tmp)
	{
		if (ft_strlen(line[0]) > ft_strlen(tmp->var_name))
			len = ft_strlen(line[0]);
		else
			len = ft_strlen(tmp->var_name);
		if (ft_strncmp(line[0], tmp->var_name, len) == 0)
		{
			free_matrix(line);
			return (tmp);
		}
		tmp = tmp->next;
	}
	free_matrix(line);
	return (NULL);
}

static void	update_var(char *s, t_env *var_node)
{
	char	**split;

	var_node->line = ft_strdup(s);
	split = ft_split(var_node->line, '=');
	var_node->var_name = split[0];
	var_node->var_content = split[1];
	free(split);
}

t_env	*exporting_var(t_shell sh, t_env **lst_env)
{
	t_env	*last;
	t_env	*new;

	new = NULL;
	// check_exp_variable(sh.tokens);
	while (sh.tokens)
	{
		sh.tokens = sh.tokens->next;
		if (sh.tokens)
		{
			new = found_var(sh.tokens->data, *lst_env);
			if (!new)
			{
				new = create_envnode(sh.tokens->data);
				if (!new)
					return (NULL);
				last = *lst_env;
				while (last->next)
					last = last->next;
				last->next = new;
				new->prev = last;
			}
			else
				update_var(sh.tokens->data, new);
		}
	}
	return (*lst_env);
}
// case export hola="como estas" que tal como="vamos"
// static void    check_tokens(t_token *tok)
// {
//     t_token *tmp;
//     int     count;

//     count = 0;
//     tmp = tok;
//     while (tmp)
//     {
//         printf("this is the token[%d]--->[%d]", count, tmp->index);
//         count++;
//         tmp = tmp->next;
//     }

// }

void	execute_export(t_shell *sh, char **env)
{
	int	flag;

	flag = 0;
	// ❗️fix token function
	// = is found, next char is " || next char is null  but tok->next[0] is "
	if (sh->tokens->next == NULL && sh->env == NULL)
		sh->env = create_lst_env(env);
	else if (sh->tokens->next == NULL && sh->env != NULL)
	{
		// to put in alphabetic order function to do
		print_lst_env(sh->env, 2);
		flag = 1;
	}
	else if (sh->tokens->next != NULL && sh->env == NULL)
	{
		sh->env = create_lst_env(env);
		sh->env = exporting_var(*sh, &sh->env);
	}
	else if (sh->tokens->next != NULL && sh->env != NULL)
	{
		sh->env = exporting_var(*sh, &sh->env);
	}
	if (flag == 0)
		print_lst_env(sh->env, 2);
}
// while check_order == ko
// check 1st charact
// if 1st char == 1st->next char move to 2nd and so one