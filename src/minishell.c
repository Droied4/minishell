/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 10:20:59 by deordone          #+#    #+#             */
/*   Updated: 2024/03/11 15:27:02 by deordone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{

	t_shell sh;

	(void)av;
	(void)env;
	if (ac != 1)
		exit(1);
	while (1)
	{
		sh.line = readline(RED"🏓 PongShell ► "NC);
		add_history(sh.line);
		sh.tokens = generate_tokens(sh.line);
		sh.cmds = generate_tablecmd(sh.tokens);
		parse_all(&sh);
		execute_builtins(&sh, env);
		ft_deltoken(&sh.tokens);
		ft_delcmds(&sh.cmds);
		free(sh.line);
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
