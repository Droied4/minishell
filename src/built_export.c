/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 18:51:22 by avolcy            #+#    #+#             */
/*   Updated: 2024/04/01 13:16:39 by avolcy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	found_var(char *var, t_env *lst, int *i)
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
			*i += 1;
			free_matrix(line);
			return (1);
		}
		else
		{
			*i += 1;
			tmp = tmp->next;
		}
	}
	free_matrix(line);
	return (0);
}

static t_env	*update_var(char *s, t_env **lst, int pos)
{
	int		i;
	char	**split;
	t_env	*newlst;

	i = 0;
	newlst = *lst;
	while (++i < pos && newlst)
		newlst = newlst->next;
	newlst->line = ft_strdup(s);
	split = ft_split(newlst->line, '=');
	newlst->var_name = split[0];
	newlst->var_content = split[1];
	free(split);
	return (*lst);
}

t_env	*exporting_var(t_shell sh, t_env **lst_env)
{
	int		i;
	t_env	*last;
	t_env	*new;

	new = NULL;
	// check_exp_variable(sh.tokens);
	while (sh.tokens)
	{
		i = 0;
		sh.tokens = sh.tokens->next;
		if (sh.tokens)// && is_correct(sh.tokens->data))
		{
			if (!found_var(sh.tokens->data, *lst_env, &i))
				new = create_envnode(sh.tokens->data);
			else
				*lst_env = update_var(sh.tokens->data, lst_env, i);
			if (new)
			{
				last = *lst_env;
				while (last->next)
					last = last->next;
				last->next = new;
				new->prev = last;
			}
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