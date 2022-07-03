#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <readline/readline.h>

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

void	add_history(char *line);
#endif
