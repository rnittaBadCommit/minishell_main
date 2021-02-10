#include "includes/minishell.h"

char		*g_signal;
t_arg_main	*g_arg_main;

char	***make_strb_array(char ***cmd_split)
{
	char	***ret;
	int		i;

	ret = malloc(sizeof(char **) * (count(cmd_split) + 1));
	i = -1;
	while (cmd_split[++i])
		ret[i] = make_strb(cmd_split[i]);
	ret[i] = NULL;
	return (ret);
}

int		is_strb_empty(char *s)
{
	int	ret;

	if (!*s)
		return (0);
	ret = 1;
	while (*s)
	{
		if (*s != -1)
			ret = 0;
		s++;
	}
	return (ret);
}

void	remove_empty_strb(char **cmd_split, int *i)
{
	if (is_strb_empty(cmd_split[*i]))
		free(cmd_split[*i]);
	else
	{
		remove_quotes(cmd_split[*i]);
		(*i)++;
	}
}