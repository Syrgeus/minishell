/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdrowzee <jdrowzee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 16:16:26 by jdrowzee          #+#    #+#             */
/*   Updated: 2022/07/17 17:40:10 by jdrowzee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_line(char *line, char *limiter, int fd)
{
	if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
		exit(0);
	write(1, "> ", 2);
	write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
}

char	*sum(char *line, char buf)
{
	int		size;
	char	*str;
	int		i;

	size = ft_strlen(line);
	str = (char *)malloc(sizeof(char) * (size + 2));
	if (!str)
		return (NULL);
	i = 0;
	while (line[i] != 0)
	{
		str[i] = line[i];
		i++;
	}
	free(line);
	str[i++] = buf;
	str[i] = '\0';
	return (str);
}

void	handle_heredoc(t_list *token)
{
	int	org_stdin;

	org_stdin = dup(STDIN_FILENO);
	while (token)
	{
		if (strncmp(token->content, "<<", 3) == 0)
		{
			dup2(org_stdin, STDIN_FILENO);
			heredoc(token->next->content);
			token = token->next;
		}
		token = token->next;
	}
}

int	heredoc(char *limiter)
{
	int		fd[2];
	pid_t	pid;
	char	*line;

	if (pipe(fd) == -1)
		return (error_msg("pipe"));
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		write(1, "> ", 2);
		while (get_next_line(&line))
			print_line(line, limiter, fd[1]);
		close(fd[1]);
	}
	else if (pid > 0)
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(pid, 0, 0);
		close(fd[0]);
	}
	else
		return (error_msg("fork"));
	return (TRUE);
}
