#include "../minishell.h"

void	print_ar(char **ar)
{
	int	i;

	i = 0;
	while (ar[i])
	{
		printf("'%s'\n", ar[i]);
		i++;
	}
	///IIIIIIIIIIIIIII DELEEETE MEEEEEE
}

void	print_lists(t_redi *current)
{
	int	i = 1;

//	printf("%p\n", current);
	////remove this
	while (current)
	{
		printf("%d", i);
		if (i % 10 == 1 && i % 100 != 11)
			printf(":st");
		else if (i % 10 == 2 && i % 100 != 12)
			printf(":nd");
		else if (i % 10 == 3 && i % 100 != 13)
			printf(":rd");
		else
			printf(":th");
		printf(" node is of type %d, in pipe %zu spot %zu\n", current->type, current->pipe_n, current->red_n);
	//	printf(" node has n %d h %d and validness of %d\n", current->n, current->h, current->valid);
		current = current->next;
		i++;
	}
}

void	print_node(t_cond *node, int b, int sub_b, int level)
{
	printf("level [%d] branch[%d][%d] node type %d\n", level, b, sub_b, node->type);
	if (!node->type)
		printf("content:\n%s\n", node->content);
}

void	print_tree(t_cond *head, int b, int sub_b, int level)
{
	if (!head)
		return ;
	print_tree(head->first_cond, b, sub_b, level + 1);
	print_node(head, b, sub_b, level);
	print_tree(head->sec_cond, b, sub_b + 1, level);//
	print_tree(head->next, b + 1, sub_b, level);
}

void	print_tokens(t_error *he)   
{
	/////fdsafdsa
	printf("current active tokens:\n");
	if (he->q)
		printf("q\n");
	if (he->sq)
		printf("sq\n");
	if (he->plus_yes)
		printf("plus_yes\n");
	if (he->token)
		printf("token\n");
	if (he->or)
		printf("or\n");
	if (he->pipe)
		printf("pipe\n");
	if (he->and)
		printf("and\n");
	if (he->amper)
		printf("amper\n");
	if (he->out_o)
		printf("out o\n");
	if (he->in_o)
		printf("in o\n");
	if (he->out_t)
		printf("out t\n");
	if (he->in_t)
		printf("in t\n");
	if (he->par != 0)
		printf("par is %d\n", he->par);
}
