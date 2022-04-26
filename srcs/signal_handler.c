/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeheoki < taeheoki@student.42seoul.kr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 16:39:58 by taeheoki          #+#    #+#             */
/*   Updated: 2022/04/26 16:54:47 by taeheoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

extern int	g_exit_status;

static void	sigint_handler(pid_t pid)
{
	if (pid == -1)
	{
		ft_putendl_fd("", STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else
		ft_putendl_fd("", STDOUT_FILENO);
	g_exit_status = 130;
}

static void	sigquit_handler(pid_t pid)
{
	if (pid == 0)
	{
		ft_putendl_fd("Quit: 3", STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
	}
	else
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		write(1, "  \b\b", 4);
	}
}

void	signal_handler(int signum)
{
	pid_t	pid;
	int		status;

	pid = waitpid(-1, &status, WNOHANG);
	if (signum == SIGINT)
		sigint_handler(pid);
	else if (signum == SIGQUIT)
		sigquit_handler(pid);
}

void	set_signal(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
}
