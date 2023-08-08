#include "minishell.h"

t_node	*parse(t_tokenizer *token)
{
	t_node	*root;

	if (EOF)
	{
		//종료
		return (NULL);
	}
	root = msh_grammer(token); //생성규칙 따라 트리 생성
	if (token != EOF)
	{
		//syntax error
		//free root
		//종료
		return (NULL);
	}
	return (root);
}

t_tokenizer	get_next_token()
{
	t_tokenizer res;
	
}