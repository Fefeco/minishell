/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifer2 <davifer2@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 18:10:16 by davifer2          #+#    #+#             */
/*   Updated: 2024/06/27 18:51:35 by davifer2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static const char	*get_token_type(t_tokens *lexer_nodes)
{
	const char	*token_type;

	if (lexer_nodes->token == PIPE)
		token_type = "PIPE";
	else if (lexer_nodes->token == GTHAN)
		token_type = "GTHAN";
	else if (lexer_nodes->token == STHAN)
		token_type = "STHAN";
	else if (lexer_nodes->token == H_DOC)
		token_type = "H_DOC";
	else if (lexer_nodes->token == APPEND)
		token_type = "APPEND";
	else
		token_type = "WORD";
	return (token_type);
}

void	ft_test_lexer(t_tokens *lexer_nodes)
{
	const char	*token_type;

	ft_printf("==============\n= Test lexer =\n==============\n");
	while (lexer_nodes)
	{
		token_type = get_token_type(lexer_nodes);
		ft_printf("Token: |%s| Type: %s\n", lexer_nodes->value, token_type);
		lexer_nodes = lexer_nodes->next;
	}
	ft_printf("============\n= End test =\n============\n");
}

void	ft_test_parser(t_cmd *parser_nodes)
{
	int	i;

	ft_printf("===============\n= Test parser =\n===============\n");
	while (parser_nodes)
	{
		i = -1;
		while (parser_nodes->cmd_array && parser_nodes->cmd_array[++i])
			printf("cmd_array[%d] = %s\n", i, parser_nodes->cmd_array[i]);
		if (parser_nodes->redir_in)
			ft_printf("redir_in fd = %d file_name = %s\n",
				parser_nodes->redir_in->fd, parser_nodes->redir_in->filename);
		else
			ft_printf("NO redir_in\n");
		if (parser_nodes->redir_out)
			ft_printf("redir_out fd = %d file_name = %s\n",
				parser_nodes->redir_out->fd, parser_nodes->redir_out->filename);
		else
			ft_printf("NO redir_out\n");
		parser_nodes = parser_nodes->next;
		if (parser_nodes)
			ft_printf("=== AQUI VA PIPE ===\n");
	}
	ft_printf("============\n= End test =\n============\n");
}

static void	ft_test_random_filename(char *name)
{
	int	i;

	i = 0;
	ft_printf("=================\n= Test filename =\n=================\n");
	printf("File_name: \n");
	while (i < 6)
	{
		printf("%02x", name[i++]);
	}
	printf("\n");
	ft_printf("============\n= End test =\n============\n");
}

// static void	ft_test_envs(t_env *env_list)
// {
// 	ft_printf("========\n= Test envirorments variables =\n========\n");
// 	while (env_list)
// 	{
// 		ft_printf("%s=%s\n", env_list->key, env_list->value);
// 		env_list = env_list->next;
// 	}
// 	ft_printf("=================\n= End Test =\n=================\n");
// }

void	init_tests(t_tokens *lexer_nodes, t_cmd *parser_nodes, t_env *envs)
{
	char	*filename;

	(void)parser_nodes;
	filename = ft_random_filename();
	printf("\n\n");
	ft_test_lexer(lexer_nodes);
	ft_test_parser(parser_nodes);
	ft_test_random_filename(filename);
	(void)envs;
	free(filename);
	printf("\n\n");
}
