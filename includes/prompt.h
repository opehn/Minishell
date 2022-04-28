/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeheoki < taeheoki@student.42seoul.kr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 00:55:13 by taeheoki          #+#    #+#             */
/*   Updated: 2022/04/28 22:54:18 by acho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_H
# define PROMPT_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>
# include <unistd.h>
# include <signal.h>
# include <stdlib.h>
# include "libft.h"
# include <stdio.h>
# include "parsing.h"

/*
** =============================================================================
** signal_handler.c
** =============================================================================
*/
void	signal_handler(int signum);
void	set_signal(void);

/*
** =============================================================================
** prompt.c
** =============================================================================
*/
void	init_env(t_env_list **env_list, char **envp);
void	init_info(t_info **info, char **envp, t_env_list *env_list);
char	*prompt_readline(char *prompt);
void	prompt(char **envp, t_env_list *env_list);

#endif
