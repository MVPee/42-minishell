/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-pee <mvan-pee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 14:11:33 by mvan-pee          #+#    #+#             */
/*   Updated: 2024/02/14 14:17:34 by mvan-pee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void ft_unset(t_env *head, t_data *data, char **split)
{
    if (split[1])
        env_remove_entry(head, split[1]);
    data->env_var = 0;
}
