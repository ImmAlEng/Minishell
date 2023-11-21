/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iengels < iengels@student.42vienna.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 22:04:12 by iengels           #+#    #+#             */
/*   Updated: 2023/04/28 22:13:20 by iengels          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <dirent.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/ioctl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

extern int			g_status;
typedef struct s_dlist
{
	char			*str;
	int				q;
	struct s_dlist	*prev;
	struct s_dlist	*next;
}					t_dlist;

typedef struct s_tlist
{
	char			*command;
	char			**flargs;
	char			*op;
	char			**env;
	char			*path;
	pid_t			pid;
	char			*doc;
	struct s_tlist	*prev;
	struct s_tlist	*next;
}					t_tlist;

typedef struct s_var
{
	char			**env;
	char			**path;
	int				count_token;
	int				true;
	int				fd[2];
	pid_t			*pid;
	int				in;
	int				t;
	int				op_check;
	int				wstatus;
	int				j;
	int				id;
	int				build_in;
	char			*output;
	char			*input;
	char			*minishell;
	struct s_tlist	*head;
	struct s_dlist	*exp;
}					t_var;

void				ft_sigint(int sig);
int					ft_check_open_q(char *s);
int					ft_incomplete(t_tlist *lis, t_var *v);
int					ft_check_export_arg(char *s, t_dlist *export, t_tlist *lis,
						t_var *vars);
char				*ft_get_prompt(int id, int ac, char **av, t_var *v);
void				ft_add_dlist_back(t_dlist **lis, char *str, int q);
t_dlist				*ft_create_dlist(char *str, int q);
void				ft_print_list(t_dlist *head);
t_dlist				*ft_freelist(t_dlist *head);
int					ft_check_open_q(char *s);
void				ft_tokens(char *s, t_dlist **t, int m_q[3]);
unsigned int		ft_space_check(char c, int q);
void				ft_truncate(t_dlist **p, int q[3], t_var *v);
unsigned int		ft_is_operator(char *s, unsigned int q);
void				ft_add_tlist_back(t_tlist **lis);
t_tlist				*ft_create_tlist(void);
t_tlist				*ft_real_token(t_dlist *v, t_tlist *t, t_var *j);
int					ft_get_qvariable(char *s1, unsigned int **d, t_var *v);
void				ft_print_token(t_tlist *head);
int					ft_input_check(t_tlist *lis, t_var *vars, t_dlist **export);
t_tlist				*ft_freetoken(t_tlist *l);
char				**ft_get_path(t_dlist *export);
int					ft_getdir(void);
int					ft_print_env(t_dlist *export, int i);
int					ft_change_dir(t_tlist *lis, t_dlist **export);
int					ft_do_unset(t_dlist **expor, t_tlist *lis);
t_dlist				*ft_export_list(t_var *v);
int					ft_do_export(t_dlist **expor, t_tlist *lis);
void				close_fds_start(t_var *vars);
void				close_fds_end(t_var *vars);
void				ft_close(int fd);
int					ft_count_token(t_tlist *lis);
int					ft_check_operator(t_tlist *lis, t_var *vars);
int					ft_check_access(t_var *vars, char *str, char *path);
int					ft_build_in(t_tlist **l, t_var *vars, t_dlist **export);
void				ft_child(t_tlist *lis, t_var *vars, int i,
						t_dlist **export);
char				*ft_add2(t_tlist *lis, t_var *v);
int					ft_replace2(t_tlist *lis, t_var *v);
int					ft_add(t_tlist *lis, t_var *vars);
int					ft_replace(char *command, int in, char *str);
void				ft_get_command_path(t_tlist *t);
void				free_all(t_var **vars, t_tlist **lis);
void				ft_free_innerloop(t_var *v, t_tlist **lis);
void				ft_vars_initiate(t_var *v, char **env, t_dlist **export);
int					ft_lis_and_token(t_var *v, t_dlist **l, t_tlist **lis);
void				ft_free_prompt1(char **p);
int					ft_do_echo(t_tlist *lis);
char				**ft_do_avg(t_tlist *lis, t_var *v);
char				**ft_do_avg2(t_tlist *lis, t_var *v);
void				ft_token_loop(char *s, int *q, unsigned int *i, int **m_q);
int					ft_search_for_slash(char *s);
void				free_stuff(char **avg);
void				ft_free_all(t_dlist *exp);
void				ft_free(t_var *v);
int					input_check_init(t_var *vars);
void				ft_free_prompt(t_var *v);
int					ft_check_inputline(char *str);
void				ft_free_child(t_var *vars, t_dlist **export);
void				ft_last_quote(char *s, int (*q)[3]);
void				ft_copy_int_array(int (*dest)[3], int src[3], int size);
int					ft_post_processor(t_tlist **p, t_var *v);
void				ft_del_node(t_tlist *l);
void				ft_initialize_truncate(int *i, unsigned int *q,
						unsigned int *j);
int					ft_askopen_qstatus(int q, int m_q[3], char s);
void				ft_change_q_status(unsigned int *q, int m_q[3], char s,
						int p);
void				ft_set_to_zero(unsigned int *i, unsigned int *q,
						unsigned int *j);
void				ft_execve(t_tlist *lis, t_var *vars);
int					ft_buildins2(t_tlist *lis, t_dlist **export);
int					ft_help_unset(t_dlist **expor, char *str, int i);
int					ft_input_helper(t_tlist **lis, t_var **vars,
						t_dlist **export, int i);
int					ft_add2_helper(t_tlist *lis, t_var *v, char **str,
						char *input);
char				*ft_replace_helper(int in, char *str);
int					special_case(t_tlist *lis, t_var *vars, t_dlist **export);
unsigned int		ft_get_qvar_size(char *s, unsigned int **j, unsigned int *i,
						t_var *v);
int					ft_heredoc_error(t_var *v, char **str);
char				*ft_strjoin_3(char *s1, char *s2, char *s3);
void				ft_free_and_exit(t_var *v, int exit_code);
char				*ft_init_name(char *s2, int *i, t_var *v);
char				**ft_make_argv(t_tlist *lis, t_var *v);
char				*ft_get_own_env(char *s, t_var *v);
int					ft_strccmp(char *s1, char *s2, char c);
int					ft_free_name_return_i(char **name);
void				ft_freetoken2(t_tlist *l);
char				*ft_get_envvarpos(char *s);
int					ft_check_command(char *str, int k, t_tlist *lis);
int					ft_is_variable(char *s);
#endif
