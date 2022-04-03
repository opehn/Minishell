#ifndef MINISHELL_ERROR_H
# define MINISHELL_ERROR_H

//===========================exit error=====================================//
# define ERR_PIPE_SPLIT "Failure to split pipe"
# define ERR_PARSING "Failure to parse"
# define ERR_MALLOC "Failure to allocate memory"

// ========================non-exit error===================================//
# define ERR_UNCLOSED 1
# define ERR_SYNTAX 2

# define MSG_UNCLOSED "Unclosed sequence detected"
# define MSG_SYNTAX "Syntex error"

#endif

// 내 생각이 뭐였냐면 일단 파이프안에 전부 넣어 그게 널이든 데이터조각이든
// 그러면 pipe_parsing 자체는 끝났어
// 그 다음 pipe 리스트로 Syntex error 체크를 바로 돌리는건 어떨까라는 거지

// pipe[0] = sflkgjfsdg
// pipe[1] = (NULL) or space
// pipe[2] = s;dofgjpsdfg
// pipe[3] = (NULL)

// 1. abc |
// 	pipe[0] = abc
// 	pipe[1] = NULL
// 	pipe[2] = NULL

// 2. abc
// 	pipe[0] = abc
// 	pipe[1] = NULL



