/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nechaara <nechaara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 10:59:48 by mvan-pee          #+#    #+#             */
/*   Updated: 2024/02/15 15:50:41 by nechaara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	ft_pwd(t_data *data, t_env **head)
{
	char buffer[500];

	ft_printf("%s\n", getcwd(buffer, 500));
	data->env_var = 0;
}
