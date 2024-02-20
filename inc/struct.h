/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 17:44:23 by deordone          #+#    #+#             */
/*   Updated: 2024/02/20 20:00:14 by deordone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_token
{
	int		index;
	char	*data;
	int		type;
	struct s_token *next;
	struct s_token *prev;
}		t_token;

typedef enum e_type
{
	PIPE,//0
	GREAT,//1
	LESS,//2
	DGREAT,//3
	DLESS,//4
	CMD,//5
	FLAG,//6
	ARCH,//7
	SQUOTE,//8
	DQUOTE,//9
	EXP//10
}		t_type;

#endif
