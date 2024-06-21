/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 18:51:22 by avolcy            #+#    #+#             */
/*   Updated: 2024/06/21 11:54:55 by deordone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*found_var(char *cmd_line, t_env *lst, size_t len, char *tmp_l)
{
	t_env	*tmp;
	char	**line;

	if (len == 0)
		return (NULL);
	line = ft_split(cmd_line, '=');
	if (line[0][ft_strlen(line[0]) - 1] == '+')
	{
		tmp_l = trimmer_quotes(line[0], (int) '+');
		free(line[0]);
		line[0] = tmp_l;
	}
	tmp = lst;
	while (tmp)
	{
		len = ft_strlen(tmp->var_name);
		if (ft_strlen(line[0]) > ft_strlen(tmp->var_name))
			len = ft_strlen(line[0]);
		if (ft_strncmp(line[0], tmp->var_name, len + 1) == 0)
			return (free_matrix(&line), tmp);
		tmp = tmp->next;
	}
	if (line)
		free_matrix(&line);
	return (NULL);
}

static void	update_var(char *s, t_env *var_node)
{
	char	**split;
	char	*tmp;
  char  *new_cont;

	free(var_node->line);
  var_node->line = ft_strdup(s);
  if (!found_char(var_node->line, '='))
    return ;
	split = ft_split(var_node->line, '=');
  if (split[0][ft_strlen(split[0]) - 1] == '+' && split[1] != NULL)
	{
		if (split[1][0] == SQUOT || split[1][0] == DQUOT)
		{
			tmp = trimmer_quotes(split[1], split[1][0]);
			free(split[1]);
			split[1] = tmp;
		}
		new_cont = ft_strjoin2(&var_node->var_content, split[1]);
	}
	else if (!split[1])
		new_cont = ft_strdup("");
  else
		new_cont = ft_strdup(split[1]);
  if (var_node->var_content)
    free(var_node->var_content);
  var_node->var_content = new_cont;
	free_matrix(&split);
}

static void	add_node_to_lstenv(t_env **lstenv, t_env **new)
{
	t_env	*last;

	last = *lstenv;
	while (last->next)
		last = last->next;
	last->next = *new;
	(*new)->prev = last;
}

t_env	*exporting_var(t_shell sh, t_env **lst_env, t_env *new)
{
	while (sh.tokens)
	{
		sh.tokens = sh.tokens->next;
		if (sh.tokens && !is_correct_name(sh.tokens->data))
		{
			new = found_var(sh.tokens->data, *lst_env,
					ft_strlen(sh.tokens->data), NULL);
			if (!new)
			{
				new = create_envnode(sh.tokens->data);
				if (!new)
					return (NULL);
				add_node_to_lstenv(lst_env, &new);
			}
			else
				update_var(sh.tokens->data, new);
		}
	}
	return (*lst_env);
}

/*to put in alphabetic order function to do
while check_order == ko
check 1st charact
if 1st char == 1st->next char move to 2nd and so one*/

void	execute_export(t_shell *sh, char **env)
{
	int	flag;

	flag = 0;
	if (sh->tokens->next == NULL && sh->env == NULL)
		sh->env = create_lst_env(env);
	else if (sh->tokens->next == NULL && sh->env != NULL)
	{
		print_lst_env(sh->env, 2);
		flag = 1;
	}
	else if (sh->tokens->next != NULL && sh->env == NULL)
	{
		sh->env = create_lst_env(env);
		sh->env = exporting_var(*sh, &sh->env, NULL);
	}
	else if (sh->tokens->next != NULL && sh->env != NULL)
	{
		flag = 1;
		sh->env = exporting_var(*sh, &sh->env, NULL);
	}
	if (flag == 0)
		print_lst_env(sh->env, 2);
}
