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
	if (signum == SIGINT)
	{
		ft_printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_sig.flag = SIGINT;
	}
}

void	signal_heredoc(int signum)
{
	if (signum == SIGINT)
	{
		ft_printf("\n");
		exit(1);
	}
}

void	signal_quit(int signum)
{
	if (signum == SIGQUIT)
		ft_printf_fd(2, "\nQuit\n");
	exit(131);
}

void	init_signal(void)
{
	g_sig.flag = 0;
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}
