#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#include <readline/readline.h>
#include <readline/history.h>

//readline
void readline_test(){

	char *line_read;
	const char *prompt = "$";
	int a;

	line_read = readline(prompt);
	while (line_read)
	{
		if (line_read && *line_read)
		{
			add_history(line_read);
		}
		line_read = readline(prompt);
	}
}

//signal
void handle_sigtstp(int sig)
{
    printf("stop not allowed\n");

}

void _signal()
{

	signal(SIGTSTP, &handle_sigtstp);

    int x;
    printf("input number : ");
    scanf("%d", &x);
    printf("input number : %d, result : %d\n", x, x * 5);
}

//kill
void	_kill()
{
    int pid = fork();
    if (pid == -1) return ;

    if (pid == 0)
    {
        while (1)
        {
            printf("some output\n");
            usleep(50000);
        }
    }
    else
    {
        kill(pid, SIGSTOP);
        int t;
        do {
            printf("put time: ");
            scanf("%d", &t);

            if ( t > 0)
            {
                kill(pid, SIGCONT);
                sleep(t);
                kill(pid, SIGSTOP);
            }
        } while (t > 0);
        kill(pid, SIGKILL);
        wait(NULL);
    }
}

//getcwd
void	_getcwd()
{
	char *buf;

	buf = NULL;
	char *path = getcwd(buf, 0);
	printf("%s\n", path);
}

//chdir
void _chdir()
{
	int ret = chdir("../../");
	printf("%d\n", ret);

	system("pwd");
}

void	_getcwd_chdir_test()
{
	// in test folder
	printf("errno: %d\n", errno);
	printf("getcwd(NULL, 0) => return: %s\n", getcwd(NULL, 0));
	printf("\n");
	
	// chmod 0 no_permission_dir
	printf("chdir(\"no_permission_dir\") => return: %d\n", chdir("no_permission_dir"));
	printf("errno: %d\n", errno);// no permission => 13
	perror(NULL);// Permission denied
	printf("\n");

	// notExist 
	printf("chdir(\"notExist\") => return: %d\n", chdir("notExist"));
	printf("errno: %d\n", errno);// no permission => 2
	perror(NULL);// No such file or directory
	printf("\n");
	
	// file
	printf("chdir(\"file\") => return: %d\n", chdir("file"));
	printf("errno: %d\n", errno);// no permission => 2
	perror(NULL);// Not a directory
	printf("\n");
	
	// no_permission_file
	printf("chdir(\"no_permission_file\") => return: %d\n", chdir("no_permission_file"));
	printf("errno: %d\n", errno);// no permission => 2
	perror(NULL);// Not a directory
	printf("\n");
	
}

//opendir, readdir
void	_dir()
{
    DIR *dp;
    struct dirent *dirp;

    dp = opendir("./");

    while ((dirp = readdir(dp)) != NULL)
        printf("%s\n", dirp->d_name);

    closedir(dp);
    exit(EXIT_SUCCESS);
}

int main()
{
	// readline_test();
	// _signal();
	// _kill();
	// _getcwd();
	// _chdir();
	_getcwd_chdir_test();
	// _dir();

	return 0;
}
