/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 14:11:33 by mvan-pee          #+#    #+#             */
/*   Updated: 2024/02/27 21:03:10 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char *ft_unset(t_env **head, t_data *data, char *line)
{
    char    **splitted_args;
    size_t  index;

    splitted_args = ft_split(line, " ");
    if (!splitted_args)
        return NULL;
    if (ft_splitlen((const char **)splitted_args) > 1)
    {
        index = 1;
        while (splitted_args[index])
        {
            env_remove_entry(head, splitted_args[index]);
            index++;
        }        
    }
    ft_free_matrix(1, &splitted_args);
    data->env_var = 0;
    return (ft_strdup(""));
}
