/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 09:11:04 by nrechati          #+#    #+#             */
/*   Updated: 2019/04/18 17:18:07 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "resolve.h"

int		add_to_test(t_list **test, void *fct)
{
	t_list *cmd;

	if (!(cmd = (t_list *)malloc(sizeof(t_list))))
		return (0);
	cmd->data_size = 0;
	cmd->data = fct;
	cmd->next = NULL;
	ft_lstaddback(test, cmd);
	return (1);
}

int		new_cmd(t_list **alst, char **env, int (*init)(t_instr *, char **))
{
	t_instr cmd;
	t_list *newdir;

	ft_bzero(&cmd, sizeof(t_instr));
	init(&cmd, env);
	if (!(newdir = ft_lstnew(&cmd, sizeof(t_instr))))
		return (0);
	ft_lstaddback(alst, newdir);
	return (1);
}

int		test_to_bench(t_hash *hashmap, t_list **stack, char **env, char *test)
{
	t_list	*ptr;

	ptr = ft_hmap_getdata(hashmap, test);
	if (!ptr)
		return (ft_dprintf(2, "\x1b[31m[ERROR]: Hashmap getdata FAILED\n\x1b[0m") & 0);
	while (ptr)
	{
		if (!new_cmd(stack, env, ptr->data))
			return (ft_dprintf(2, "\x1b[31m[ERROR]: Hashmap getdata FAILED\n\x1b[0m") & 0);
		ptr = ptr->next;
	}
	return (1);
}

int		print_test_stack(t_list **stack, char *test)
{
	int		i;
	t_list	*ptr;

	i = 1;
	ptr = *stack;
	ft_dprintf(2, "\n\x1b[32m[PRINTING]: ********** %s **********\n\n\x1b[0m", get_line(test));
	while (ptr)
	{
		if (((t_instr *)ptr->data)->env)
			ft_printf("\x1b[93m CMD %d || ac = %d | av : %s | env : OK | IN = %d | OUT = %d | ERR = %d ||\n\x1b[0m"
			, i, ((t_instr *)ptr->data)->ac, get_line(test), ((t_instr *)ptr->data)->fd_in
			,((t_instr *)ptr->data)->fd_out, ((t_instr *)ptr->data)->fd_err);
		else
			return (ft_dprintf(2, "\x1b[31m[ERROR]: %s ENV is empty\n\x1b[0m", ((t_instr *)ptr->data)->av) & 0);
		ptr = ptr->next;
		i++;
	}
	return (1);
}

static int get_env(t_list **alst, char **env)
{
	int i;

	i = 0;
	while (env[i] != NULL)
	{
		if (!f_create_node(alst, env[i]))
			return (0);
		i++;
	}
	return (1);
}

int		main(int ac, char **av, char **env)
{
	t_list		*stack;
	void 		*data;
	t_hash 		hashmap;
	t_list		*env_lst = NULL;
	t_registry	registry;

	/* Init Fake Registry */
	ft_bzero(&registry, sizeof(t_registry));
	get_env(&env_lst, env);
	registry.env = env_lst;

	/* Init Test bench hashmap */
	hashmap = ft_hmap_init(16);
	if (!hashmap.map)
		return (ft_dprintf(2, "\x1b[31m[ERROR]: Failed to malloc hashmap\n\x1b[0m") & 0);
	if (!fill_test_bank(&hashmap))
		return (0);

	/* Init registry hashmaps */
	registry.bin_hashmap = ft_hmap_init(4096);
	registry.blt_hashmap = ft_hmap_init(16);
	hash_blt(&registry);

	/* Print Test Bench Hashmap */
	ft_print_hashmap_p(&hashmap) ; ft_printf("\n\x1b[0m");
	if (ac != 2)
		return (ft_dprintf(2, "USAGE: ./resolve [test]\n\x1b[0m"));

	/* Load test */
	stack = NULL;
	if (!test_to_bench(&hashmap, &stack, env, av[1]))
		return (ft_dprintf(2, "\x1b[31m[ERROR]: Failed to load %s\n\x1b[0m", av[1]));
	ft_dprintf(2, "\x1b[32m[SUCCESS]: Test Bank INIT succeeded\n\x1b[0m");
	ft_dprintf(2, "\x1b[32m[SUCCESS]: Test Bank LOAD succeeded\n\x1b[0m");
	ft_dprintf(2, "\x1b[32m[SUCCESS]: \x1b[93m%s\x1b[32m INIT succeeded\n\x1b[0m", get_line(av[1]));

	/*	Print test */
	if (!print_test_stack(&stack, av[1]))
		return (0);

	/* Resolve test */
	resolve_stack(&stack, &registry);

	ft_dprintf(2, "\x1b[32m[SUCCESS]: Test \x1b[93m| %s |\x1b[32m finished with success\n\x1b[0m", get_line(av[1]));
	return (0);
}
