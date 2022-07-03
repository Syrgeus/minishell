#include "../include/minishell.h"

int main (int argc, char **argv, char **env)
{
    t_struct    shell = {};    
    
    char    *buf = *env;
    //shell.exit_flag = 0;

    printf("%d\n, %c\n\n, %s\n", argc, *argv[0], buf);
    while (!shell.exit_flag)
    {
        rl_replace_line("", 0);  
        shell.line = readline("minishell$ ");
        if (shell.line && *shell.line)
			add_history(shell.line);
        printf("%s\n", shell.line);                
    }
    
    
    return (0);
}