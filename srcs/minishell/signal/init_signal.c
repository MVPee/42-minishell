/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_signal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nechaara <nechaara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 17:29:06 by mvpee             #+#    #+#             */
/*   Updated: 2024/03/11 17:34:21 by nechaara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();

	}
}

void	init_signal(t_data *data)
{
	//CTRL-C
	if (signal(SIGINT, signal_handler) != SIG_ERR)
		(*data).env_var = COMMAND_INTERRUPTED;
	//CTRL-D
	else if (signal(SIGQUIT, SIG_IGN) != SIG_ERR)
		(*data).env_var = SUCCESSFUL_COMMAND;
}
