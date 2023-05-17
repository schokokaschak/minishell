/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akashets <akashets@42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 09:30:01 by akashets          #+#    #+#             */
/*   Updated: 2023/04/07 21:38:18 by akashets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include	<stdio.h>
# include	<stdlib.h>
# include	<string.h>
# include	<signal.h>
# include	<dirent.h>
# include	<fcntl.h>

# include	<readline/readline.h>
# include	<readline/history.h>

# include "libft/libft.h"

# define TEXT 0
# define SPACE 1
# define PIPE 2
# define INPUT 3
# define OUTPUT_OVER 4
# define HERE_DOC 5
# define OUTPUT_APPEND 6
# define DUP_QUOTES 7
# define SING_QUOTES 8
# define PRNTH_LEFT 10
# define PRNTH_RIGHT 11
# define LOGICAL_AND 12
# define LOGICAL_OR 13
# define SEPAR_MORE 14
# define SEPAR_LESS 15
# define SEPAR_PIPE 16
# define EXTENDED_TEXT 17
# define EXTENDED_QUOT 18
# define REDIRECTIONS 19
# define WILDCARD_REMOVE 20
# define OPENED 0
# define CLOSED 1

typedef struct dirent	t_dirent;

typedef struct s_string_list
{
	char					*str;
	struct s_string_list	*next;
	struct s_string_list	*prev;
}t_string_list;

typedef struct s_wildcard
{
	t_string_list	*comps;
	t_string_list	*iter;
	int				ending;
	int				starting;
}t_wildcard;

typedef struct s_token_list
{
	int					len;
	char				*token;
	int					type;
	struct s_token_list	*next;
	struct s_token_list	*prev;
}t_token_list;

typedef struct s_log_groups
{
	struct s_pipe_groups	*pipe_groups;
	t_token_list			*tokens;
	int						token_count;
	int						rec_depth;
	int						needed;
	struct s_log_groups		*next;
	struct s_log_groups		*prev;
}			t_log_groups;

typedef struct s_data
{
	char				*input;
	int					i;
	int					flag;
	int					flag_pid;
	int					last_log_ret;
	t_log_groups		*log_groups;
}				t_data;

typedef struct s_pipe_groups
{
	struct s_cmnd			*cmnd;
	t_token_list			*tokens;
	int						token_count;
	struct s_pipe_groups	*next;
	struct s_pipe_groups	*prev;

}	t_pipe_groups;

typedef struct s_cmnd
{
	char	*cmd;
	char	**argv;
	char	**cmd_paths;
	pid_t	pid;
	int		infile;
	int		outfile;
	int		here;
	int		cp;
	int		is_d;
	int		f_in;
	int		f_out;
}	t_cmnd;

typedef struct s_pipex {
	int		ncmd;
	int		pipe_n;
	int		*pipe;
	int		idd;
	char	*paths;
	char	*epath;
}		t_pipex;

char					**g_envp;

/* tokens */

t_token_list	*create_token(int type, char *start, int len);
t_token_list	*lexer(char *input);
t_token_list	*free_tokens(t_token_list	*tokens);

void			add_common_tok(int *type, char *cur, char **start, \
						t_token_list	**tokens);
void			check_for_token(int *type, char *cur, char **start, \
						t_token_list **tokens);
void			add_token(t_token_list **tokens, t_token_list *new_token);
void			free_token(t_token_list *token);

int				add_quot_tok(int *type, char *cur, char **start, \
						t_token_list	**tokens);
int				check_for_quot_token(int *type, char *cur, char **start, \
						t_token_list **tokens);
int				extend_token(t_token_list *token);
int				sub_extend_token(t_token_list *cur, char **seps, int *index);

/* lexer */

void			init_seps(char **separs);
void			init_index(int *index);
void			cancel_prnth_loc(int *l, int *o, int *p);
void			prnth_loc_if_state(t_token_list *t, int *on_prnth, \
					int *logical_char, int *valid_prnth);

int				lexical_errors(t_token_list *tokens);
int				check_group_pos(t_token_list *tokens);
int				is_redir(int type);
int				is_prnth(int type);
int				is_group(int type);
int				is_log_group(int type);
int				is_text(int type);
int				get_type(char c);

