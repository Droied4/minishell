/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_pwd_cd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 19:13:30 by avolcy            #+#    #+#             */
/*   Updated: 2024/03/22 13:33:28 by avolcy           ###   ########.fr       */
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

// static void update_current_pwd(t_env *lst)
// {
// 	//iterate through lst and change pwd content 
// 	//calling the getwd function
// }

// static void update_current_oldpwd(t_env *lst)
// {
// 	//iterate through lst and change oldpwd content 
// 	//to the last one
	
// }

int	execute_cd(t_shell *sh, char **env)
{
	// static	char *defpath;
	const char	*path;
	
	// if (!defpath)
	// 	defpath = ft_strdup("HOME");
	// printf("\t\n\nthe home add [%p]\n\n", defpath);
	if (sh->env == NULL)
		sh->env = create_lst_env(env);
	if (sh->tokens->next == NULL)
		path = found_path(sh, "HOME");
	else
		path = (sh->tokens->next->data);
	//OLDPWD = current PWD
	//update_current_oldpwd(sh->env);	
	if (chdir(path) == -1)
	{
		free(&path);
		ft_dprintf(STDERR_FILENO, "hola its ok\n");
	}
	//update de PWD with getcwd; 
	//update_current_pwd(sh->env);
	return (0);
}