/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 20:26:13 by avolcy            #+#    #+#             */
/*   Updated: 2024/05/27 17:20:55 by avolcy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	- exit without nothing $? = 0
	- with one arg, takes that arg if it's only a number (exit 42, $? = 42)
	- if characters are found in the first arg like 42a, its does exit
		but msg = bash: exit: 42a: numeric argument required ($? = 255)
	- more than one arg is passed and the first doesn't have any rare characters
		it doesn't process the exit but print msg = bash: 
		exit: too many arguments ($? = 1)
*/

int	token_size(t_token *tokens)
{
	int	len;

	len = 0;
	while (tokens)
	{
		len++;
		tokens = tokens->next;
	}
	return (len);
}

void	normal_exit(t_shell *sh, int error_code)
{
	free_matrix(&sh->matriz_env);
	ft_deltoken(&sh->tokens);
	ft_del_redirs(&sh->pro.r);
	ft_del_words(&sh->pro.w);
	ft_del_env(&sh->env);
	clear_history();
	free(sh->line);
	exit(error_code);
}

int	all_chars_digit(char *data)
{
	int	i;

	i = 0;
	while (data[i])
	{
		if (!ft_isdigit(data[i]))
			return (-1);
		i++;
	}
	return (1);
}

/*
	1 - exit; exits and ($? = 0)✅
	2 - exit 42; exits and ($? = 42)✅
	3 - "exit 42q" or "exit s sgg gs"; exits and ($? = 255)✅
		prints : numeric argument required ✅
	4 - "exit 42 42"; doesn't exit ($? = 1) $? ✅
		prints : too many arguments ✅
*/
int	execute_exit(t_shell *sh)
{
	int	size;
	int	status;

	status = 0;
	size = token_size(sh->tokens);
	if (size > 2 && all_chars_digit(sh->tokens->next->data) == 1)
	{
		status = 1;
		ft_dprintf(2, TOO_MANY_ARG);
	}
	else if (size == 2 && all_chars_digit(sh->tokens->next->data) == 1)
		normal_exit(sh, ft_atoi(sh->tokens->next->data));
	else if (size >= 2 && all_chars_digit(sh->tokens->next->data) == -1)
	{
		ft_dprintf(1, "Pongshell: %s: " NUM_ARG_REQ, sh->tokens->next->data);
		normal_exit(sh, 255);
	}
	else
		normal_exit(sh, sh->exit_status);
	return (status);
}

int	execute_builtins(t_shell *shell, char **env)
{
	int	status;

	status = 0;
	if (shell->tokens && shell->tokens->data)
	{
		if (!ft_strncmp(shell->tokens->data, "cd", 3))
			status = execute_cd(shell, NULL, env);
		else if (!ft_strncmp(shell->tokens->data, "echo", 5))
			execute_echo(shell);
		else if (!ft_strncmp(shell->tokens->data, "env", 4))
			execute_env(shell, env);
		else if (!ft_strncmp(shell->tokens->data, "exit", 5))
			status = execute_exit(shell);
		else if (!ft_strncmp(shell->tokens->data, "export", 7))
			execute_export(shell, env);
		else if (!ft_strncmp(shell->tokens->data, "pwd", 4))
			status = execute_pwd();
		else if (!ft_strncmp(shell->tokens->data, "unset", 7))
		{
			if (shell->tokens->next == NULL)
				return (status);
			execute_unset(&shell, NULL, env);
		}
	}
	return (status);
}
