/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdg <sdg@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 11:26:07 by naylee            #+#    #+#             */
/*   Updated: 2023/08/14 12:47:11 by sdg              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


t_bool	match_token(t_symbol type, t_tokenizer *tokenizer)
{ 
   //현재 토큰이 매개변수와 같으면 match 성공
   if(type == get_curr_token(tokenizer)->type)
   {
		//다음토큰을 찾아놓음
		get_next_token(tokenizer);
		return (TRUE);
   }
   //현재 토큰이 매개변수와 다를때
   return (FALSE);

}

t_token	*get_curr_token(t_tokenizer *tokenizer) {
    return (tokenizer->curr_token);
}


// init_tokenizer(char* line)  ==> t_tokenizer를 만든다.
// curr_token_start_ptr, curr_token_end_ptr 이 ls를 가리키고있다

// get_next_token() ==> t_tokenizer를 갱신한다.
// 갱신되면 t_tokenizer는 다른 토큰(문자열)을 가리키게 된다

//get_next_token() -> 원래 예전에 만들어놨던 t_tokenizer를 갱신.
t_token	*get_next_token(t_tokenizer *tokenizer)
{
	t_token token;

	reset_start_ptr(tokenizer);
	if (*tokenizer->end == '(')
	{
		tokenizer->start++;
		while (*tokenizer->end != '\0' && *tokenizer->end != ')')
			tokenizer->end++;
		if (*tokenizer->end == ')')
		{
			tokenizer->end--;
			return (make_token(tokenizer, SUBSHELL));
		}
		else
		{
			printf("syntax error\n");
			//syntax_error("~~~");
			//종료코드
		}
	}
	if (*tokenizer->end == ')')
	{
		printf("syntax error\n");
		//syntax_error("~~~");
		//종료코드
	}
	return (scan_char_token(tokenizer));
}


static char	*make_empty_str(void)
{
	char	*res;

	res = (char *)malloc(sizeof(char) * (1));
	if (!res)
		return (0);
	res[0] = '\0';
	return (res);
}

#include <string.h>

static size_t	fft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

static char	*fft_substr(char const *s, unsigned int start, size_t len)
{
	char			*res;
	size_t			i;
	unsigned int	s_len;

	if (*s == 0)
		return (make_empty_str());
	s_len = (unsigned int)fft_strlen(s);
	if (s_len <= start)
		len = 0;
	i = 0;
	while (i < len && s[start + i])
		i++;
	res = (char *)malloc(sizeof(char) * (i + 1));
	if (!res)
		return (0);
	i = 0;
	while (i < len && s[start + i])
	{
		res[i] = s[start + i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

t_token	*make_token(t_tokenizer *tokenizer, t_symbol type)
{
	tokenizer->curr_token->type = type;
	tokenizer->curr_token->len = tokenizer->end - tokenizer->start + 1;
	tokenizer->curr_token->str = fft_substr(tokenizer->start, 0, tokenizer->curr_token->len);
	return (tokenizer->curr_token);
}

// t_token 추가(한개, 계속 갱신)
// 문자열비교할때 curr_token으로 비교
// 

//환경변수 replace
//void	replace_env(t_tokenizer *tokenizer)
//{
//	char	*env;

//	env = ft_substr(tokenizer->start, tokenizer->end - tokenizer->start);

//}
