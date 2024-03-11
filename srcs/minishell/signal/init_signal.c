/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sig.                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 17:29:06 by mvpee             #+#    #+#             */
/*   Updated: 2024/03/11 20:01:09 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	signal_handler(int signum)
{
	if (signum == SIGINT && !g_sig.execve && !g_sig.heredoc)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (signum == SIGINT && (g_sig.execve || g_sig.heredoc))
		printf("\n");
	g_sig.flag = true;
}

void	init_signal(t_data *data)
{
	g_sig.execve = false;
	g_sig.heredoc = false;
	g_sig.flag = false;
	//CTRL-C
	signal(SIGINT, signal_handler);
	//CTRL-D
	signal(SIGQUIT, SIG_IGN);
}
