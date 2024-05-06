/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 18:36:20 by avolcy            #+#    #+#             */
/*   Updated: 2024/05/02 19:31:19 by avolcy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*he token
❗️ UNCLOSE ENTRY TO SUPERVISED , DEIVID*/
char	*expansion_var(t_shell *sh, char *data, int i)
{
	char	*new;
	char	**data_sp;
	t_env	*var_node;

	data_sp = ft_split(data, '$');
	if (!data_sp)
		return (NULL);
	new = NULL;
	while (data_sp[++i])
	{
		var_node = found_var(data_sp[i], sh->env);
		if (var_node)
			new = ft_strjoin2(new, var_node->var_content);
		else if (!var_node)
			new = ft_strjoin2(new, data_sp[i]);
	}
	if (ft_strncmp(remove_char(data, '$', 0), new, ft_strlen(new)) == 0)
		new = ft_strdup("");
	if (data_sp)
		free_matrix(data_sp);
    
    // ft_del_env(&var_node);
    printf("inside of EEEEEEEXP add is {%p}\n", data);
	return (free(data), new);
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

static char	*compare_it_before(t_shell *sh, char *s)
{
	char	*new_s;

	if (found_char(s, SQUOT) || found_char(s, DQUOT))
	{
		if (found_char(s, SQUOT) && s[0] != '\'')
			s = remove_char(s, SQUOT, 0);
		else if (found_char(s, DQUOT) && s[0] != '\"')
			s = remove_char(s, DQUOT, 0);
		else if (found_char(s, DQUOT) && s[0] == '\"')
			return (remove_char(s, '\"', 0));
		new_s = remove_char(s, '$', 0);
		return (new_s);
	}
	new_s = expansion_var(sh, s, -1);
	// s = remove_char(s, '$', 0);
	// if (ft_strncmp(s, new_s, ft_strlen(new_s)) == 0)
	// 	new_s = ft_strdup("");
	return (new_s);
}

static char	*string_modifier(t_shell *sh, char *s, char **env)
{
	char	*new_s;

	new_s = NULL;
	if (!sh->env)
		sh->env = create_lst_env(env);
	if (s[0] == SQUOT)
		new_s = remove_char(s, SQUOT, 0);
	else if (ft_strlen(s) == 2 && s[0] == DQUOT && s[1] == DQUOT)
		return (ft_strdup(""));
	else if (s[0] == DQUOT && found_char(s, '$'))
	{
		new_s = remove_char(s, DQUOT, 0);
		if (found_char(new_s, SQUOT))
		{
			new_s = add_dollar_case(new_s, 0, 0);
			new_s = expansion_var(sh, new_s, -1);
		}
		else
			new_s = expansion_var(sh, add_dollar_case(new_s, 0, 0), -1);
	}
	else if (found_char(s, '$') || found_char(s, DQUOT))
		new_s = compare_it_before(sh, s);
	else
		new_s = ft_strdup(s);
	printf("this is inside of modifier final result is {%s}\n", new_s);
	return (new_s);
}
// char	*filter_data(t_shell *sh, char *s, char **env, int pos)
// {

// }
char	*filter_data(t_shell *sh, char *s, char **env, int pos)
{
	char	*new;
	char	*save;
	char 	*tmp;

	new = NULL;
	tmp = s;
	//save = my_allocation(ft_strlen(s));
	// printf("\n\tthis is inside of filter data \n\t|---senter---(%p)\n\t|--save--(%p)\n", s, save);
	while (*tmp != '\0')
	{
		// save[0] = '\0';
		if (*tmp == SQUOT || *tmp == DQUOT)
		{
			pos = find_next_quote(tmp, *tmp);
			// ft_strlcpy(save, tmp, pos + 1);
            save = ft_substr(tmp, 0, pos);
		}
		else
		{
			pos = find_next_pos(tmp);
			// ft_strlcpy(save, tmp, pos + 1);
            save = ft_substr(tmp, 0, pos);
		}
		save = string_modifier(sh, save, env);
		if (save)
			new = ft_strjoin2(new, save);
		tmp = tmp + pos;
		pos = 0;
	}
	printf("\n\tthis is inside of filter data \n\t|---sleave-{%s}--(%p)\n\t|--save--(%p)\n", new, s, save);
	free(save);
	return (new);
}

void	expansor(t_shell *sh, char **env)
{
	t_token	*tok;
	(void)env;
	tok = sh->tokens;
	print_tokens(sh->tokens);
	while (tok)
	{
		printf("this is the tok before EXP--->[%s] and its address is [%p]\n", tok->data, tok->data);
		if (!ft_strncmp("$?", tok->data, 2) || !ft_strncmp("$$", tok->data, 2))
			tok->data = special_cases(tok->data, sh->exit_status);
		else if (found_char(tok->data, SQUOT) || found_char(tok->data, DQUOT)
			|| found_char(tok->data, '$'))
		{
			char *new = malloc(ft_strlen(tok->data));
			ft_strlcpy(new, tok->data, ft_strlen(tok->data));
			ft_clean_up(&tok->data);
			tok->data = filter_data(sh, new, env, 0);
			free(new);
		}
		printf("this is the tok after EXP--->[%s] and its address is [%p]\n", tok->data, tok->data);
		tok = tok->next;
	}
	print_tokens(sh->tokens);
}