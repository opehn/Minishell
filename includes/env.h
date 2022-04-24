#ifndef ENV_H
# define ENV_H

typedef struct s_env_list 
{
	char	*key;
	char	*value;
	struct s_env_list *next;
} t_env_list;

t_env_list  *new_env_list(char *arg, char *equal);
void    append_env_list(t_env_list *env_list, char *arg, char *equal);

#endif
