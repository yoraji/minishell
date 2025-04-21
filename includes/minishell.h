#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

//
#include <readline/readline.h>
#include <readline/history.h>
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
    char **envp;
    int exit_status;
    char *cmds;
    int cmd_count;
    t_pipe *pipes;
    int pipe_count;
    t_redir *redirs;
    int redir_count_left;
    int redir_count_right;
    int double_redir_count_left;
    int double_redir_count_right;
    int heredoc_count;
    int hdoc_count;
    char **hdocs;
} t_data;

// * utils functions *
// function ft_strlen - ft_strjoin - ft_atoi
//function ft_split - ft_strchr - ft_memcpy

int	ft_atoi(const char *ptr);
char	*ft_strdup(const char *s);
char	**Tokenization_handling( char *argv, char del);
void sig_handler(int signum);
void init_data(t_data *data);
void free_data(t_data *data);
char	**ft_split(char const *s, char c);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *s);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_calloc(size_t count, size_t size);

