/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_signal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonjan <hyeonjan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 20:05:33 by yenawee           #+#    #+#             */
/*   Updated: 2022/07/13 21:08:09 by hyeonjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static t_sh	*g_sh;

void	set_sh(t_sh *sh)
{
	g_sh = sh;
}

static void	new_prompt(int signal)
{
	(void)signal;
	g_sh->exit_status = 1;
	g_sh->heredoc_index = 0;
	ft_putstr_fd(1, "\b\b  ");
	rl_replace_line("", 0);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}

void	heredoc_prompt(int signal)
{
	(void)signal;
	g_sh->exit_status = 1;
	g_sh->heredoc_index = 0;
	ft_putstr_fd(1, "\b\b  ");
	rl_replace_line("", 0);
	write(1, "\n", 1);
	rl_on_new_line();
	exit(EXIT_FAILURE);
}

void	set_input_signal(void)
{
	signal(SIGINT, new_prompt);
	signal(SIGQUIT, SIG_IGN);
}
