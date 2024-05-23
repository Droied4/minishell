/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 18:36:20 by avolcy            #+#    #+#             */
/*   Updated: 2024/05/21 20:33:42 by avolcy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expansion_final(t_shell *sh, char *str)
{
	int		i;
	char	**env_split;
	t_env	*var_node;
	char	*tmp;

	env_split = split_env_var(str);
	if (!env_split)
		return (NULL);
	i = 0;
	while (env_split[i])
	{
		var_node = NULL;
		if (env_split[i][0] == '$')
			var_node = found_var(&env_split[i][1], sh->env);
		if (var_node)
		{
			tmp = ft_strdup(var_node->var_content);
			free(env_split[i]);
			env_split[i] = tmp;
		}
		i++;
	}
	tmp = join_split(env_split);
	free_matrix(env_split);
	return (tmp);
}

char	*expand_string(t_shell *sh, char *str)
{
	char	*expanded;
	int		trimmed;

	trimmed = 0;
	if (str[0] == SQUOT)
		return (ft_strtrim(str, "\'"));
	if (str[0] == DQUOT)
	{
		str = ft_strtrim(str, "\"");
		trimmed = 1;
	}
	if (found_char(str, '$'))
	{
		expanded = expansion_final(sh, str);
		if (!ft_strncmp(expanded, str, ft_strlen(str)))
			expanded = ft_strdup("");
	}
	else
		expanded = ft_strdup(str);
	if (trimmed)
		free(str);
	return (expanded);
}

char	**split_quotes(char *str)
{
	int		i;
	int		position;
	int		words;
	char	**smart_split;

	words = count_words(str, 0, 0, 0);
	smart_split = malloc(sizeof(char *) * (words + 1));
	if (!smart_split)
		return (NULL);
	i = 0;
	position = 0;
	while (i < words)
	{
		smart_split[i] = ft_get_cpy(str, &position);
		str = &str[position];
		i++;
	}
	smart_split[i] = NULL;
	return (smart_split);
}

char	*expand_data(t_shell *sh, char *str)
{
	int		i;
	char	**smart_split;
	char	*tmp;

	smart_split = split_quotes(str);
	if (!smart_split)
		return (NULL);
	i = 0;
	while (smart_split[i])
	{
		tmp = expand_string(sh, smart_split[i]);
		if (!tmp)
			return (free_matrix(smart_split), NULL);
		free(smart_split[i]);
		smart_split[i] = tmp;
		i++;
	}
	tmp = join_split(smart_split);
	free_matrix(smart_split);
	return (tmp);
}

void	expansor(t_shell *sh)
{
	t_token	*tok;
	char	*tmp;

	tok = sh->tokens;
	while (tok)
	{
		if (!ft_strncmp("$?", tok->data, 2) || !ft_strncmp("$$", tok->data, 2))
			tok->data = special_cases(tok->data, sh->exit_status);
		else if (found_char(tok->data, '$'))
		{
			tmp = expand_data(sh, tok->data);
			free(tok->data);
			tok->data = tmp;
		}
		else if (found_char(tok->data, SQUOT) || found_char(tok->data, DQUOT))
		{
			tmp = aux_trim(tok->data);
			free(tok->data);
			tok->data = tmp;
		}
		tok = tok->next;
	}
	print_tokens(tok);
}

/*CURIOUS WAY OF CALLING FUNCTION
result = concat("'", concat(username, "'"));
EXPECTED RESULT : "'"$USER"'"
bash-3.2$ echo  test  |  wc  -c
		5
bash-3.2$
'hola'"$USER"'"$USER"'"'$USER'"
 echo 'hola'  "     $USER    "  " a " "${USER}"
$'USER' $"USER"
echo $TERM ""hola$USER$USET$USERm > $USERg
ambiguous redirect*/