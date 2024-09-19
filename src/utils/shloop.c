/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shloop.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcarranz <fcarranz@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 10:16:30 by fcarranz          #+#    #+#             */
/*   Updated: 2024/09/02 11:33:26 by fcarranz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*put_path_prompt(char *cwd, t_utils *utils)
{
	char	short_pathname[PATH_MAX];
	char	info_machine[PATH_MAX];
	char	prompt[PATH_MAX];

	ft_bzero(info_machine, PATH_MAX);
	get_user_and_hostname(info_machine, utils->envs);
	get_short_path(short_pathname, cwd, utils);
	ft_strlcpy(prompt, "\001" ANSI_COLOR_GREEN "\002", sizeof(prompt));
	ft_strlcat(prompt, info_machine, sizeof(prompt));
	ft_strlcat(prompt, "\001" ANSI_COLOR_RESET "\002", sizeof(prompt));
	ft_strlcat(prompt, ":", sizeof(prompt));
	ft_strlcat(prompt, "\001" ANSI_COLOR_BLUE "\002", sizeof(prompt));
	ft_strlcat(prompt, short_pathname, sizeof(prompt));
	ft_strlcat(prompt, "\001" ANSI_COLOR_RESET "\002", sizeof(prompt));
	ft_strlcat(prompt, "$ ", sizeof(prompt));
	return (ft_strdup(prompt));
}

void	init_prompt(char *cwd, char **line, t_utils *utils)
{
	char	*prompt;

	prompt = put_path_prompt(cwd, utils);
	if (!prompt)
		*line = readline(PROMPT);
	*line = readline(prompt);
	free(prompt);
}

static void	process_line(char *line, t_utils *utils)
{
	t_tokens	*lexer_nodes;
	t_cmd		*parser_nodes;

	detect_ctrl_c(utils);
	lexer_nodes = ft_lexer(line);
	if (ft_check_syntax(lexer_nodes, &line))
	{
		free(line);
		return ;
	}
	add_history(line);
	free(line);
	parser_nodes = ft_parser(lexer_nodes, utils);
	ft_expander(parser_nodes, utils, utils->exit_status);
	ft_search_path(parser_nodes, utils);
	if (ft_remove_parser_quotes(parser_nodes) == -1)
	{
		utils->status = 0;
		free_loop(lexer_nodes, parser_nodes);
		return ;
	}
	ft_executor(parser_nodes, utils);
	free_loop(lexer_nodes, parser_nodes);
}

int	set_dir(char **line, t_utils *utils)
{
	t_env	*node;

	node = ft_get_env_from_list(utils->envs, "OLDPWD");
	if (node && node->value)
	{
		chdir(node->value);
		return (1);
	}
	else
	{
		*line = readline(PROMPT);
		return (1);
	}
}

void	ft_shloop(t_utils *utils)
{
	char	*line;
	char	cwd[PATH_MAX];

	line = NULL;
	while (utils->status == -1)
	{
		set_signals(NON_INTERACTIVE);
		if (getcwd(cwd, sizeof(cwd)))
			init_prompt(cwd, &line, utils);
		else
			if (set_dir(&line, utils))
				continue ;
		if (!line)
		{
			ft_putstr_fd("exit\n", 1);
			break ;
		}
		utils->cmds_amount++;
		process_line(line, utils);
	}
	rl_clear_history();
}
