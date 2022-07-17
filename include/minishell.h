/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdrowzee <jdrowzee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 11:57:03 by jdrowzee          #+#    #+#             */
/*   Updated: 2022/07/17 14:26:17 by jdrowzee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <sys/wait.h>
# include <sys/errno.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <fcntl.h>
# include <dirent.h>
# include <curses.h>
# include <termios.h>
# include <signal.h>
# include <unistd.h>
# include "../libft/libft.h"

# define ERROR		-1

extern int	st_flag;

typedef struct s_env
{
	char			*key;
	int				print_check;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_set
{
	struct termios	org_term;
	struct termios	new_term;
	int				org_stdin;
	int				org_stdout;
}	t_set;

typedef struct s_proc
{
	t_env	*env_lst;
	t_list	*data;
	t_list	*cmd;
	t_list	*limiter;
	int		status;
	int		pip_flg;
	int		infile;
	int		outfile;
}	t_proc;	

/*init.c*/

void	fr_init(t_set *set, t_env **env, char **envp);
void	init_set(t_set *set, char ***envp, t_env *env);
void	reset_set(t_set *set);
void	reset_stdio(t_set *set);

/*split.c*/

int	split_token(char *input, t_list **token);
int	split_rest_token(char *input, t_list **token);
int	split_pipe_token(char *input, int i, t_list **token);
int	split_space_token(char *input, int i, t_list **token);
int	split_redirection_token(char *input, int i, t_list **token);

/* handler.c */

int		check_builtin_command(t_list *cmd);
void	execute_builtin_command(t_proc *proc, char **exe);
void	ft_replace_line(int var_stat);
void	haft_handler(int status);
void	ft_handler(int status);

/*
typedef struct s_list
{
	void			*content;
	int				vision;
	struct s_list	*next;
}	t_list;

typedef struct s_cmd
{
	char			**cmd;
	int				fd[2];
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_minishell
{
	t_list			*var;

	t_list			*com;
	t_cmd			*cmd;

	char			*line;

	int				exit_flag;

}	t_struct;

*/

void	add_history(char *line);

#endif
