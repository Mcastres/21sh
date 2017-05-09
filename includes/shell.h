/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmadad <hmadad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 14:43:05 by hmadad            #+#    #+#             */
/*   Updated: 2017/04/27 14:56:14 by mcastres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include <../libft/libft.h>
# include <errno.h>
# include <sys/wait.h>
# include <signal.h>
# include <termcap.h>
# include <term.h>
# include <stdio.h>

# define RED   "\x1B[31m"
# define GRN   "\x1B[32m"
# define YEL   "\x1B[33m"
# define BLU   "\x1B[34m"
# define MAG   "\x1B[35m"
# define CYN   "\x1B[36m"
# define WHT   "\x1B[37m"
# define RESET "\x1B[0m"

# define STDIN 0
# define STDOUT 1
# define STDERR 2

typedef struct	s_shell
{
	int					s_h;
	int					position;
	int					pos_max;
	char				*line;
	char				**path;
	char				**all;
	char				**opt;
	char				**env;
	struct s_history	*history;
	struct termios		default_term;
}				t_shell;

typedef struct		s_history
{
	char				*content;
	struct s_history	*previous;
	struct s_history	*next;

}					t_history;

void			ft_process(t_shell **shell);
int				is_redirection(char **commands);
int				do_redirection(char **commands, t_shell **shell);
void 			ft_doquote(t_shell **shell);
void 			ft_dodquote(t_shell **shell);
int 			ft_dquote(char *str);
int 			ft_quote(char *str);
int				is_pipe(char **commands, t_shell **shell);
int				ft_21sh(char ***env);
t_history		*ft_init_term(t_shell **shell);
void			ft_read_commande(t_shell **shell);
void			ft_history_key(t_shell **shell, char *buf);
char			*ft_ltos(t_list **commande);
void			ft_reset_position(t_shell **shell);
t_history		*ft_listenew(char *content);
void			ft_liste_push_back(t_history **lst, t_history *new);
void			ft_liste_push_front(t_history **lst, t_history *new);
int				ft_putc(int c);
char			*ft_getenv(char **env, char *search);
int				ft_setenv(char ***env, char *str);
int				ft_unsetenv(char ***env, char *str);
char			*get_pwd();
void			ft_prompt(char **env);
char			*ft_find_last_pwd(char *pwd);
char			**ft_realloc(char ***ta, char *str);
char			**ft_unalloc(char ***ta, char *str);
void			ft_delete_char(t_shell **shell, char *buf);
void			ft_print_char(t_shell **shell, char *buf);
char			*ft_strtrimb(char *str);
void			ft_exec_commande(t_shell **shell);
char			*ft_change_home_sign(char *line, char *home, char c);
void			ft_exit(t_shell **shell);
void			ft_check_commande(t_shell **shell, char *commande);
void			ft_echo(char **opt, char ***env);
void			ft_prepare_unsetenv(char ***env, char **opt);
void			ft_prepare_setenv(char ***env, char **opt);
int				ft_prepare_cd(char **opt, char ***env);
int				ft_cd(char **opt, char ***env, char c);
void			ft_cd_errors(char *newpath, char **home);
int				ft_cd_home(char ***env, char **home);
int				ft_verif_home(char **opt, char **home, char ***env);
int				ft_home_process(char **home, char *split);
char			*ft_cdsplit(char *split, char *home);

#endif
