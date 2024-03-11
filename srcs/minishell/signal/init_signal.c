/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_signal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-pee <mvan-pee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 17:29:06 by mvpee             #+#    #+#             */
/*   Updated: 2024/03/11 12:57:12 by mvan-pee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		//printf("\n");
		//rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		//data.env_var = 130.
	}
}

void	init_signal(void)
{
	//CTRL-C
	signal(SIGINT, signal_handler);
	//CTRL-D
	signal(SIGQUIT, SIG_IGN);
}
