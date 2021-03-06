/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeheoki < taeheoki@student.42seoul.kr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 16:02:05 by acho              #+#    #+#             */
/*   Updated: 2022/04/30 12:49:16 by acho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"
#include "error.h"
#include "env.h"
#include "parsing.h"
#include "action.h"

void	init_env(t_env_list **env_list, char **envp)
{
	int			i;
	t_env_list	*temp;

	*env_list = (t_env_list *)malloc(sizeof(t_env_list));
	if (!*env_list)
		exit_error(ERR_MALLOC);
	temp = *env_list;
	i = 0;
	while (envp[i])
	{
		temp->key = ft_strndup(envp[i], ft_strchr(envp[i], '=') - envp[i] + 1);
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

void	init_info(t_info **info, char **envp, t_env_list *env_list)
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

char	*prompt_readline(char *prompt)
{
	char	*input;

	signal(SIGQUIT, SIG_IGN);
	input = readline(prompt);
	set_signal();
	return (input);
}

void	prompt(char **envp, t_env_list *env_list)
{
	t_info	*info;
	char	*input;
	int		res;

	init_info(&info, envp, env_list);
	while (1)
	{
		input = prompt_readline("minishell$ ");
		if (!input)
		{
			rl_replace_line("", 0);
			printf("exit\n");
			exit(0);
		}
		add_history(input);
		res = parsing(info, input);
		if (!res)
			action(info);
		delete_info(info);
		free(input);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_env_list	*env_list;

	argv += argc;
	free(*argv);
	set_signal();
	init_env(&env_list, envp);
	prompt(envp, env_list);
	return (0);
}
