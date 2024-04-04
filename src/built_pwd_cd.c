/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_pwd_cd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 19:13:30 by avolcy            #+#    #+#             */
/*   Updated: 2024/04/04 19:24:57 by avolcy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_pwd(void)
{
	char	s[PATH_MAX];

	if (getcwd(s, sizeof(s)) != NULL)
	{
		ft_dprintf(STDOUT_FILENO, "%s\n", s);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

static void update_currentpwd_cd(t_env *lst)
{
	t_env *var_node;
	char	path[PATH_MAX];

	path[0] = '\0';
	getcwd(path, sizeof(path));
	var_node = found_var("PWD", lst);
	if (!var_node)
		return ;
	free(var_node->var_content);
	var_node->var_content = ft_strdup(path);
}

static void update_oldpwd_cd(t_env *lst, char *old)
{
	t_env *var_node;

	var_node = found_var("OLDPWD", lst);
	if (!var_node)
		return ;
	free(var_node->var_content);
	var_node->var_content = ft_strdup(old);
}

int	execute_cd(t_shell *sh, char **env)
{
	t_env *home;
	char	*path;
	char	oldpath[PATH_MAX];
	
	if (sh->env == NULL)
		sh->env = create_lst_env(env);
	if (sh->tokens->next == NULL)
	{
		home = found_var("HOME", sh->env);
		path = home->var_content;
	}
	else
		path = (sh->tokens->next->data);
	oldpath[0] = '\0';
	getcwd(oldpath, sizeof(oldpath));
	if (chdir(path) == -1)
		ft_dprintf(STDERR_FILENO, "path did not found bro\n");
	else 
	{
		update_oldpwd_cd(sh->env, oldpath);
		update_currentpwd_cd(sh->env);
	}	
	return (0);
}