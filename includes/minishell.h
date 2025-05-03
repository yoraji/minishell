#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//
#include <errno.h>
//

#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/stat.h>
#include <readline/readline.h>
#include <readline/history.h>

//
typedef enum {
    NODE_COMMAND,
    NODE_PIPE,
    NODE_DOUBLE_AND,
    NODE_REDIRECTION
} NodeType;

typedef struct ASTNode {
    NodeType type;
    char **args; // For command arguments
    char *filename; // For redirection
    struct ASTNode *left;
    struct ASTNode *right;
} ASTNode;

//
typedef struct s_pipe
{
    int fd[2];
} t_pipe;

typedef struct s_redir
{
    char *file;
    int type; // 0 for input, 1 for output
} t_redir;


typedef struct s_data
{
    char **tab;
    char **envp;
    // int exit_status;
    char *cmds;
    int cmd_count;
    t_pipe *pipes;
    int pipe_count;
    t_redir *redirs;
    int redir_count_left;
    int redir_count_right;
    int double_redir_count_left;
    int double_redir_count_right;
    // int heredoc_count;
    // int hdoc_count;
    char **hdocs;
} t_data;

/* libft function */

char	**ft_split(char const *s, char c);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char const *s1, char const *s2);
int     ft_strlen(const char *s);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_calloc(size_t count, size_t size);
int	    ft_atoi(const char *ptr);
char	*ft_strdup(const char *s);
int     ft_isspace(int c);
int     ft_strcmp(char *s1, char *s2);


/* signal handling */
void setup_signals(void);

// void sigint_handler(int signum);
// void sigquit_handler(int signum);

void sigint_handler(int signum);
void sigquit_handler(int signum);

void sig_handler(int signum);

/* build-in function */
int builtin_cd(ASTNode *node);
int builtin_echo(char **args);
int builtin_pwd(void);
int is_directory(char *path);
int execute_builtin(t_data *data);


// int builtin_env(char **envp);
// int builtin_export(char **args, char **envp);
// int builtin_unset(char **args, char **envp);
// int builtin_exit(char **args);
// int is_builtin(char *cmd);
int detect_cmd(char **tab);

/* enviroment */
int is_expand_env(char **input);

int builtin_env(char **envp);
int builtin_export(char **args, char **envp);
int builtin_unset(char **args, char **envp);
int builtin_exit(char **args);
int is_builtin(char *cmd);
int detect_cmd(char **tab);

/* Constrating_AST.c */

ASTNode *build_node(char **tokens);
void print_ast(ASTNode *node, int depth);

/* parsing_engine */
int     unclosed_quotes(char **tab);
char    *extract_token(char *input, int *i);
char    **tokens(char *input);
int     not_encarder(char **tab);
int     brain(char **tab);
int     count_quotes(char *argv);
void    detect_sepical_token(char **tab, t_data *data);
int     ft_scan(char **tab);
int     handling_input(char *argv, t_data *data);
char    **scan_token(char **tab);

/* free */
void   free_data(t_data *data);
void free_tab(char **tab);

/* execution */
int is_expand_env(char **input);
char **expand_env(char **input, char **envp);



/* syntax error */
int detect_cmd_v1(char **tab);
int invalid_pipe_position(char **tab);
int parsing(t_data *data);

/* print token */
void    print_tokens(char **tokens);


// Unclosed parentheses : (, ), {, }, [, ]
// Dangling operators : &&, ||, ;, &, |
// Redirect without target: cat <, ls >
// Invalid redirection: ls > <, ls < >