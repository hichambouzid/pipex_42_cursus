#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>


// int main()
// {
// 	int pidfd[2];
// 	char tab[100];
// 	int r;
// 	pid_t p;

// 	if (pipe(pidfd) == -1)
// 		return (write(2, "error\n", sizeof("error\n")));

// 	p = fork();
// 	if (p < 0)
// 	{
// 		printf("error\n");
// 		return (0);
// 	}
// 	else if (p == 0)
// 	{
// 		printf("hello i'm a child procces %d \n", getpid());
// 		write(pidfd[1], "hello world\n", 11);
// 		close(pidfd[1]);
// 	}
// 	else
// 	{
// 		r = read(pidfd[0], tab, 100);
// 		tab[r] = 0;
// 		printf("the return is %s\n", tab);
// 		printf("hello i'm a parent proccess %d\n", getpid());
// 		wait(NULL);
// 	}
// }
