/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 10:20:59 by deordone          #+#    #+#             */
/*   Updated: 2024/03/05 15:41:28 by avolcy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	sh;

int	main(int ac, char **av, char **env)
{
//	t_shell	sh;
	//t_env	*s_env;
	char	*line;
	
	(void)av;
	if (ac != 1)
		exit(1);
	while (1)
	{
		line = readline(RED"🏓 PongShell ► "NC);
		if (!ft_strncmp("🏓 PongShell ► ", line, 15))//to solve enter
			return (1);//not working as expected but will figured it out soon
		add_history(line);
		sh.tokens = generate_tokens(line);
		printlst(sh.tokens);
		execute_builtins(&sh, env);
		//parse_all(&sh);
		// if (!ft_strncmp(sh.tokens->data, "env", 4))
		// {
		// 	if (flag <= 0)
		// 		s_env = create_lst_env(env);
		// 	print_lst_env(s_env, 1);
		// }
		// else if (!ft_strncmp(sh.tokens->data, "export", 7))
		// {
		// 	execute_builtins(&sh, env);
		// 	// if (sh.tokens->next)
		// 	// {
		// 	// 	if (s_env->next)
		// 	// 		s_env = create_lst_env(env);
		// 	// 	s_env = exporting_var(sh, &s_env);
		// 	// 	flag = 1;
		// 	// }
		// 	// else if (!sh.tokens->next && flag > 0)
		// 	// 	s_env = create_lst_env(convert_to_dchar(s_env));
		// 	// else
		// 	// 	s_env = create_lst_env(env);
		// 	// print_lst_env(s_env, 2);
		// }
		// else if (ft_strncmp(line, "exit", 5) == 0)
		// {
		// 	printf("exit\n");
		// 	//free(line);
		// 	exit(0);
		// }
		free(line);
	}
	// ft_del(&sh.tokens);
	// ft_del_env(&s_env);
	return (0);
}
