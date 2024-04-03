/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 20:26:13 by avolcy            #+#    #+#             */
/*   Updated: 2024/04/03 18:16:11 by avolcy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Your shell must implement the following builtins:
// ◦ echo with option -n
// ◦ cd with only a relative or absolute path
// ◦ pwd with no options
// ◦ export with no options
// ◦ unset with no options
// ◦ env with no options or arguments
// ◦ exit with no options

#include "minishell.h"

void	execute_exit(t_shell *sh)
{
	if (sh->tokens)
		ft_deltoken(&sh->tokens);
	if (sh->env)
		ft_del_env(&sh->env);
	if (sh->line)
		free(sh->line);
	clear_history();
	printf("exit\n");
	exit(0);
}

//segv if env -i ./minishell && env passed
void	execute_builtins(t_shell *shell, char **env)
{
	if (shell->tokens && shell->tokens->data)
	{
		if (!ft_strncmp(shell->tokens->data, "cd", 3))
			execute_cd(shell, env);
		else if (!ft_strncmp(shell->tokens->data, "echo", 5))
			execute_echo(shell);
		else if (!ft_strncmp(shell->tokens->data, "env", 4))
			execute_env(shell, env);
		else if (!ft_strncmp(shell->tokens->data, "exit", 5))
			execute_exit(shell);
		else if (!ft_strncmp(shell->tokens->data, "export", 7))
			execute_export(shell, env);
		else if (!ft_strncmp(shell->tokens->data, "pwd", 4))
			execute_pwd();
		else if (!ft_strncmp(shell->tokens->data, "unset", 7))
		{
			if (shell->tokens->next == NULL)
				return ;
			execute_unset(&shell, env);
			print_lst_env(shell->env, 1);//test puurposes;
		}
	}
}
