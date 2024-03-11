/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 10:20:59 by deordone          #+#    #+#             */
/*   Updated: 2024/03/11 17:10:25 by avolcy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	main(int ac, char **av, char **env)
{

	t_shell	sh;
	//t_env	*s_env;
	//char	*line;
	
	(void)av;
	(void)ac;
	init_shell(&sh);
	while (1)
	{
		// if I had the line variable in the struct in order to free it after
		sh.line = readline(RED"🏓 PongShell ► "NC);
		if (!ft_strncmp("🏓 PongShell ► ", sh.line, 15))//to solve enter
			return (1);//not working as expected but will figured it out soon
		add_history(sh.line);
		sh.tokens = generate_tokens(sh.line);
		print_tokens(sh.tokens);
		sh.cmds = generate_tablecmd(sh.tokens);
		parse_all(&sh);
		execute_builtins(&sh, env);
		if (sh.line)
			free(sh.line);
		//ft_deltoken(&sh.tokens);
		//ft_delcmds(&sh.cmds);
	}
	return (0);
}
/*
//estas intentando hacer el lexer que separe tambien los metacaracteres
static int len_newstr(char *s, char **lim)
{
	int i;
	int j;
	int h;
	int len;

	i = -1;
	len = 0;
	while (s[++i])
	{
		j = -1;
		while (lim[++j])
		{
			h = -1;
			while (lim[j][++h])
			{
				if (s[i] == lim[j][h])
					len++;
			}
		}
	}
	return (len);
}



int main(void)
{
	char **input;
	input = ft_split(STR_REDIR, ' ');
	printf("num -> %i\n", len_newstr("<<", input));
	return (0);	
}*/
