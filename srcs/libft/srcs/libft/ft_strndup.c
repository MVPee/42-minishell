/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nechaara <nechaara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 16:47:54 by nechaara          #+#    #+#             */
/*   Updated: 2024/02/14 16:48:40 by nechaara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_strndup(const char *s, size_t n)
{
	size_t	len;
	char	*dup;

	len = ft_strlen(s);
	if (len > n)
		len = n;
	dup = (char *)malloc((len + 1) * sizeof(char));
	if (!dup)
		return (NULL);
	ft_memcpy(dup, s, len);
	dup[len] = '\0';
	return (dup);
}