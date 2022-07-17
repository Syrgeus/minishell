/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdrowzee <jdrowzee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 11:43:50 by jdrowzee          #+#    #+#             */
/*   Updated: 2022/07/17 17:40:31 by jdrowzee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_stat;

void	parse_input(char *input, t_env *env, char **envp)
{
	t_list	*token;

	token = 0;
	add_history(input);
	if (split_token(input, &token) == TRUE && check_token(token) == TRUE)
	{
		handle_heredoc(token);
		parse_pipe_token(token, env, envp);
		while (waitpid(-1, &g_stat, 0) > 0)
			continue ;
	}
	if (WIFEXITED(g_stat))
		g_stat = WEXITSTATUS(g_stat);
	ft_lstclear(&token, free);
}

int	main(int argc, char **argv, char **envp)
{
	t_set	set;
	t_env	*env;
	char	*input;

	(void)argc;
	(void)argv;
	init_set(&set, &env, envp);
	signal(SIGINT, ft_handler);
	while (1)
	{
		init_set2(&set, &envp, env);
		input = readline("$ ");
		signal(SIGQUIT, ft_handler);
		if (!input)
		{
			reset_set(&set);
			exit(0);
		}
		tcsetattr(STDIN_FILENO, TCSANOW, &set.org_term);
		parse_input(input, env, envp);
		input = ft_free(input);
		reset_stdio(&set);
		ft_free_split(envp);
	}
	return (0);
}
