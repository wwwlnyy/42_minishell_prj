#include "../include/wait_queue.h"
#include "../include/minishell.h"
#include "../include/execute.h"
#include "../include/exec_node_util.h"
#include "../include/exec_word_util.h"
#include "../include/filename_expansion.h"
#include "../include/arg_expansion.h"
#include "../include/make_argv_util.h"

void	enqueue(pid_t pid, t_context *p_ctx)
{
	if (p_ctx->queue_size >= PROC_MAX)
		exit(1);
	p_ctx->queue[p_ctx->queue_size] = pid;
	p_ctx->queue_size++;
}

void	wait_queue(t_context *p_ctx)
{
	int	idx;
	int	size;

	idx = 0;
	size = p_ctx->queue_size;
	while (idx < size)
	{
		wait_and_set_exit_status(p_ctx->queue[idx], p_ctx, 0);
		idx++;
		p_ctx->queue_size--;
	}
}
