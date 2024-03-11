/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 11:40:06 by avolcy            #+#    #+#             */
/*   Updated: 2023/05/17 15:43:43 by avolcy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalnum(int v)
{
	if ((v >= 48 && v <= 57) || (v >= 65 && v <= 90) || (v >= 97 && v <= 122))
		return (1);
	return (0);
}