/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifer2 <davifer2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 12:37:07 by fcarranz          #+#    #+#             */
/*   Updated: 2024/08/30 21:52:13 by davifer2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal;

void	detect_ctrl_c(t_utils *utils)
{
	if (g_signal == 1)
	{
		g_signal = 0;
		utils->exit_status = 130;
	}
}

void	handle_signal(int signal)
{
	if (signal == SIGINT)
	{
		g_signal = 1;
		ft_putstr_fd("\n", 1);
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	handle_signal_interactive(int signal)
{
	if (signal == SIGINT)
	{
		g_signal = 1;
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	*handle_error_ctrl_d(char *stop, int cmds_amount)
{
	char	*cmds_count;

	cmds_count = ft_itoa(cmds_amount);
	ft_putstr_fd(HEREDOC_ERROR, 2);
	ft_putstr_fd(cmds_count, 2);
	ft_putstr_fd(" delimited by end-of-file (wanted `", 2);
	ft_putstr_fd(stop, 2);
	ft_putstr_fd("')\n", 2);
	free(cmds_count);
	return (NULL);
}

void	set_signals(int mode)
{
	if (mode == INTERACTIVE)
	{
		signal(SIGINT, handle_signal_interactive);
		signal(SIGQUIT, handle_signal_interactive);
	}
	if (mode == NON_INTERACTIVE)
	{
		signal(SIGINT, handle_signal);
		signal(SIGQUIT, SIG_IGN);
	}
}
