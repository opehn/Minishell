/* ************************************************************************** */
/*																									 */
/*																		  :::		::::::::	*/
/*	err_util.c													  :+:		:+:	 :+:	*/
/*																	 +:+ +:+			+:+	  */
/*	By: taeheoki < taeheoki@student.42seoul.kr>	 +#+  +:+		 +#+		  */
/*																+#+#+#+#+#+	+#+			  */
/*	Created: 2022/04/26 16:52:56 by acho				  #+#	 #+#				 */
/*	Updated: 2022/04/30 15:48:31 by acho				 ###	########.fr		 */
/*																									 */
/* ************************************************************************** */

#include "custom_cmd.h"

extern int	g_exit_status;

void	custom_err_msg(char *func_name, char *msg, char *arg)
{
	ft_putstr_fd("minishell", STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(func_name, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	if (arg)
	{
		ft_putstr_fd("\'", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd("\'", STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putstr_fd(msg, STDERR_FILENO);
	write(1, "\n", 1);
}

int		notice_invalid_arg(char *func, char **opts_arr)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (opts_arr[i])
	 {
		  if (ft_strchr(opts_arr[i], ' '))
		  {
				custom_err_msg(func, "not a valid identifier", opts_arr[i]);
				flag = 2;
		  }
		  if (ft_strchr(opts_arr[i], '='))
		  {
				custom_err_msg(func, "not a valid identifier", opts_arr[i]);
				flag = 2;
		  }
		  if (ft_strchr(opts_arr[i], '-'))
		  {
				custom_err_msg(func, "not a valid identifier", opts_arr[i]);
				flag = 2;
		  }
		  i++;
	 }
	 return (flag);
}

int	perror_cd_many(char *project, char *pathname)
{
	ft_putstr_fd(project, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(pathname, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd("too many arguments", STDERR_FILENO);
	return (1);
}

int	perror_cd(char *project, char *pathname)
{
	ft_putstr_fd(project, STDERR_FILENO);
	ft_putstr_fd(": cd: ", STDERR_FILENO);
	ft_putstr_fd(pathname, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(strerror(errno), STDERR_FILENO);
	return (1);
}
