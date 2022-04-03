#include "prompt.h"
#include "parsing.h"
#include "error.h"

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

void    prompt(void)
{
    char	*input;

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
        parsing(input);
		// if (parsing(input))
		// {
			//트리만듬
			// cmd_run(tree)
		// }
    }
}

int main(void)
{
    set_signal();
    prompt();
	return (0);
}
