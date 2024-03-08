/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free_free.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:57:18 by mvpee             #+#    #+#             */
/*   Updated: 2024/03/08 15:01:01 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_strjoin_free_free(char **s1, char *s2)
{
	int		i;
	int		j;
	char	*str;

	if (!s2)
		return (NULL);
	if (!(*s1))
		*s1 = ft_strdup("");
	if (!(*s1))
		return (NULL);
	str = (char *)malloc(sizeof(char) * (ft_strlen(*s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	i = -1;
	j = 0;
	while ((*s1)[++i])
		str[j++] = (*s1)[i];
	i = -1;
	while ((s2)[++i])
		str[j++] = (s2)[i];
	str[j] = '\0';
	ft_free(2, s1, &s2);
	return (str);
}
