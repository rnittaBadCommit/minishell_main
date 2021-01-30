#include "minishell.h"
#define MALLOC_FAIL 1
#define EXIT 2
#define INI_FAIL MALLOC_FAIL + EXIT

typedef int t_all;

char	**split_command(char *s, char c);

void	print_error(int i)
{
	i++;
}

char **make_command_array_splitpipe(char *cmd)
{
	char **cmd_split;

	//if (!(cmd = separate_redirect(cmd)))
	//	return (NULL);
	if (!(cmd_split = split_command(cmd, '|')))
	{
		free(cmd);
		return (NULL);
	}
	return (cmd_split);
}

char ***make_command_array_malloc(char **tmp)
{
	int cnt;
	char ***ret;

	cnt = 0;
	while (tmp[cnt])
		cnt++;
	if (!(ret = (char ***)malloc(sizeof (char **) * (cnt + 1))))
	{
		print_error(MALLOC_FAIL);
		split_free_all(tmp);
		return (NULL);
	}
	return (ret);
}

void	command_array_free(char ***cmd)
{
	int i;

	i = -1;
	while (cmd[++i])
		split_free_all(cmd[i]);
	free(cmd);
}

char ***make_command_array(char *cmd)
{
	char **tmp;
	char ***ret;
	int i;

	if (!(tmp = make_command_array_splitpipe(cmd)))
		return (NULL);
	if (!(ret = make_command_array_malloc(tmp)))
		return (NULL);
	i = -1;
	while (tmp[++i])
		if (!(ret[i] = split_command(tmp[i], ' ')))
		{
			command_array_free(ret);
			return (NULL);
		}
	ret[i] = NULL;
	return (ret);
}

void command_main(char *cmd_raw)
{
	char ***cmd_split;

	if (!(cmd_split = make_command_array(cmd_raw)))
		return;
	int i = -1;
	while (cmd_split[++i])
	{
		int j = -1;
		while (cmd_split[i][++j])
			printf("%s\n", cmd_split[i][j]);
	}
}

typedef struct s_syntax_check
{
	char pipe;
	char redirect;
}	t_syntax_check;

int	_syntax_check_make_sedstr(char *cmd_raw, char **ret)
{
	char bitflag_quote;
	int i;
	int j;

	if (!(*ret = (char *)malloc(strlen(cmd_raw))))
    {
        print_error(MALLOC_FAIL);
		return (-1);
    }
	bitflag_quote = 0;
	i = -1;
	while (*cmd_raw)
	{
		check_quote(*cmd_raw, &bitflag_quote);
		if (!bitflag_quote)
		{
			*ret[++i] = *cmd_raw;
			if (*cmd_raw == '\'' || *cmd_raw == '\"')
				*ret[i] = 'a';
		}
		cmd_raw++;
	}
    *ret[++i] = '\0';
    return (!!bitflag_quote);
}

int print_synerr(char *cmd)
{
	char s[8];

	s[0] = cmd[0];
	s[2] = '\0';
	if (cmd[0] == '\n')
		s = "newline";
	else if (cmd[0] == '>')
		s[1] = cmd[1] * (cmd[1] == cmd[0]);
	else if (cmd[0] == '<')
		s[1] = '\0';
	else if (cmd[0] == '|')
		s[1] = cmd[1] * (cmd[1] == cmd[0]);
	printf("bash: syntax error near unexpected token `%s'\n", s);
	return (258);
}

int _syntax_check_process2(char *cmd, char *flag_pipe, char *flag_r_redirect, char *flag_l_redirect)
{
	if (*cmd == '>')
	{
		if (*flag_r_redirect >= 2 || *flag_l_redirect || *flag_pipe)
			return (print_synerr(cmd));
		*flag_r_redirect++;
	}
	else if (*cmd == '<')
	{
		if (*flag_l_redirect || *flag_l_redirect || *flag_pipe)
			return (print_synerr(cmd));
		*flag_l_redirect++;
	}
	else
	{
		*flag_l_redirect = 0;
		*flag_r_redirect = 0;
		flag_pipe = 0;
	}
	return (0);
}

int	_syntax_check_process(char *cmd, char *flag_pipe, char *flag_r_redirect, char *flag_l_redirect)
{
	if (*cmd == ' ')
	{
		if (*flag_pipe)
			*flag_pipe += 2;
		if (*flag_r_redirect)
			*flag_r_redirect += 2;
		if (*flag_l_redirect)
			flag_l_redirect += 2;
	}
	else if (*cmd == '|')	
	{
		if (*flag_pipe >= 2 || *flag_r_redirect || *flag_l_redirect)
			return (print_synerr(PIPE));
		*flag_pipe++;
	}
	else
		return (_syntax_check_process2(cmd, flag_pipe, flag_r_redirect, flag_l_redirect));
	return (0);
}

int syntax_check_main(char *cmd)
{
	char flag_pipe;
	char flag_r_redirect;
	char flag_l_redirect;

	flag_pipe = 0;
	flag_r_redirect = 0;
	flag_l_redirect = 0;
	while (*cmd)
	{
		if (_syntax_check_process(cmd, &flag_pipe, &flag_r_redirect, &flag_l_redirect))
			return (258);
		cmd++;
	}
	return (0);
}

int syntax_check(char *cmd_raw)
{
	char *cmd;
	int tmp;

	if (_syntax_check_make_sedstr(cmd_raw, &cmd) == 1)
	{
		free(cmd);
		print_error(SYNTAX_ERROR_QUOTE);
		return (1);
	}
	if (!cmd)
		return (-1);
	tmp = syntax_check_main(cmd);
	free(cmd);
	return (tmp);	
}

int main(void)
{
	printf("\n%d", _syntax_check_make_sedstr("cat > "));
}


/*
int ini(t_all *all)
{
	if (!(arg_main_ini(&(all->arg_main))))
	{
		error(INI_FAIL);
		return (-1);
	}
}

int main(void)
{
	char *cmd_all;
	char **cmd_split;
	char **tmp_cmd_split;
	t_all all;

	if (ini(&all))
		while (1)
		{
			while (!(cmd_all = read_all(0)))
				error(MALLOC_FAIL);
			if (!(cmd_split = split_command(cmd_all, ';')))
				error(MALLOC_FAIL);
			else
			{
				tmp_cmd_split = cmd_split;
				while (*cmd_split)
				{
					command_main(*cmd_split);
					cmd_split++;
				}
				split_free_all(tmp_cmd_split);
			}
			free(cmd_all);	
		}

}

*/