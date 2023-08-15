#include "../include/minishell.h"
#include "../include/tokenizer.h"

//io_redirect_dg_after_simple_cmd ::= WORD io_redirect_star
//io_redirect_dg_after_simple_cmd ::= empty
t_node  *io_redirect_dg_after_simple_cmd(t_tokenizer *tokenizer)
{
	t_node  *parent;
	t_node  *child;

	if (match_token(WORD, tokenizer))
	{
		child = make_leaf(tokenizer);
		parent = io_redirect_star(tokenizer);
		return (merge_tree(parent, child)); //만약 word-word가 만나면 child word + parent word = new word가 되어야함
	}
	return (NULL);
}

//io_redirect_star ::= io_redirect io_redirect_star
//io_redirect_star ::= empty
t_node  *io_redirect_star(t_tokenizer *tokenizer)
{
	t_node  *parent;
	t_node  *child;
    t_token *tk;

    tk = tokenizer->curr_token;
	if (check_first_set(IO_REDIRECT, tk->type))
	{
		parent = io_redirect(tokenizer);
		child = io_redirect_star(tokenizer);
		return (merge_tree(parent, child));
	}
	return (NULL);
}

//io_redirect ::= io_file
//io_redirect ::= io_here
t_node  *io_redirect(t_tokenizer *tokenizer)
{
	t_token *tk;

    tk = tokenizer->curr_token;
	if (check_first_set(IO_FILE, tk->type))
		return (io_file(tokenizer));
	else if (check_first_set(IO_HERE, tk->type))
		return (io_here(tokenizer));
	syntax_error("Not available grammar");
	return (NULL);
}

//io_file ::= LESS WORD
//io_file ::= GREAT WORD
//io_file ::= DGREAT WORD
t_node  *io_file(t_tokenizer *tokenizer)
{
	if(match_token(LESS, tokenizer) && get_curr_token(tokenizer) == WORD)
		return (make_tree(LESS, NULL, make_leaf(tokenizer)));
	if(match_token(GREAT, tokenizer) && get_curr_token(tokenizer) == WORD)
		return (make_tree(GREAT, NULL, make_leaf(tokenizer)));
	if(match_token(DGREAT, tokenizer) && get_curr_token(tokenizer) == WORD)
		return (make_tree(DGREAT, NULL, make_leaf(tokenizer)));
	syntax_error("Not available grammar");
	return (NULL);
}

//io_here ::= DLESS WORD
t_node  *io_here(t_tokenizer *tokenizer)
{
	if(match_token(DLESS, tokenizer) && get_curr_token(tokenizer) == WORD)
		return (make_tree(DLESS, NULL, make_leaf(tokenizer)));
	syntax_error("Not available grammar");
	return (NULL);
}