#include "prompt.h"
#include "error.h"
#include "env.h"
#include "parsing.h"
#include "action.h"

void	signal_handler(int signum)
{
    pid_t   pid;
    int     status;

    pid = waitpid(-1, &status, WNOHANG);
    if (signum == SIGINT)
    {
        if (pid == -1)
        {
            ft_putendl_fd("", STDOUT_FILENO);
            rl_on_new_line();
            rl_replace_line("", 0);
            rl_redisplay();
        }
        else
            ft_putendl_fd("", STDOUT_FILENO);
    }
    else if (signum == SIGQUIT)
    {
        if (pid == 0)
        {
            printf("checking %d in signal\n", pid);
            ft_putendl_fd("Quit: 3", STDOUT_FILENO);
            rl_on_new_line();
		    rl_replace_line("", 0);
        }
        else
        {
            rl_on_new_line();
            rl_replace_line("", 1);
	    	rl_redisplay();
            // write(1, "\b\b\b\b", 4);
        }
    }
}

void    set_signal(void)
{
    signal(SIGINT, signal_handler);
    signal(SIGQUIT, signal_handler);
}

void    init_env(t_env_list **env_list, char **envp)
{
    int         i;
    t_env_list  *temp;

    *env_list = (t_env_list *)malloc(sizeof(t_env_list));
    if (!*env_list)
        exit_error(ERR_MALLOC);
    temp = *env_list;
    i = 0;
    while (envp[i])
    {
        temp->key = ft_strndup(envp[i], ft_strchr(envp[i], '=') - envp[i]);
        temp->value = ft_strdup(ft_strchr(envp[i], '=') + 1);
        if (envp[++i])
        {
            temp->next = (t_env_list *)malloc(sizeof(t_env_list));
            if (!temp->next)
                exit_error (ERR_MALLOC);
            temp = temp->next;
        }
    }
    temp->next = NULL;
}

void    init_info(t_info **info, char **envp, t_env_list *env_list)
{
    *info = (t_info *)malloc(sizeof(t_info));
    if (!(*info))
        exit_error(ERR_MALLOC);
    (*info)->root = NULL;
    (*info)->forest = NULL;
	(*info)->envp = envp;
    (*info)->env_list = env_list;
    (*info)->heredoc = NULL;
}

void    prompt(char **envp, t_env_list *env_list)
{
    t_info  *info;
    char	*input;
	int		res;

    init_info(&info, envp, env_list);
    while(1)
    {
        input = readline("minishell> ");
        if (!input)
        {
            rl_replace_line("", 0);
            printf("exit\n");
            exit(0);
        }
        add_history(input);
        res = parsing(info, input);
		if (!res)
		{
			action(info);
		}
    }
}

int main(int argc, char **argv, char **envp)
{
    t_env_list  *env_list;

    argc = 0;
    argv = NULL;
    printf("%d %p\n", argc, argv);
    set_signal();
    init_env(&env_list, envp);
    prompt(envp, env_list);
	return (0);
}
