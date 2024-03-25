/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_pwd_cd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 19:13:30 by avolcy            #+#    #+#             */
/*   Updated: 2024/03/25 17:29:17 by avolcy           ###   ########.fr       */
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

static char *found_path(t_shell *sh, char *var)
{
	int i;
	int pos;
	char *path;
	t_env *tmplst;

	i = 0;
	pos = 0;
	tmplst = sh->env;
	found_var(var, sh->env, &pos);
	while(++i < pos && tmplst)
		tmplst = tmplst->next;
	path = tmplst->var_content;// ft_strdup(tmplst->var_content);
	// printf("var: [%p]\n", var);
	// free(var);
	return (path);
}

static void update_currentpwd_cd(t_env *lst)
{
	int i;
	int pos;
	char	path[PATH_MAX];

	i = 0;
	pos = 0;
	path[0] = '\0';
	getcwd(path, sizeof(path));
	found_var("PWD", lst, &pos);
	while (++i < pos && lst)
		lst = lst->next;
	free(lst->var_content);
	lst->var_content = ft_strdup(path);
}

static void update_oldpwd_cd(t_env *lst, char *old)
{
	int i;
	int pos;

	i = 0;
	pos = 0;
	found_var("OLDPWD", lst, &pos);
	while (++i < pos && lst)
		lst = lst->next;
	free(lst->var_content);
	lst->var_content = ft_strdup(old);
}

int	execute_cd(t_shell *sh, char **env)
{
	char	*path;
	char	oldpath[PATH_MAX];
	
	if (sh->env == NULL)
		sh->env = create_lst_env(env);
	if (sh->tokens->next == NULL)
		path = found_path(sh, "HOME");
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