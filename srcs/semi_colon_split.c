#include "shell.h"

// this function will split command and ignoring ; if it is between quotes

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
				arr[i][j] = ';';
			j++;
		}
		i++;
	}
}
char **semi_colon_split(char *str) 
{
	int i;
	char quote;
	char **result;
	char **for_free;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			quote = str[i];
			while (str[++i] != quote)
			{
				if (str[i] == ';')
					str[i] = 1;
			}
		}
		i++;
	}
	result = ft_strsplit(str, ';');
	split_helper(result);
	for_free = result;
	result = trim_all_the_array(result);
	ft_free_tab((void **)for_free);
	return result;
}
