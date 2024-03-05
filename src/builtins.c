/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 20:26:13 by avolcy            #+#    #+#             */
/*   Updated: 2024/03/05 21:26:49 by avolcy           ###   ########.fr       */
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

void    execute_exit(void)
{
    printf("hola exit\n");
    printf("exit\n");
    exit(0);
}

//    if (!ft_strncmp(looking->st_cmd->cmd, "export", 7))
 void    execute_builtins(t_shell *looking, char **env)
 {
    printf("hola builtinnnnn\n");
    if (!ft_strncmp(looking->tokens->data, "export", 7))
        execute_export(looking, env);
    else if (!ft_strncmp(looking->tokens->data, "env", 4))
        create_lst_env(env);
    else if (!ft_strncmp(looking->tokens->data, "exit", 5))
        execute_exit();
     else
         printf(RED"🏓 PongShell: "NC"%s: command not found", looking->st_cmd->cmd);
//     if (!ft_strncmp(looking->cmd, "pwd", ft_strlen(looking->cmd)))
//         execute_pwd();
//     if (!ft_strncmp(looking->cmd, "echo", ft_strlen(looking->cmd)))
//         execute_echo();
//     else if (!ft_strncmp(looking->cmd, "cd", ft_strlen(looking->cmd)))
//         execute_cd();
//     else if (!ft_strncmp(looking->cmd, "unset", ft_strlen(looking->cmd)))
//         execute_unset();
 }