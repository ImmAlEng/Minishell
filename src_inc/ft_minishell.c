/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iengels < iengels@student.42vienna.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 22:07:24 by iengels           #+#    #+#             */
/*   Updated: 2023/04/28 23:13:55 by iengels          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_status;

void	ft_lists_are_null(t_dlist **l, t_tlist **lis)
{
	*l = NULL;
	*lis = NULL;
}

void	ft_export_to_env(t_var *v, t_dlist *export)
{
	int		i;
	t_dlist	*expor;

	i = 0;
	expor = export;
	while (v->env[i])
		free(v->env[i++]);
	free(v->env);
	i = 0;
	while (export != NULL)
	{
		i++;
		export = export->next;
	}
	export = expor;
	v->env = malloc(i + 1);
	i = 0;
	while (export)
	{
		v->env[i++] = export->str;
		export = export->next;
	}
	export = expor;
}

void	main_to_big(t_dlist **l, t_tlist **lis, t_var *v, t_dlist **export)
{
	v->path = ft_get_path(*export);
	if (v->input[0] == '\0' || ft_check_inputline(v->input) == 0)
	{
		v->id = 1;
		free(v->input);
		ft_putchar_fd('\n', 1);
	}
	else
	{
		add_history(v->input);
		if (ft_lis_and_token(v, &(*l), &(*lis)) == 0)
		{
			if (v->id == 1)
			{
				if (ft_input_check(*lis, v, &*export) == 0)
					ft_putstr_fd("command not found.\n", 2);
			}
		}
		ft_free_innerloop(v, &(*lis));
	}
	free_stuff(v->path);
}

int	main(int ac, char **av, char **env)
{
	t_var	*v;
	t_dlist	*export;
	t_dlist	*l;
	t_tlist	*lis;

	ft_lists_are_null(&l, &lis);
	v = (t_var *)malloc(sizeof(t_var));
	ft_vars_initiate(v, env, &export);
	while (v->true == 1)
	{
		signal(SIGINT, ft_sigint);
		signal(SIGQUIT, SIG_IGN);
		v->minishell = ft_get_prompt(v->id, ac, av, v);
		v->input = readline(v->minishell);
		ft_free_prompt(v);
		if (v->input == NULL)
			v->true = 2;
		else
			main_to_big(&l, &lis, v, &export);
	}
	rl_clear_history();
	ft_free_all(export);
	free(v);
	return (0);
}

/*
{
   readline
   Memcheck:Leak
   ...
  fun:*
}
*/