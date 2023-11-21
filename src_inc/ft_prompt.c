/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iengels <iengels@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 22:04:20 by iengels           #+#    #+#             */
/*   Updated: 2023/04/28 14:15:28 by iengels          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_prompt1(t_var *v)
{
	char	**new;
	char	*cwd;
	char	*tmp1;
	char	*tmp2;

	tmp1 = ft_strdup("\033[0;32m]\n\033[0;34m\033");
	tmp2 = ft_strdup("[0;32m\033[1m└─\033[0;34m\033[1m$ \033[0;0m");
	cwd = NULL;
	cwd = getcwd(cwd, 2000);
	new = malloc(sizeof(char *) * 6);
	new[0] = ft_strdup("\033[0;32m┌──(\033[0;34m\033[1m");
	new[1] = ft_get_own_env("USER", v);
	new[2] = ft_strdup("\033[0;34m\033[1m@minishell\033[0;32m)-[\033[0;0m\033[1m");
	new[3] = ft_strdup(cwd);
	new[4] = ft_strjoin(tmp1, tmp2);
	new[5] = NULL;
	if (new[1] == NULL)
		new[1] = ft_strdup("nouserset");
	free(cwd);
	free(tmp1);
	free(tmp2);
	return (new);
}

char	*ft_prompt(char **new)
{
	unsigned int	j[6];
	unsigned int	i;
	unsigned int	c;
	char			*prompt;

	c = 0;
	i = 0;
	while (new[i] != NULL)
	{
		j[i] = ft_strlen(new[i]);
		c += ft_strlen(new[i]);
		i++;
	}
	prompt = malloc(c + 1);
	prompt[c--] = '\0';
	while (i--)
	{
		while (j[i]--)
		{
			prompt[c] = new[i][j[i]];
			c--;
		}
	}
	return (prompt);
}

char	*ft_get_prompt(int id, int ac, char **av, t_var *v)
{
	char	**prompt1;
	char	*prompt;

	(void)ac;
	(void)av;
	if (id == 2)
		prompt = ft_strdup("\033[0;31m└─(|) pipe> \033[0;0m");
	else if (id == 3)
		prompt = ft_strdup("\033[0;35m└─(<<) heredoc> \033[0;0m");
	else if (id == 4)
		prompt = ft_strdup("\033[1;31m└─(>) input> \033[0;0m");
	else if (id == 5)
		prompt = ft_strdup("\033[1;33m└─(>>) append> \033[0;0m");
	else
	{
		prompt1 = ft_prompt1(v);
		prompt = ft_prompt(prompt1);
		ft_free_prompt1(prompt1);
		prompt1 = NULL;
	}
	return (prompt);
}

int	ft_heredoc_error(t_var *v, char **str)
{
	ft_putstr_fd("Unexpected termination due to EOF\nexit\n", 2);
	if (*str[0])
	{
		free(*str);
		*str = NULL;
	}
	v->true = 2;
	return (1);
}
