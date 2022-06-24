#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>

void	getcwd_chdir_test(void)
{
	// in test folder
	printf("errno: %d\n", errno);
	printf("getcwd(NULL, 0) => return: %s\n", getcwd(NULL, 0));

	// set about permission
	printf("chmod 0 no_permission_dir => return: %d\n", chmod("no_permission_dir", 0));
	printf("chmod 0 no_permission_file => return: %d\n", chmod("no_permission_file", 0));
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

	// set about permission
	printf("chmod rwxr-xr-x no_permission_dir => return: %d\n", chmod("no_permission_dir", S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH));
	printf("chmod rw-r--r-- no_permission_file => return: %d\n", chmod("no_permission_file", S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH));
	printf("\n");
}

// int	main(void)
// {
// 	getcwd_chdir_test();
// }
