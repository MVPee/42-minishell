/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splittrim.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 11:24:30 by mvpee             #+#    #+#             */
/*   Updated: 2024/03/01 11:42:47 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	**ft_splittrim(char **split, char *set)
{
    int i;
	int count;
    char **new_split;
    char *trimmed_str;

    count = 0;
    i = 0;
    if (!split || !set)
    {
        return (NULL);
    }
	while (split[count])
    {
        count++;
    }
    new_split = (char **)malloc((count + 1) * sizeof(char *));
	if (!new_split)
		return (ft_free_matrix(1, &split), NULL);
	while (i < count)
	{
		trimmed_str = ft_strtrim(split[i], set);
		if (!trimmed_str)
			return (ft_free_matrix(2, &new_split, &split), NULL);
		new_split[i] = ft_strdup(trimmed_str);
        if (!new_split[i])
            return (ft_free_matrix(2, &new_split, &split), ft_free(1, &trimmed_str), NULL);
        ft_free(1, &trimmed_str);
		i++;
	}
	new_split[count] = NULL;
	return (ft_free_matrix(1, &split), new_split);
}
