/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 20:26:13 by avolcy            #+#    #+#             */
/*   Updated: 2024/03/01 16:43:12 by avolcy           ###   ########.fr       */
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

//  void    execute_builtins(t_shell *looking)
//  {
//     if (!ft_strncmp(looking->cmd, "pwd", ft_strlen(looking->cmd)))
//         execute_pwd();
//     if (!ft_strncmp(looking->cmd, "echo", ft_strlen(looking->cmd)))
//         execute_echo();
//     else if (!ft_strncmp(looking->cmd, "cd", ft_strlen(looking->cmd)))
//         execute_cd();
//     else if (!ft_strncmp(looking->cmd, "export", ft_strlen(looking->cmd)))
//         execute_export();
//     else if (!ft_strncmp(looking->cmd, "unset", ft_strlen(looking->cmd)))
//         execute_unset();
//     if (!ft_strncmp(looking->cmd, "env", ft_strlen(looking->cmd)))
//         display_env();
//     else if (!ft_strncmp(looking->cmd, "exit", ft_strlen(looking->cmd)))
//         execute_exit();
//     else
//         printf(RED"🏓 PongShell: "NC"%s: command not found", looking->cmd);
//  }