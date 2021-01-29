<<<<<<< HEAD
=======
#include "minishell.h"

>>>>>>> 7d797f74c480302d7fe8f58966f6eb1d8a727603
void     _bcopy(void *dest, void *src, int size)
{
    char    *s1;
    char    *s2;

    s1 = (char *)dest;
    s2 = (char *)src;
    while (size--)
        s1[size] = s2[size];
}

int     _bcopy_int(void *dest, void *src, int size)
{
    _bcopy(dest, src, size);
    return (0);
}

void	_bzero(void	 *s, int n)
{
	char *str = (char *)s;
	int i = 0;
<<<<<<< HEAD

=======
>>>>>>> 7d797f74c480302d7fe8f58966f6eb1d8a727603
	while (i < n)
	{
		str[i] = 0;
		i++;
	}
}