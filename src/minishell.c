#include "../include/minishell.h"
#include "../include/parser.h"
#include "../include/execute.h"
#include "../include/execute_util.h"
#include "../include/here_doc.h"
#include "../include/ms_signal.h"

void __leak()
{
	system("leaks minishell");
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	init_envp(envp);
	minishell_loop();
	atexit(__leak);
}

void	init_envp(char **envp)
{
	t_list	**env;
	int		idx;

	env = get_envp();
	idx = 0;
	ft_lstadd_back(env, NULL);
	while (envp[idx])
	{
		ft_lstadd_back(env, ft_lstnew(ft_strdup(envp[idx])));
		idx++;
	}
}

t_list	**get_envp(void)
{
	static t_list	*env_list;

	return (&env_list);
}

void	print_eof_exit()
{
	ft_putstr_fd("\033[1A", STDOUT);
	// if (get_heredoc_data()->heredoc_fault_flag == FALSE)
	// 	ft_putstr_fd("\033[2C", STDOUT);
	ft_putstr_fd("\033[8C", STDOUT);
	printf("exit\n");
}

void	minishell_loop(void)
{
	t_node		*root;
	char		*line;

	sigact_default_mode();
	line = "";
	while (line)
	{
		set_heredoc_fault_flag(FALSE);		
		line = readline("prompt> ");
		if (line)
		{
			if (*line != '\0')
				add_history(line);
			root = parser(line);
			execute(root);
			free_tree(root);
			free(line);			
		}
	}
	print_eof_exit();
}
