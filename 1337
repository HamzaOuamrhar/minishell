#include <libc.h>

int	summer (int *tab , int n, int j)
{
	int i = 0;
	int counter = 0;
	while (tab[i])
	{
		if ( i == j)
		{
			i++;
			continue;
		}
		int u = i;
		while (tab[u])
		{
			if (tab[u+1] && (n == tab[u] + tab[u + 1]))
				counter++;
			i++;
		}
		i++;
	}
	return (counter);
}
int main()
{
	int n;
	scanf("%d", &n);			
	int j = 0;
	while (j < n)
	{
		int n2;
		scanf("%d", &n2);
		int k = 0;
		int *tab  = malloc (4 * (n2 + 1));
		int c = 0;
		while (k < n2)
		{
			int w;
			scanf("%d", &w);
			// printf("[[%d]] ", w);
			tab[c++] = w;
			k++;
		}
		tab[c] = '\0';
		int counter = 0;
		if (n2 == 1 && tab[0] == 0)
			printf("1");
		else if (n2 == 1 &&tab[0] != 0)
			printf("0");
		else
		{
			int counter = 0;
			int i = 0;
			while (i < n2)
			{
				counter += summer(tab, tab[i], i);
				i++;
			}
			printf("%d", counter);
		}
		j++;
		if (j != n)
			printf("\n");
	}
}