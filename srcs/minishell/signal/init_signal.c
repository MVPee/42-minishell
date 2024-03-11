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
	}
	if (!g_sig.minishell)
		if (signum == SIGINT && (g_sig.heredoc || g_sig.execve))
			ft_printf("\n");
	g_sig.flag = true;
}

void	init_signal(t_data *data)
{
	g_sig.execve = false;
	g_sig.heredoc = false;
	g_sig.flag = false;
	g_sig.minishell = false;
	//CTRL-C
	signal(SIGINT, signal_handler);
	//CTRL-D
	signal(SIGQUIT, SIG_IGN);
}
