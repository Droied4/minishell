/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 18:36:20 by avolcy            #+#    #+#             */
/*   Updated: 2024/05/28 21:50:22 by avolcy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
static int is_retokenizable(char *string)
{
	while (*string)
	{
		if (*string == 32 || (*string >= 9 && *string <= 13))
			return (1);
		string++;
	}
	return (0);
}

// t_token	*last_new_tok(t_token *token)
// {
// 	t_token *tmp = token;
// 	while (tmp->next)
// 		tmp = tmp->next;
// 	return tmp;		
// } 

size_t total_len_data(t_token *old_tok)
{
	size_t total_len;

	total_len = 0;
	while (old_tok)
	{
		total_len += ft_strlen(old_tok->data);
		old_tok = old_tok->next;
	}
	return (total_len);	
}



t_token	*retoken_ization(t_token *tok)
{
	t_token *tmp;
	t_token *new;

	tmp = tok;
	new = tok;
	while (tmp)
	{
		if(is_retokenizable(tmp->data))
			new =  generate_tokens(tmp->data);
		tmp = tmp->next;
	}
	free(tok->data);
	free(tok);
	tok = new;
	return (tok);
}
char *join_tokens(t_token *old_tok) 
{
	int i;
	int j;
	char *new_line;
	size_t len;

	len = total_len_data(old_tok);
	new_line = malloc(sizeof(char) * len + 1 + token_size(old_tok));
	while (old_tok)
	{
		if(old_tok && old_tok->data)
		{
			i = 0;
			j = 0;
			while (old_tok->data[i])
			{
				new_line[j++] = old_tok->data[i];
				i++;
			}
			if (old_tok)
				new_line[j++] = ' ';
			i = 0;
		}
		old_tok = old_tok->next;
	}
	printf("1-----------------%s\n", new_line);
	return (new_line);	
}

void	expansor(t_shell *sh)
{
	t_token	*tok;
	t_token	*tmp_tok;
	char	*tmp;
	// t_token	*tok_tmp;

	tok = sh->tokens;
	tmp_tok = sh->tokens;
	print_tokens(sh->tokens);
	while (tmp_tok)
	{
		if (!ft_strncmp("$?", tmp_tok->data, 2) || !ft_strncmp("$$", tmp_tok->data, 2))
			tmp_tok->data = special_cases(tmp_tok->data, sh->exit_status);
		else if (found_char(tmp_tok->data, '$'))
		{
			tmp = expand_data(sh, tmp_tok->data);
			if (tmp[0] != '\0')
			{
				free(tmp_tok->data);
				tmp_tok->data = tmp;
				tmp_tok->type = CMD;
			}
		}
		else if (found_char(tmp_tok->data, SQUOT) || found_char(tmp_tok->data, DQUOT))
		{
			tmp = aux_trim(tmp_tok->data);
			free(tmp_tok->data);
			tmp_tok->data = tmp;
			// tmp_tok->type = CMD;
		}
		tmp_tok = tmp_tok->next;
	}
	char *line = join_tokens(sh->tokens);
	printf("-----------------%s\n", line);
	sh->tokens = generate_tokens(line);
	// free_matrix(&line);
	// if(sh->tokens && sh->tokens->data && is_retokenizable(sh->tokens->data))
	// 	sh->tokens = retoken_ization(sh->tokens);
	print_tokens(sh->tokens);
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
