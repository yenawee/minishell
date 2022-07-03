#include "test.h"

void	interrupt_process(int signal)
{
	(void)signal;
	printf("\n");
	exit(1);
}

void	quit_process(int signal)
{
	(void)signal;
	printf("Quit : \n");
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
