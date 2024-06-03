#include <libc.h>

int main()
{
	char *arr[] = {"ls", "1","+", "1", NULL};
	int a = execve("/bin/expr", arr, NULL);
	// strerror(a);
}