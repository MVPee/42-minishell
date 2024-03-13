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
		ft_printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_sig.flag = true;
	}
	else if (!g_sig.minishell && signum == SIGINT)
	{
		if (g_sig.heredoc)
			ft_printf("\n");
	}
}

void	signal_heredoc(int signum)
{
	if (g_sig.heredoc && signum == SIGINT)
		exit(COMMAND_INTERRUPTED);
}

void	init_signal(void)
{
	g_sig.execve = false;
	g_sig.heredoc = false;
	g_sig.flag = false;
	g_sig.minishell = false;
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}
