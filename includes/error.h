/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeheoki < taeheoki@student.42seoul.kr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 00:40:45 by taeheoki          #+#    #+#             */
/*   Updated: 2022/04/27 00:41:57 by taeheoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

//===========================exit error=====================================//
# define ERR_PIPE_SPLIT "Failure to split pipe"
# define ERR_PARSING "Failure to parse"
# define ERR_MALLOC "Failure to allocate memory"
# define ERR_NULL 	"NULL"
# define ERR_TOKENIZE "Failure to tokenize pipe_data"
# define ERR_FORK "Failure to fork"
# define ERR_REDIR "Failure to redirect"
# define ERR_HEREDOC "Failure to heredoc"
# define ERR_WAITPID "Failure to return exit status"

// ========================non-exit error===================================//
# define ERR_UNCLOSED 1
# define ERR_SYNTAX 2
# define ERR_RED 3
# define ERR_CMD 4
# define NOERR	5

# define MSG_UNCLOSED "Unclosed sequence detected"
# define MSG_SYNTAX "Syntex error"
# define MSG_RED "ambiguos rediretion"
# define MSG_CMD "invalid command" 

/*
** =============================================================================
** error_msg.c
** =============================================================================
*/
int		print_err(int res);
void	exit_error(char *str);

#endif
