/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdrowzee <jdrowzee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 16:17:22 by jdrowzee          #+#    #+#             */
/*   Updated: 2022/07/17 17:41:17 by jdrowzee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	error_msg(char *msg)
{
	g_stat = 2;
	write(2, "bash: ", 6);
	if (!msg)
		write(2, "syntax error near unexpected token 'newline'", 44);
	else if (msg[0] == '|' || msg[0] == '<' || msg[0] == '>')
	{
		write(2, "syntax error near unexpected token '", 36);
		write(2, msg, ft_strlen(msg));
		write(2, "'\n", 2);
		return (ERROR);
	}
	else
	{
		g_stat = 127;
		write(2, msg, ft_strlen(msg));
		if (ft_strncmp(strerror(errno), "Bad address", 12) == 0)
			write(2, ": command not found", 19);
		else
		{
			write(2, ": ", 2);
			write(2, strerror(errno), ft_strlen(strerror(errno)));
		}
	}
	write(2, "\n", 1);
	return (g_stat);
}

void	*ft_free(char *p)
{
	if (p)
	{
		free(p);
		p = NULL;
	}
	return (NULL);
}

void	*ft_free2(char **p)
{
	int	i;

	if (!p)
		return (NULL);
	i = -1;
	while (p[++i])
	{
		free(p[i]);
		p[i] = NULL;
	}
	free(p[i]);
	p[i] = NULL;
	free(p);
	return (NULL);
}

char	*ft_strndup(char *s, int n)
{
	char	*temp;
	int		i;

	temp = (char *)malloc(sizeof(char) * (n + 1));
	if (!temp)
		return (NULL);
	i = -1;
	while (s[++i] && i < n)
		temp[i] = s[i];
	temp[i] = 0;
	return (temp);
}

char	*ft_strntrim(char *s, char *set, int n)
{
	char	*temp;
	char	*temp2;
	int		i;

	temp = (char *)malloc(sizeof(char) * (n + 1));
	if (!temp)
		return (NULL);
	i = -1;
	while (s[++i] && i < n)
		temp[i] = s[i];
	temp[i] = 0;
	temp2 = ft_strtrim(temp, set);
	ft_free(temp);
	return (temp2);
}
