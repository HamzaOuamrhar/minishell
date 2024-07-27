#include "minishell.h"
int main()
{
    int fd1 = open("/Users/iez-zagh/Desktop/minishell/imad.txt", O_WRONLY);
    int fd2 = open("imad.txt", O_RDONLY);
    printf("%d\n", fd2);
}