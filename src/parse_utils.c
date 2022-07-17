/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdrowzee <jdrowzee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 15:58:11 by jdrowzee          #+#    #+#             */
/*   Updated: 2022/07/17 17:40:42 by jdrowzee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*my_strtrim(char *data, int start, int end)
{
	char	*tmp;
	int		i;
	int		j;

	tmp = (char *)malloc(sizeof(char) * end);
	if (!tmp)
		return (NULL);
	i = -1;
	j = 0;
	while (data[++i] && i < end)
		if (i != start)
			tmp[j++] = data[i];
	tmp[j] = 0;
	return (tmp);
}

int	check_token(t_list *token)
{
	int	i;

	i = 0;
	while (token)
	{
		if (token->content[0] == '|' && (i == 0
				|| !token->next || token->next->content[0] == '|'))
			return (error_msg("|"));
		else if (token->content[0] == '<' || token->content[0] == '>')
		{
			if (token->content[1] && token->content[0] != token->content[1])
				return (error_msg(&token->content[1]));
			else if (ft_strlen(token->content) > 2)
				return (error_msg(&token->content[2]));
			else if (!token->next)
				return (error_msg(NULL));
			else if (token->next->content[0] == '<'
				|| token->next->content[0] == '>'
				|| token->next->content[0] == '|')
				return (error_msg(token->next->content));
		}
		i++;
		token = token->next;
	}
	return (TRUE);
}

int	find_env_var_token(char *data, int start, int end)
{
	int	find;

	find = start + 1;
	while (data[find] && find < end && data[find] != '$')
		find++;
	if (find == end)
		return (FALSE);
	return (TRUE);
}

int	find_valid_env_var_point(char *data)
{
	int	find;

	if (data[0] == '?')
		return (1);
	find = 0;
	while (data[find] && (ft_isalnum(data[find]) || data[find] == '_'))
		find++;
	return (find);
}

int	find_valid_quot_point(char *data, int start)
{
	int	find;

	find = start + 1;
	while (data[find] && data[start] != data[find])
		find++;
	if (data[find])
		return (find);
	return (start);
}
