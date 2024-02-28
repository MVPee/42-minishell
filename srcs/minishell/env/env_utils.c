/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nechaara <nechaara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 14:16:17 by nechaara          #+#    #+#             */
/*   Updated: 2024/02/26 15:56:34 by nechaara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void    free_env_list(t_env *head)
{
    t_env   *current;
    
    while (head)
    {
        current = head;
        head = head->next;
        free(current->key);
        free(current->value);
        free(current);
        current = NULL;
    }
}
