/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 20:26:13 by avolcy            #+#    #+#             */
/*   Updated: 2024/03/19 20:44:24 by avolcy           ###   ########.fr       */
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

void	execute_builtins(t_shell *shell, char **env)
{
	if (shell->tokens && shell->tokens->data)
	{
		if (!ft_strncmp(shell->tokens->data, "export", 7))
			execute_export(shell, env);
		else if (!ft_strncmp(shell->tokens->data, "env", 4))
		{
			if (shell->env == NULL)
			{
				shell->env = create_lst_env(env);
				print_lst_env(shell->env, 1);
			}
			else
				print_lst_env(shell->env, 1);
		}
		else if (!ft_strncmp(shell->tokens->data, "pwd", 4))
			execute_pwd();
		else if (!ft_strncmp(shell->tokens->data, "exit", 5))
			execute_exit(shell);
		else if (!ft_strncmp(shell->tokens->data, "unset", 7))
		{
			if (shell->tokens->next == NULL)
				return ;
			execute_unset(&shell, env);
			print_lst_env(shell->env, 1);
		}
		else if (!ft_strncmp(shell->tokens->data, "cd", 3))
			execute_cd();
		//     if (!ft_strncmp(looking->cmd, "echo", ft_strlen(looking->cmd)))
		//         execute_echo();
	}
}