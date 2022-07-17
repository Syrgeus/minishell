/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdrowzee <jdrowzee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 13:33:29 by jdrowzee          #+#    #+#             */
/*   Updated: 2022/07/17 13:35:07 by jdrowzee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_handler(int status)
{
	pid_t	pid;

	pid = waitpid(-1, 0, WNOHANG);
	if (status == SIGINT)
	{
		if (pid == -1)
		{
			write(1, "\n", 1);
			ft_replace_line(1);
		}
		else
		{
			write(1, "\n", 1);
			st_flag = 130;
		}
	}
	else if (status == SIGQUIT && pid != -1)
	{
		write(1, "Quit: 3\n", 8);
		st_flag = 131;
	}
	else
		ft_replace_line(131);
}

void	ft_replace_line(int var_stat)
{
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	st_flag = var_stat;
}

void	execute_builtin_command(t_proc *proc, char **exe)
{
	if (ft_strncmp(proc->cmd->content, "echo", 5) == 0)
		ft_echo(&exe[1]);
	if (ft_strncmp(proc->cmd->content, "cd", 3) == 0)
		ft_cd(&exe[1], proc->env_lst);
	if (ft_strncmp(proc->cmd->content, "pwd", 4) == 0)
		ft_pwd();
	if (ft_strncmp(proc->cmd->content, "export", 7) == 0)
		ft_export(&exe[1], proc->env_lst, 0, 0);
	if (ft_strncmp(proc->cmd->content, "unset", 6) == 0)
		ft_unset(&exe[1], &proc->env_lst);
	if (ft_strncmp(proc->cmd->content, "env", 4) == 0)
		ft_env(proc->env_lst);
	if (ft_strncmp(proc->cmd->content, "exit", 5) == 0)
		ft_exit(&exe[1]);
	free(exe);
}

int	check_builtin_command(t_list *cmd)
{
	if (ft_strncmp(cmd->content, "echo", 5) == 0
		|| ft_strncmp(cmd->content, "cd", 3) == 0
		|| ft_strncmp(cmd->content, "pwd", 4) == 0
		|| ft_strncmp(cmd->content, "export", 7) == 0
		|| ft_strncmp(cmd->content, "unset", 6) == 0
		|| ft_strncmp(cmd->content, "env", 4) == 0
		|| ft_strncmp(cmd->content, "exit", 5) == 0)
		return (TRUE);
	cmd = cmd->next;
	return (FALSE);
}
