/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifer2 <davifer2@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 11:21:43 by davifer2          #+#    #+#             */
/*   Updated: 2024/08/01 21:18:52 by davifer2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_error_exit(int fd, char *cmd)
{
	ft_putstr_fd("exit\n", fd);
	ft_putstr_fd("mini: exit: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
}

static int	handle_sign(char **str, int sign)
{
	if (**str == '-' || **str == '+')
	{
		if (**str == '-')
			sign = -1;
		(*str)++;
	}
	return (sign);
}

static long	convert_to_long(const char *str, char **endptr)
{
	long	result;
	int		sign;

	result = 0;
	sign = 1;
	*endptr = (char *)str;
	while (ft_isspace((unsigned char)**endptr))
		(*endptr)++;
	sign = handle_sign(endptr, sign);
	while (ft_isdigit((unsigned char)**endptr))
	{
		if (result > (LONG_MAX - *(*endptr) - '0') / 10)
		{
			errno = ERANGE;
			if (sign)
				return (LONG_MAX);
			return (LONG_MIN);
		}
		result = result * 10 + (*(*endptr) - '0');
		(*endptr)++;
	}
	return (sign * result);
}

int	ft_exit(char **args, int fd, t_utils *utils)
{
	char	*endptr;
	long	exit_code;

	++args;
	if (*args)
	{
		exit_code = convert_to_long(*args, &endptr);
		if ((errno == ERANGE || exit_code == LONG_MAX) || *endptr != '\0')
		{
			print_error_exit(fd, *args);
			utils->exit_status = 2;
			utils->status = 0;
			return (utils->exit_status);
		}
		if (args[1])
		{
			ft_putstr_fd("exit\n", fd);
			ft_putstr_fd("mini: exit: too many arguments\n", 2);
			return (1);
		}
		utils->exit_status = ft_atoi(*args);
	}
	ft_putstr_fd("exit\n", fd);
	utils->status = 0;
	return (utils->exit_status);
}
