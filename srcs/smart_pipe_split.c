#include "shell.h"

static void split_helper(char **arr)
{
	int i;
	int j;

	i = 0;
	while (arr[i])
	{
		j = 0;
		while (arr[i][j])
		{
			if (arr[i][j] == 1)
				arr[i][j] = '|';
			j++;
		}
		i++;
	}
}

char **smart_pipe_split(char *str) 
{
	int i;
	char quote;
	char **result;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			quote = str[i];
			while (str[++i] != quote)
			{
				if (str[i] == '|')
					str[i] = 1;
			}
		}
		i++;
	}
	result = ft_strsplit(str, '|');
	split_helper(result);
	return (result);
}
