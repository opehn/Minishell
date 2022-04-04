
#include "libft.h"

typedef struct s_env_list 
{
	char	*key;
	char	*value;
	struct s_env_list *next;
} t_env_list;