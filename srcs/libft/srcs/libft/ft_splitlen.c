/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitlen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 16:39:37 by mvpee             #+#    #+#             */
/*   Updated: 2023/11/19 16:39:37 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

size_t	ft_splitlen(const char **src)
{
	size_t	i;

	i = 0;
	while (src[i])
	{
		ft_printf("debug: %s\n", src[i]);
		i++;
	}
		
	return (i);
}
