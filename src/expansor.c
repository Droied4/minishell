/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:04:47 by avolcy            #+#    #+#             */
/*   Updated: 2024/04/27 12:53:36 by avolcy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


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
			new = ft_strjoin2(new, ft_strdup(var_node->var_content));
		else if (!var_node)
			new = ft_strjoin2(new, data_sp[i]);
	}
	if (data_sp)
		free_matrix(data_sp);
    printf("inside of EEEEEEEXP add is {%p}\n", data);
	return (new);
}

/*CURIOUS WAY OF CALLING FUNCTION
result = concat("'", concat(username, "'"));
EXPECTED RESULT : "'"$USER"'"
bash-3.2$ echo  test  |  wc  -c
		5
bash-3.2$
'hola'"$USER"'"$USER"'"'$USER'"
 echo 'hola'  "     $USER    "  " a " "${USER}"
$'USER' $"USER"*/

static char	*compare_it_before(t_shell *sh, char *s)
{
	char	*new_s;

	if (found_char(s, SQUOT) || found_char(s, DQUOT))
	{
		if (found_char(s, SQUOT) && s[0] != '\'')
			s = remove_char(s, SQUOT, 0);
		else if (found_char(s, DQUOT) && s[0] != '\"')
			s = remove_char(s, DQUOT, 0);
		new_s = remove_char(s, '$', 0);
		return (new_s);
	}
	new_s = expansion_var(sh, s, -1);
	s = remove_char(s, '$', 0);
	if (ft_strncmp(s, new_s, ft_strlen(new_s)) == 0)
		new_s = ft_strdup("");
	return (new_s);
}

static char	*string_modifier(t_shell *sh, char *s, char **env)
{
	char	*new_s;

	new_s = s;
	if (!sh->env)
		sh->env = create_lst_env(env);
	if (s[0] == SQUOT)
		new_s = remove_char(s, SQUOT, 0);
	else if (s[0] == DQUOT)
	{
		if (ft_strlen(s) == 2 && s[0] == DQUOT && s[1] == DQUOT)
			return (ft_strdup(""));
		new_s = remove_char(s, DQUOT, 0);
		if (found_char(new_s, SQUOT))
		{
			new_s = add_dollar_case(new_s, 0, 0);
			new_s = expansion_var(sh, new_s, -1);
		}
		else
			new_s = expansion_var(sh, add_dollar_case(new_s, 0, 0), -1);
	}
	else if (found_char(s, '$'))
		new_s = compare_it_before(sh, s);
	return (free(s), new_s);
}

char	*filter_data(t_shell *sh, char *s, char **env, int pos)
{
	char	*new;
	char	*save;

	new = NULL;
	save = my_allocation(ft_strlen(s));
	while (*s != '\0')
	{
		save[0] = '\0';
		if (*s == SQUOT || *s == DQUOT || *s == '$')
		{
			pos = find_next_quote(s, *s);
			save = ft_substr(s, 0, (size_t)pos);
		}
		else
		{
			pos = find_next_pos(s);
			save = ft_substr(s, 0, (size_t)pos);
		}
		save = string_modifier(sh, save, env);
		if (save)
			new = ft_strjoin2(new, save);
		s = s + pos;
		pos = 0;
	}
	return (new);
}

void	expansor(t_shell *sh, char **env)
{
	t_token	*tok;

	tok = sh->tokens;
	while (tok)
	{
		printf("this is the tok before EXP--->[%s]\n", tok->data);
		if (!ft_strncmp("$?", tok->data, 2) || !ft_strncmp("$$", tok->data, 2))
			tok->data = special_cases(tok->data, sh->exit_status);
		else if (found_char(tok->data, SQUOT) || found_char(tok->data, DQUOT)
			|| found_char(tok->data, '$'))
		{
			tok->data = filter_data(sh, tok->data, env, 0);
		}
		printf("this is the tok after EXP--->[%s]\n", tok->data);
		tok = tok->next;
	}
}
