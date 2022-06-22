#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdlib.h>
#include <term.h>

void	censor(int fd, const char *s)
{
	if (isatty(fd))
	{
		if (s)
			printf("%s is referring to a terminal\n", s);
		else
			printf("File Descriptor %d is referring to a terminal\n", fd);
	}
	else
	{
		if (s)
			printf("%s is not referring to a terminal\n", s);
		else
			printf("File Descriptor %d is not referring to a terminal\n", fd);
	}
}

void    f_isatty_test(void)
{
    int fd;

    fd = open("test", O_RDONLY);
	if (fd < 0)
        return ;
	censor(STDIN_FILENO, "STDIN");
	censor(STDOUT_FILENO, "STDOUT");
	censor(STDERR_FILENO, "STDERR");
    censor(fd, NULL);
	censor(42, NULL);
	close(fd);
}

void    f_ttyname_test(void)
{
    printf("TTYNAME:\t%s\n", ttyname(STDIN_FILENO));
    printf("TTYNAME:\t%s\n", ttyname(STDOUT_FILENO));
    printf("TTYNAME:\t%s\n", ttyname(STDERR_FILENO));
}

void    f_ttyslot_test(void)
{
    printf("TTYSLOT:\t%d\n", ttyslot());
}

void    f_ioctl_test(void)
{
	struct winsize	size;

	if (ioctl(STDIN_FILENO, TIOCGWINSZ, &size) == -1)
		printf("Error\n");
    else
    {
        printf("Terminal Row Size:\t%d\n",size.ws_row);
        printf("Terminal Col Size:\t%d\n",size.ws_col);
    }
}

void    f_getenv_test(void)
{
    char    *s = "TERM";
	char	*term;

	term = getenv(s);
	if (term)
        printf("%s Type is %s\n", s, term);
    else
        printf("getenv(%s) -> Fail\n", s);
	printf("path => %s\n", getenv("PATH"));

}

int	main(void)
{
	f_isatty_test();
    f_ttyname_test();
    f_ttyslot_test();
    f_ioctl_test();
    f_getenv_test();
}
