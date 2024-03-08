/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 20:26:13 by avolcy            #+#    #+#             */
/*   Updated: 2024/03/08 23:45:12 by deordone         ###   ########.fr       */
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

void    execute_exit(t_shell *sh)
{
    (void)sh;
    if (sh->tokens)
        ft_deltoken(&sh->tokens);
    if (sh->env)
	    ft_del_env(&sh->env);
    //if (sh->line)
    //free(sh->line);
    clear_history();
    printf("hola exit\n");
    printf("exit\n");
    exit(0);
}



//    if (!ft_strncmp(looking->st_cmd->cmd, "export", 7))
 void    execute_builtins(t_shell *shell, char **env)
 {
    //char **test;
    if (!ft_strncmp(shell->tokens->data, "export", 7))
    {
        execute_export(shell,env);
        print_lst_env(shell->env, 2);
    }
    else if (!ft_strncmp(shell->tokens->data, "env", 4))
    {
        if (shell->env == NULL)
            shell->env = create_lst_env(env);
        else
            print_lst_env(shell->env, 1); 
        print_lst_env(shell->env, 1); 
    }
    else if (!ft_strncmp(shell->tokens->data, "exit", 5))
        execute_exit(shell);
//     if (!ft_strncmp(looking->cmd, "pwd", ft_strlen(looking->cmd)))
//         execute_pwd();
//     if (!ft_strncmp(looking->cmd, "echo", ft_strlen(looking->cmd)))
//         execute_echo();
//     else if (!ft_strncmp(looking->cmd, "cd", ft_strlen(looking->cmd)))
//         execute_cd();
//     else if (!ft_strncmp(looking->cmd, "unset", ft_strlen(looking->cmd)))
//         execute_unset();
 }
//test = convert_to_dchar(shell->env);
// int i = 0;
// while(test[i])
// {
//     printf("line---[%i]----[%s]\n",i, test[i]);
//     i++;
// }
// printf("hey where adding new one\n");
//execute_export(shell, convert_to_dchar(shell->env));
//printf("------------AFTER CREATE IT-----------\n");
//print_lst_env(shell->env, 2);
