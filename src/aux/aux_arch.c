/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_arch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 12:37:44 by avolcy            #+#    #+#             */
/*   Updated: 2024/05/30 21:39:29 by avolcy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	error_name_variable(char *str)
{
	ft_dprintf(2, "PongShell : export: `%s': not a valid identifier\n", str);
	return (1);
}

int	is_correct_name(char *name)
{
	int	i;

	i = 0;
	if (name[i] == '=' || !ft_isalpha(name[i]))
		return (error_name_variable(name));
	while (name[i] && name[i] != '=')
	{
		if (name[i] == '+' && name[i + 1] && name[i + 1] == '=')
			break ;
		if (ft_isalnum(name[i]) || name[i] == '_')
			i++;
		else
			return (error_name_variable(name));
	}
	return (0);
}

char	**convert_env_dchar(t_env *lst_env, char **env, int i)
{
	char	**new;
	t_env	*tmp;
	int		size;

	if (!lst_env)
		lst_env = create_lst_env(env);
	print_lst_env(lst_env, 0);
	size = ft_lstenv_size(lst_env);
	new = (char **)malloc(sizeof(char *) * (size + 1));
	if (!new)
		return (NULL);
	tmp = lst_env;
	while (tmp->next)
	{
		new[i] = ft_strdup(tmp->line);
		if (!new[i])
		{
			ft_del_env(&lst_env);
			return (free_matrix(&new), NULL);
		}
		i++;
		tmp = tmp->next;
	}
	return (new[i] = NULL, new);
}

char	*quotes_removal_master(char *cmd_line, int i, int j)
{
	char	**smart_split;

	if (!cmd_line)
		return (NULL);
	smart_split = split_quotes(cmd_line);
	if (!smart_split)
		return (NULL);
	while (smart_split[i])
	{
		if (smart_split[i][j])
		{
			if (smart_split[i][j] == SQUOT)
				smart_split[i] = (ft_strtrim(smart_split[i], "\'"));
			else if (smart_split[i][j] == DQUOT)
				smart_split[i] = ft_strtrim(smart_split[i], "\"");
		}
		i++;
	}
	free(cmd_line);
	cmd_line = join_split(smart_split);
	return (free_matrix(&smart_split), cmd_line);
}

t_token	*quotes_removal(t_token *tokens)
{
	t_token	*tok;

	tok = tokens;
	while (tok)
	{
		tok->data = quotes_removal_master(tok->data, 0, 0);
		tok = tok->next;
	}
	return (tokens);
}
