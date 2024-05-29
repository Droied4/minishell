/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 18:36:20 by avolcy            #+#    #+#             */
/*   Updated: 2024/05/29 22:10:40 by avolcy           ###   ########.fr       */
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
	
	if (found_char(str, '$') && str[0] != SQUOT)
	{
		expanded = expansion_final(sh, str);
		if (!ft_strncmp(expanded, str, ft_strlen(str)))
			expanded = ft_strdup("");
	}
	else
		expanded = ft_strdup(str);
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

//a function that clean the line doing the same split process jut to remove the quotes
//char *quote_removal(char *cmd_line)
//1 - smart_split
//2 - ft_strtrim
char *quotes_removal(char *cmd_line)
{
	int i = 0;
	int j = 0;
	char **smart_split;

	if (!cmd_line)
		return (NULL);
	smart_split = split_quotes(cmd_line);
	while (smart_split[i])
	{
		if (smart_split[i][j])
		{
		ft_dprintf(1, "before removal number[%d]-----line[%s]\n", i, smart_split[i]);
			if (smart_split[i][j] == SQUOT)
				smart_split[i] = (ft_strtrim(smart_split[i], "\'"));
			else if (smart_split[i][j] == DQUOT)
				smart_split[i] = ft_strtrim(smart_split[i], "\"");
		ft_dprintf(1, "after removal number[%d]-----line[%s]\n", i, smart_split[i]);
		}

		i++;
	}
	free(cmd_line);
	cmd_line = join_split(smart_split);
	printf("this is new_cmdline----%s\n", cmd_line);
	return (cmd_line);
}

void	expansor(t_shell *sh)
{
	t_token *tok;
	char	*tmp;
	char	*tmp_line;

	print_tokens(sh->tokens);
	if (!ft_strncmp("$?", sh->line, 2) || !ft_strncmp("$$", sh->line, 2))
		sh->line = special_cases(sh->line, sh->exit_status);
	else if (found_char(sh->line, '$'))
	{
		tmp = expand_data(sh, sh->line);
		if (tmp[0] != '\0')
		{
			free(sh->line);
			sh->line = tmp;
		}
		//printf("----right after expansion-------------%s\n", sh->line);
	}
	tok= sh->tokens;
	tmp_line = quotes_removal(sh->line);
	printf("this is new_cmdl   ine----%s\n", tmp_line);
	sh->line = tmp_line;
	sh->tokens = generate_tokens(sh->line);
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
