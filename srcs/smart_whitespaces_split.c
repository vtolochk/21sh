#include "shell.h"

static void smart_helper(char **arr)
{
	int i;
	int j;

	i = 0;
	while (arr[i])
	{
		substitute_tild(&arr[i]);
		j = 0;
		while (arr[i][j])
		{
			if (arr[i][j] == 1)
				arr[i][j] = ' ';
			else if (arr[i][j] == 2)
				arr[i][j] = '\t';
			j++;
		}
		i++;
	}
}

char **smart_whitespaces_split(char *str)
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
				if (str[i] == ' ')
					str[i] = 1;
				else if (str[i] == '\t')
					str[i] = 2;
			}
		}
		i++;
	}
	result = ft_split_whitespaces(str);
	smart_helper(result);
	return (result);
}