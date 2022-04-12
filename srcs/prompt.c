#include "prompt.h"
#include "error.h"
#include "env.h"
#include "parsing.h"

void    sigint_handler(int signum)
{
    ++signum;
    printf("\n");
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

void    set_signal(void)
{
    signal(SIGINT, sigint_handler);
    signal(SIGQUIT, SIG_IGN);
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
        temp->key = envp[i];
        temp->value = ft_strchr(envp[i], '=') + 1;
        *(temp->value - 1) = '\0';
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

void    init_info(t_info **info, t_env_list *env_list)
{
    *info = (t_info *)malloc(sizeof(t_info));
    if (!(*info))
        exit_error(ERR_MALLOC);
    (*info)->root = NULL;
    (*info)->env_list = env_list;
}

void    prompt(t_env_list *env_list)
{
    t_info  *info;
    char	*input;
    // int     i;

    // i = 0;
    init_info(&info, env_list);
    // while(env_list)
    // {
    //     printf("env[%d] : key = %s, value = %s\n", i, env_list->key, env_list->value);
    //     env_list = env_list->next;
    //     i++;
    // }
    while(1)
    {
        input = readline("acho> ");
        if (!input)
        {
            rl_replace_line("", 0);
            printf("exit");
            exit(0);
        }
        add_history(input);
        parsing(info, input);
        // action(info)
		// if (parsing(input))
		// {
		//   트리만듬
		//   cmd_run(tree)
		// }
    }
}

int main(int argc, char **argv, char **envp)
{
    t_env_list  *env_list;

    argc = 0;
    argv = NULL;
    printf("%d %p\n", argc, argv);
    //set_signal();
    init_env(&env_list, envp);
    prompt(env_list);
	return (0);
}