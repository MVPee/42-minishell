/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-pee <mvan-pee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 16:29:03 by mvan-pee          #+#    #+#             */
/*   Updated: 2024/02/22 16:29:20 by mvan-pee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void free_env(t_env *env)
{
	t_env *current;

	current = env;
	while(env)
	{
		current = env;
		env = env->next;
		ft_free(3, &current->key, &current->value, &current);
	}
}
