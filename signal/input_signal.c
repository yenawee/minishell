/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_signal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenawee <yenawee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 20:05:33 by yenawee           #+#    #+#             */
/*   Updated: 2022/07/12 00:24:28 by yenawee          ###   ########.fr       */
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
