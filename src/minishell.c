/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 10:20:59 by deordone          #+#    #+#             */
/*   Updated: 2024/03/01 19:16:34 by avolcy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_shell	sh;
	t_env	*s_env;
	char	*line;
	
	(void)av;
	if (ac != 1)
		exit(1);
	while (1)
	{
		line = readline(RED"🏓 PongShell ► "NC);
		add_history(line);
		sh.tokens = generate_tokens(line);
		printlst(sh.tokens);
		//parse_all(&sh);
		if (!ft_strncmp(sh.tokens->data, "env", 4))
		{
			s_env = create_lst_env(env);
			print_lst_env(s_env, 1);
		}
		else if (!ft_strncmp(sh.tokens->data, "export", 7))
		{
			s_env = create_lst_env(env);
			if (sh.tokens->next)
				exporting_var(sh, &s_env);
			print_lst_env(s_env, 2);
		}
		else if (ft_strncmp(line, "exit", 4) == 0)
		{
			printf("exit\n");
			//free(line);
			exit(0);
		}
		free(line);
	}
	ft_del(&sh.tokens);
	ft_del_env(&s_env);
	return (0);
}
