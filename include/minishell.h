/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdrowzee <jdrowzee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 11:57:03 by jdrowzee          #+#    #+#             */
/*   Updated: 2022/07/17 17:43:35 by jdrowzee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <fcntl.h>				//+
# include <sys/wait.h>			//+
# include <sys/stat.h>			//+
# include <sys/errno.h>			//+
# include <readline/history.h>	
# include <readline/readline.h> //+
# include <dirent.h>			//++
# include <sys/ioctl.h>			//++
# include <curses.h>			//+
# include <termios.h>			//+
# include <signal.h>			//+
# include "../libft/libft.h"

# define ERROR		-1

extern int	g_stat;

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
}t_set;

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
}t_proc;

/* builtin_1.c */

void	ft_unset(char **dbuf, t_env **env_list);
void	ft_cd(char **buf, t_env *env_list);
void	ft_env(t_env *env_list);
int		unset_key_syntax_check(char *s);
void	cd_error(int err, char *arg);

/* builtin_2.c */

void	ft_pwd(void);
char	*read_value_of_key(t_env *env_list, char *key);
int		ft_echo(char **buf);

/* builtin_exit.c  */

int		exit_numeric_arg_cal(char *arg);
int		valid_exit_arg(char	*arg);
void	exit_extra_cases(int c, char *s);
void	ft_exit(char **dbuf);

/* builtin_export.c  */

int		export_key_syntax_error(char *s);
int		export_key_syntax_check(char *s);
void	print_env_in_order(t_env *env_list);
void	ft_export(char **dbuf, t_env *env_list, char **splits, t_env *temp);
void	reset_env_print_check(t_env *env_list);

/*  builtin_tools.c  */

int		ft_strcmp(const char *s1, const char *s2);
void	ft_free_split(char **draw);
t_env	*env_dup_check(t_env *env_list, char *new_key);
t_env	*env_set(char	**envp);
void	env_lstadd_back(t_env **lst, t_env *new, char *key, char *value);

/*  command.c  */

char	*find_path(char *cmd, char **env_lst, int i);
char	**split_command(t_list *cmd);
int		execute_command(t_proc *proc, t_list *cmd, int *fd, char **envp);
int		handle_command(t_proc *proc, t_list *cmd, char **envp);
int		handle_last_command(t_proc *proc, t_list *cmd, char **envp);

/*  convert.c  */

int		ft_env_lstsize(t_env *lst);
char	**convert_env_lst_to_dp(t_env *env);

/* expand.c */

char	*expand_env_var(t_proc *proc, char *data, int start, char **new_data);
char	*expand_in_quot_env_var(t_proc *proc, char *data, int start, int end);
char	*expand_data(t_proc *proc, char *data);
char	*del_big_quot(t_proc *proc, char *data, int start, char **new_data);
char	*del_small_quot_token(char *data, int start, char **new_data);

/* expand_utils.c */

char	*expand_in_quot_utils(t_proc *proc, char *data, char **new_data);
char	*parse_pre_env_var(char *data, int start, char *new_data);

/* get_next_line.c */

int		get_next_line(char **line);

/* handler.c */

int		check_builtin_command(t_list *cmd);
void	execute_builtin_command(t_proc *proc, char **exe);
void	ft_replace_line(int var_stat);
void	haft_handler(int status);

/* heredoc.c  */

void	print_line(char *line, char *limiter, int fd);
char	*sum(char *line, char buf);
void	handle_heredoc(t_list *token);
int		heredoc(char *limiter);
void	ft_handler(int status);

/* init.c */

void	init_set(t_set *set, t_env **env, char **envp);
void	init_set2(t_set *set, char ***envp, t_env *env);
void	reset_set(t_set *set);
void	reset_stdio(t_set *set);

/* parse.c */

int		parse_std_inout_redirection(t_proc *proc, t_list *data, char *temp);
int		parse_data(t_proc *proc, t_list *data);
int		parse_process(t_proc *proc, t_env *env, char **envp);
int		parse_last_process(t_proc *proc, t_env *env, char **envp);
int		parse_pipe_token(t_list *token, t_env *env, char **envp);

/* parse_utils.c */

char	*my_strtrim(char *data, int start, int end);
int		check_token(t_list *token);
int		find_env_var_token(char *data, int start, int end);
int		find_valid_env_var_point(char *data);
int		find_valid_quot_point(char *data, int start);

/* split_token.c */

int		split_redirection_token(char *input, int i, t_list **token);
int		split_space_token(char *input, int i, t_list **token);
int		split_pipe_token(char *input, int i, t_list **token);
int		split_rest_token(char *input, t_list **token);
int		split_token(char *input, t_list **token);

/* utils.c */

int		error_msg(char *msg);
void	*ft_free(char *p);
void	*ft_free2(char **p);
char	*ft_strndup(char *s, int n);
char	*ft_strntrim(char *s, char *set, int n);


//void	add_history(char *line);

#endif