/* env */

char			**get_envp(char **envp);
char			**clone_envp(void);

int				output_env(char **envp);
int				get_env_size(char **envp);
int				find_variable(char **envp, char *var, int var_size);

/* parsing */

void			add_str_list(t_string_list	**strings, char	*str);
void			free_str_list(t_string_list	*strings);

char			**create_args(t_token_list **token, int k, char **argv, int y);
char			**create_args_2(char **argv, int k, int y);

t_data			*parse(t_token_list **tokens, int *last_exit, char *input);

t_log_groups	*create_log_group(t_token_list **token);

int				add_log_group(t_log_groups **exists, t_log_groups *new);
int				init_log_group(t_data *new, t_token_list **tokens, \
								t_token_list *cur, t_token_list *buf);
int				parse_extensions(t_token_list *tokens, int *last_exit);
int				set_recursion_depth(t_log_groups *log_group);
int				get_size_argv(char **argv, int y);
int				check_types(char *argv, int k);
/* signals */

void			signals(void);
void			sig_handle(int sig);
void			sig_handle_child(int sig);
void			child_sig(void);

/* create pipe groups */

int				init_pipe_group(t_data *new);
int				add_pipe_group(t_pipe_groups **exists, t_pipe_groups *new);
t_pipe_groups	*create_pipe_group(t_token_list **token);

/* create command */

char			*get_command(char *str, char ok);
char			*get_command_sp(char *str, char ok);
char			*get_command_fd(char *str);
char			*parse_str(t_token_list **tokens);
t_cmnd			*create_cmnd(t_token_list **token, int k, int *d, int y);
int				init_commands(t_data *new, int *last_exit);
int				ft_argv_cmp(char *argv);
int				is_arg_type(int type);
int				get_arg_size(t_token_list **token, int k);
int				arg_checker(int type);
int				check_jump(char *argv, int *y, int *i);
int				check_input_so(char *input);

/* open fd*/

void			check_fd(t_cmnd *command, char **argv, int *d);
void			here_doc(char *limit, int fd);
void			heredoc_sig_handle(int sig);
void			heredoc_sig(void);

/* builtins*/

int				get_builtins(char *command);
int				exec_builtins(char *command, char **args, t_data *d);
int				builtin_echo(char **argv);
int				builtin_pwd(void);
int				builtin_exit(char **argv, t_data *data);
int				builtin_cd(char	**argv);
char			**delete_variable(int index);
int				builtin_unset(char **argv);
char			**add_variable(char *var, int index);
int				builtin_export(char **argv);
int				check_var_name(char *var);

/* execution */

void			*execution(t_data *data, t_log_groups *log_group, int cl);
void			ft_close(t_pipex *pipex);
int				execute_pipes(t_pipe_groups **pipe_groups, t_data *d);
int				create_pipes(t_pipex *pipex);
void			start_the_show(t_cmnd *c, t_pipex p, t_data *d, \
									t_pipe_groups *t);
char			*ft_get_cmd(char **paths, char *cmd);
void			sub_dup2(int zero, int first);
char			*find_path(char **envp, t_pipex *pipex);
void			redir_pipes(t_cmnd *c, t_pipex *p);

void			parent_process(t_data *data, t_cmnd *c, t_pipe_groups *t);
void			child_process(t_cmnd *c, t_pipex *p, t_pipe_groups *t, \
												t_data *data);

/* wildcards */

int				extend_wildcards(t_token_list *tokens);
void			init_wildcard_vars(int *i, int *j, \
				int *wild, t_string_list **cur_wild);
int				check_token_ends(int *i, int *wild, \
				char *last_wild, t_token_list **cur);
void			add_wild_comp(int *j, int *wild, t_string_list **cur_wild);
void			check_start_end(t_token_list *token, t_wildcard *wildcard);

/* free in loop */

void			free_data_in_loop(t_data *data, char *input);
void			free_pipe_in_loop(t_pipe_groups *pipes);
void			free_cmnd_in_loop(t_cmnd *command);
void			free_argv(char **argv);
int				ctrl_d_exit(void);
int				free_input(char *input);

#endif
