/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   form_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtolochk <vtolochk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 11:22:00 by vtolochk          #+#    #+#             */
/*   Updated: 2018/06/13 11:22:00 by vtolochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void quoted_and_whitespaced_items(char *str, int *items)
{
	char character;

	if (!str)
		return ;
	while (*str)
	{
		while (*str && WHITESPACE)
			str++;
		if (*str == '\'' || *str == '\"')
		{
			(*items)++;
			character = *str++;
			while (*str && *str != character)
				str++;
		}
		if (*str && !(WHITESPACE) && *str != '\'' && *str != '\"')
		{
			(*items)++;
			while (*str && (!(WHITESPACE) && *str != '\'' && *str != '\"'))
				str++;
		}
		if (!(*str))
			break ;
		str++;
	}
}

static int simple_string(int *i, char ***new_arr, char *str, int items)
{
	char **temp;
	int  increase_len;
	int save_index;
	int array_index;
	char **splited_str_without_quotes;
	char *str_without_quotes;

	array_index = 0;
	save_index = (*i);
	while (str[(*i)] && str[(*i)] != '\'' && str[(*i)] != '\"')
		(*i)++;
	str_without_quotes = ft_strsub(str, save_index, (*i) - save_index);
	splited_str_without_quotes = ft_split_whitespaces(str_without_quotes);
	ft_strdel(&str_without_quotes);
	if (splited_str_without_quotes)
	{
		temp = *new_arr;
		*new_arr = array_append_array(*new_arr, splited_str_without_quotes);
		ft_free_tab((void **)temp);
		increase_len = items - array_len(*new_arr);
		temp = *new_arr;
		*new_arr = increase_array(*new_arr, increase_len);
		if (increase_len > 0)
			ft_free_tab((void **)temp);
		array_index = array_len(splited_str_without_quotes);
		ft_free_tab((void **)splited_str_without_quotes);
	}
	return (array_index);
}

static char **quoted_split(char *str)
{
	int i;
	int save_index;
	int j;
	char quote;
	char **new_arr;
	int items;

	i = 0;
	j = 0;
	items = 0;
	quoted_and_whitespaced_items(str, &items);
	new_arr = (char **)malloc(sizeof(char *) * (items + 1));
	while (j <= items)
		new_arr[j++] = NULL;
	j = 0;

	while (str[i])
	{

		if (str[i] == '\'' || str[i] == '\"')
		{
			quote = str[i];
			save_index = ++i;
			while (str[i] && str[i] != quote)
				i++;
			new_arr[j] = ft_strsub(str, save_index, i - save_index);
			j++;
		}
		if (str[i] && str[i] != '\'' && str[i] != '\"')
		{
			j += simple_string(&i, &new_arr, str, items);
			continue ;
		}
		if (!str[i])
			break ;
		i++;
	}
	//var_dump(new_arr);
	return (new_arr);
}

static char *find_first_quote(char *str)
{
	char *find;
	char *find_single_quotes;
	char *find_double_quotes;

	find_single_quotes = ft_strchr(str, '\'');
	find_double_quotes = ft_strchr(str, '\"');
	if (!find_single_quotes)
		find = find_double_quotes;
	else if (!find_double_quotes)
		find = find_single_quotes;
	else if (find_single_quotes > find_double_quotes)
		find = find_double_quotes;
	else
		find = find_single_quotes;
	return (find);
}

static char **form_helper(char *str, char *find)
{
	char *str_before_quote;
	char *start_quoting;
	char **new_arr;
	char **quoted_arr;
	char **temp[2];

	find = find_first_quote(str);
	str_before_quote = ft_strsub(str, 0, find - str);
	new_arr = ft_split_whitespaces(str_before_quote);
	ft_strdel(&(str_before_quote));
	start_quoting = ft_strsub(str, find - str, ft_strlen(str));
	quoted_arr = quoted_split(start_quoting);
	temp[0] = quoted_arr;
	ft_strdel(&start_quoting);
	temp[1] = new_arr;
	new_arr = array_append_array(new_arr, quoted_arr);
	ft_free_tab((void **)temp[0]);
	ft_free_tab((void **)temp[1]);
	return (new_arr);
}

char ***form_commands(char **splited)
{
	int i;
	int arr_len;
	char ***commands;

	i = 0;
	arr_len = array_len(splited);
	commands = (char ***)malloc(sizeof(char **) * (arr_len + 1));
	commands[arr_len] = NULL;
	while (i < arr_len)
	{
		if (ft_strchr(splited[i], '\'') || ft_strchr(splited[i], '\"'))
			commands[i] = form_helper(splited[i], NULL);
		else
			commands[i] = ft_split_whitespaces(splited[i]);
		i++;
	}
	return (commands);
}
