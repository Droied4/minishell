/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 10:02:55 by deordone          #+#    #+#             */
/*   Updated: 2024/02/23 15:46:53 by deordone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
void	parse_input(t_token *tokens)
{
	//redifinir los tipos
	//comprobar que los tipos esten bien
	//es decir que antes de flag haya un comando que delante de pipe y 
	//delante de < or > no haya otra redireccion
}*/

void	total_pipes(t_shell *sh , t_token **tokens)
{
	t_token *tmp;
	int total_pipes;

	tmp = *tokens;
	total_pipes = 0;
	while (tmp)
	{
		if (tmp->type == PIPE)
			++total_pipes;
		tmp = tmp->next;
	}
	sh->pipes = total_pipes;
}

void	fill_cmd(t_shell *sh, t_cmds **cmd)
{
		t_token *tmp_tok;
		char *new_cmd;
		char **final_cmd = NULL;
	
		tmp_tok = sh->tokens;
		char *cosita;
		cosita = ft_strdup(tmp_tok->data);//si voy a utilizar el valor de las tokens necesito duplicarlo
			if (tmp_tok->type == CMD)
			{	
				new_cmd = ft_strjoin(cosita, "=");//para despues hacer un split
			    free(cosita);
				tmp_tok = tmp_tok->next; 
				if (tmp_tok && (tmp_tok->type == CMD || tmp_tok->type == FLAG || tmp_tok->type == ARCH)) //avanzo y miro si el siguiente es un cmd flag o arch
				{
					cosita = ft_strdup(tmp_tok->data);
					new_cmd = ft_imp_strjoin(new_cmd, cosita); // si lo es lo concateno 
				}
				final_cmd = ft_split(new_cmd, '='); //al final hago un split
				free(new_cmd);	
				(*cmd)->cmd = final_cmd; // y guardo el comando en el cmd->cmd
			}
}

/*
// el parse cmd esta muy desordenado cuando vuelva lo arreglo
t_cmds	*parse_cmd(t_shell *sh)
{
	t_cmds *cmd;
	t_token *tmp;

	tmp = sh->tokens;
	while (tmp->type != PIPE && cmd->in_file == NULL && cmd->out_file == NULL)
	{
		if (tmp->type == LESS && cmd->in_file == IN_DFLT)
		{
			tmp = tmp->next;
			cmd->in_file = tmp->data;
		}
		else if (tmp->type == CMD)
		{
			if (tmp->next->type == FLAG || tmp->next->type == CMD)
				//hacer un char ** con el cmd y el cmd o el cmd y el flag
			else 
//				hacer un char ** pero solo con el cmd
		}
		else if (tmp->type == GREAT)
		{
			tmp = tmp->next;
			cmd->out_file = tmp->data;
		}
		else if (tmp->type == PIPE)
		{
			//esto es lo mas complicado buscate la vida deivid del futuro
		}
		tmp = tmp->next;
	}
}*/

void parse_all(t_shell *sh)
{
	
//	parse_input(tokens); redifinir cosas y verificar cosas crear la copia del env
	total_pipes(sh, &sh->tokens);//buscar la ruta de los comandos y prepararlos para el executor
	fill_cmd(sh, &sh->cmds);
	print_tablecmd(sh->cmds);
//🦊❗️	sh->cmds = parse_cmd(sh);
	//parse_expansor; supongo que toca parsearlo xd
}
