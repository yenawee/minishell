/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenawee <yenawee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 20:05:38 by yenawee           #+#    #+#             */
/*   Updated: 2022/07/10 20:05:39 by yenawee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	interrupt_process(int signal)
{
	(void)signal;
	printf("\n");
	exit(1);
}

void	quit_process(int signal)
{
	(void)signal;
	printf("Quit: 3 \n");
	exit(1);
}


void	exec_signals() // 자식 process fork 뜬 후 확인
{
	rl_catch_signals = 1;
	signal(SIGINT, interrupt_process);
	signal(SIGQUIT, quit_process);
}

// int main()
// {
// 	while (TRUE){
// 	exec_signals();
// 	}
// 	return 0;
// }
