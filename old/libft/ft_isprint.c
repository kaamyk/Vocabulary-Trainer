/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvincen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 13:37:39 by anvincen          #+#    #+#             */
/*   Updated: 2022/11/11 15:46:41 by anvincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
int	ft_isprint(int c)
{
	if (c < 32 || c > 126)
		return (0);
	return (1);
}