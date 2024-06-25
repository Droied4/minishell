/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 18:36:20 by avolcy            #+#    #+#             */
/*   Updated: 2024/06/21 12:20:35 by deordone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*expansion_final(t_shell *sh, char **env_split, int i, char	*tmp)
{
	char	*tmp2;
	t_env	*var_node;

	if (!env_split)
		return (free_matrix(&env_split), NULL);
	while (env_split[++i])
	{
		var_node = NULL;
		if (env_split[i][0] == '$')
			var_node = found_var(&env_split[i][1], sh->env,
					ft_strlen(&env_split[i][1]), NULL);
		if (!var_node && env_split[i][0] == '$')
		{
			tmp = ft_strdup("");
			free(env_split[i]);
			env_split[i] = tmp;
		}
		if (var_node)
		{
			tmp = ft_strdup(var_node->var_content);
			free(env_split[i]);
			env_split[i] = tmp;
		}
	}
	return (tmp2 = join_split(env_split), free_matrix(&env_split), tmp2);
}

char	*expand_string(t_shell *sh, char *str, char *tmp, char *expanded)
{
	if (found_char(str, '$') && str[0] != SQUOT)
	{
		if (is_special_cases(str) != 0)
		{
			expanded = special_cases(str, sh->exit_status);
		}
		else
			expanded = expansion_final(sh, split_env_var(str), -1, NULL);
		if (expanded && found_char(expanded, '$'))
		{
			tmp = expansion_final(sh, split_env_var(expanded), -1, NULL);
			free(expanded);
			expanded = tmp;
		}
		if (!ft_strncmp(expanded, str, ft_strlen(str)))
		{
			free(expanded);
			expanded = ft_strdup("");
		}
	}
	else
		expanded = ft_strdup(str);
	return (expanded);
}

char	**split_quotes(char *str)
{
	int		i;
	int		words;
	int		position;
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
		if (!smart_split[i])
			return (free_matrix(&smart_split), NULL);
		str = str + position;
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
	char	*tmp2;

	smart_split = split_quotes(str);
	if (!smart_split)
		return (NULL);
	i = 0;
	while (smart_split[i])
	{
		tmp = expand_string(sh, smart_split[i], NULL, NULL);
		if (!tmp)
			return (free_matrix(&smart_split), NULL);
		free(smart_split[i]);
		smart_split[i] = tmp;
		i++;
	}
	tmp2 = join_split(smart_split);
	free_matrix(&smart_split);
	return (tmp2);
}

void	expansor(t_shell *sh)
{
	char	*tmp;

	if (sh->line[0] == '\0')
		return ;
	else if (found_char(sh->line, '$'))
	{
		tmp = expand_data(sh, sh->line);
		if (tmp[0] != '\0' || ft_strlen(tmp) == 0)
		{
			free(sh->line);
			sh->line = tmp;
		}
	}
	ft_deltoken(&sh->tokens);
	sh->tokens = generate_tokens(sh->line);
	if (found_char(sh->line, SQUOT) || found_char(sh->line, DQUOT))
		sh->tokens = quotes_removal(sh->tokens);
}
/*CURIOUS WAY OF CALLING FUNCTION
result = concat("'", concat(username, "'"));
EXPECTED RESULT : "'"$USER"'"
bash-3.2$ echo  test  |  wc  -c
		5
bash-3.2$
echo 'hola'"$USER"'"$USER"'"'$USER'"
 echo 'hola'  "     $USER    "  " a " "${USER}"
$'USER' $"USER"
echo $TERM ""hola$USER$USET$USERm > $USERg
ambiguous redirect*/
