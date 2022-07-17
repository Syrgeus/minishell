/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdrowzee <jdrowzee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 11:43:50 by jdrowzee          #+#    #+#             */
/*   Updated: 2022/07/17 13:51:14 by jdrowzee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	st_flag;

void    parse_input(char *input, t_env *env, char **envp)
{
    t_list  *token;

    token = 0;
    add_history(input);
    if(split_token(input, &token) == TRUE && check_token(token) == TRUE)
    {
        handle_heredoc(token);
        parse_pipe_token(token, env, envp);
        while(waitpid(-1, &st_flag, 0) > 0)
            continue ;
    }
    if (WIFEITED(st_flag))
        st_flag = WEXITSTATUS(st_flag);
    ft_lstclear(&token, free);
}

int	main(int argc, char **argv, char **envp)
{
    t_set   set;
    t_env   *env;
    char    *input;    
    
    (void)argc;
    (void)argv;
    ft_init(&set, &env, envp);
    signal(SIGINT, ft_handler);
    while (1)
	{
		init_set(&set, &envp, env);
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
