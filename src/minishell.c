#include "../includes/minishell.h"


int    get_input(t_data *data)
{
    // Function to get input from the user
    // This function should handle reading input and storing it in data->cmds
    return -1;
}

int    parse_input(t_data *data)
{
    // Function to parse the input commands
    // This function should handle parsing the input and storing it in data->cmds
    return -1;
}
void   execute_commands(t_data *data)
{
    // Function to execute the parsed commands
    // This function should handle executing the commands stored in data->cmds
    return ;
}


void   free_data(t_data *data)
{
    // Function to free allocated memory in data
    if (data->envp)
        free(data->envp);
    if (data->cmds)
        free(data->cmds);
    if (data->pipes)
        free(data->pipes);
    if (data->redirs)
        free(data->redirs);
    if (data->hdocs)
        free(data->hdocs);
}


void sig_handler(int signum)
{
    if (signum == SIGINT)
    {
        write(1, "\n", 1);
        // Handle SIGINT signal
    }
    else if (signum == SIGQUIT)
    {
        write(1, "Quit: 3\n", 8);
        // Handle SIGQUIT signal
    }
}


void free_tab(char **tab)
{
    int i;

    if (!tab) 
        return;
    i = 0;
    while (tab[i])
    {
        free(tab[i]);
        tab[i] = NULL; // Set to NULL to avoid double free
        i++;
    }
    free(tab);
    tab = NULL; // Set the pointer to NULL after freeing
}

void detect_sepical_token(char **tab, t_data *data)
{
    // Function to detect special tokens (pipes, redirections, etc.)
    // This function should handle detecting special tokens in the input
    int i = 0;
    while (tab[i])
    {
        if (strcmp(tab[i], "|") == 0)
            data->pipe_count++;
        else if (strcmp(tab[i], ">") == 0)
            data->redir_count_right++;    
        else if (strcmp(tab[i], "<") == 0)
            data->redir_count_left++;
        else if (strcmp(tab[i], ">>") == 0)
            data->double_redir_count_right++;
        else if (strcmp(tab[i], "<<") == 0)
            data->double_redir_count_left++;      
        i++;
    }
}

int unclosed_quotes(char **tab)
{
    int i;
    int j ;
    char quote;

    i = 0;
    while (tab[i])
    {
        j = 0;
        quote = 0;
        while (tab[i][j])
        {
            if ((tab[i][j] == '\'' || tab[i][j] == '"'))
            {
                if (quote == 0)
                    quote = tab[i][j];
                else if (quote == tab[i][j])
                    quote = 0;
            }
            j++;
        }
        if (quote != 0)
        {
            printf("Error: Unmatched %c quote in token: %s\n", quote, tab[i]);
            return 1;
        }

        i++;
    }
    return 0;
}

int ft_isspace(int c)
{
    return (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f' || c == '\v');
}

//  char *extract_token(char *input, int *i)
// {
//     int start = *i;
//     char quote = 0;
//     int len = 0;

//     // // Skip initial whitespace
//     while (input[*i] && ft_isspace(input[*i]))
//         (*i)++;
//     start = *i;

//     // Handle quotes
//     if (input[*i] == '\'' || input[*i] == '"')
//     {
//         quote = input[(*i)++];
//         // start++;
//         while (input[*i] && (input[*i] != quote))
//         {
//             (*i)++;
//             len++;
//         }
//         len +=  2;  // ?? !!
//         (*i)++; // Skip closing quote
//     }
//     else
//     {
//         while (input[*i] && !isspace(input[*i]))
//         {
//             (*i)++;
//             len++;
//         }
//     }

//     char *token = malloc(len + 1);
//     if (!token)
//         return NULL;
//     strncpy(token, input + start, len); // ???
//     token[len] = '\0';
//     return token;
// }

// problem of escape char you have to handle it
char *extract_token(char *input, int *i)
{
    char *result = calloc(1, sizeof(char)); // ??
    if (!result)
        return NULL;

    while (input[*i] && ft_isspace(input[*i])) // Skip whitespace
        (*i)++;

    while (input[*i] && !ft_isspace(input[*i]))
    {
        char quote = 0;

        // Handle quotes
        if (input[*i] == '\'' || input[*i] == '"')
        {
            quote = input[(*i)++];
            int qstart = *i;
            while (input[*i] && input[*i] != quote) // Skip until closing quote
                (*i)++;
            int len = *i - qstart;
            char *seg = strndup(input + qstart, len);
            if (!seg)
            {
                free(result);
                return NULL;
            }
            char *tmp = ft_strjoin(result, seg);
            free(result);
            result = tmp;
            free(seg);
            if (input[*i] == quote)
                (*i)++;
        }
        // Handle escape characters
        else if (input[*i] == '\\')
        {
            (*i)++; // Skip the backslash
            if (input[*i]) // Ensure there is a character after the backslash
            {
                char escaped[2] = {input[*i], '\0'};
                char *tmp = ft_strjoin(result, escaped);
                free(result);
                result = tmp;
                (*i)++;
            }
        }
        else
        {
            // Handle regular characters
            int wstart = *i;
            while (input[*i] && !ft_isspace(input[*i]) && input[*i] != '\'' && input[*i] != '"' && input[*i] != '\\')
                (*i)++;
            int len = *i - wstart;
            char *segment = strndup(input + wstart, len);
            if (!segment)
            {
                free(result);
                return NULL;
            }

            char *tmp = ft_strjoin(result, segment);
            free(result);
            result = tmp;
            free(segment);
        }
    }
    return result;
}

int detect_cmd_v1(char **tab)
{
    int i;
    
    i = 1;
    while(tab[i])
    {
        if (strcmp(tab[i], "cd") == 0)
            return (1);
        else if (strcmp(tab[i], "echo") == 0)
            return (1);
        else if (strcmp(tab[i], "export") == 0)
            return (1);
        else if (strcmp(tab[i], "unset") == 0)
            return (1);
        else if (strcmp(tab[i], "env") == 0)
            return (1);
        else if (strcmp(tab[i], "exit") == 0)
            return (1);
        else if (strcmp(tab[i], "ls") == 0)
            return (1);
        i++;
    }
    return (0);
}

int detect_cmd(char **tab)
{
    int i = 0;
    if(tab)
    {
        // ft_strcmp ??
        if (strcmp(tab[i], "cd") == 0)
            return (1);
        else if (strcmp(tab[i], "echo") == 0)
            return (1);
        else if (strcmp(tab[i], "export") == 0)
            return (1);
        else if (strcmp(tab[i], "unset") == 0)
            return (1);
        else if (strcmp(tab[i], "env") == 0)
            return (1);
        else if (strcmp(tab[i], "ls") == 0)
            return (1);
        else if (strcmp(tab[i], "cat") == 0)
            return (1);
        i++;
    }
    return (0);
}
void print_tokens(char **tokens)
{
    int i = 0;
    while (tokens[i])
    {
        printf("Token: [%s]\n", tokens[i]);
        i++;
    }
}

char **tokens(char *input)
{
    char **tokens = malloc(sizeof(char *) * 128);
    if (!tokens) return NULL;
    int count = 0;
    int i = 0, t = 0;
    while (input[i])
    {
        while (input[i] && isspace(input[i]))
            i++;
        if (!input[i])
            break;
        char *token = extract_token(input, &i);
        if (!token)
            return NULL;
        tokens[t++] = token;
    }
    tokens[t] = NULL;
    return tokens;
}

int invalid_pipe_position(char **tab)
{
    int i;

    i = 0;
    if (!tab[0])
        return (1);
    while (tab[i])
    {
        if (strcmp(tab[i], "|") == 0)
        {
            if (i == 0 || tab[i + 1] == NULL || strcmp(tab[i + 1], "|") == 0)
            {
                printf("Syntax error near unexpected token `|'\n");
                return (1);
            }
        }
        i++;
    }
    return (0);
}
// Unclosed parentheses 
// Dangling operators
// Redirect without target: cat <, ls >
// Invalid redirection: ls > <, ls < >
// 
int  brain(char **tab)
{
    int i;
    int j=0;

    if (detect_cmd(tab) == 0 || invalid_pipe_position(tab))
    {
        printf("Error: Command not found: %s\n", tab[0]);
        return (1);
    }
    i = 1;
    while (tab[i])  
    {
        if(detect_cmd_v1(tab) == 1)
        {
            printf("Error: Command not found: %s\n", tab[i]);
            return (1);
        }
        i++;
    }
    return 0;
}

int count_quotes(char *argv)
{
    int i = 0;
    int count = 0;

    while (argv[i])
    {
        if (argv[i] == '\'' || argv[i] == '"')
            count++;
        i++;
    }
    return count;
}
int ft_scan(char **tab)
{
    int i = 0;
    int j = 0;
    int count = 0;

    while (tab[i])
    {
        j = 0;
        while (tab[i][j])
        {
            // ??
            if (isalnum(tab[i][j + 1]) && isalnum(tab[i][j - 1]) && (tab[i][j] == '|' || tab[i][j] == '<' || tab[i][j] == '>'))
                return 1;
            j++;
        }
        i++;
    }
    return 0; // Return 1 if odd, indicating an error
}

char **scan_token(char **tab)
{
    int i = 0;
    char **new_tab = malloc(sizeof(char *) * 256); // increase if needed
    if (!new_tab)
        return NULL;

    int new_tab_index = 0;

    while (tab[i])
    {
        int j = 0;
        while (tab[i][j])
        {
            // Skip whitespace
            if (tab[i][j] == ' ')
            {
                j++;
                continue;
            }

            // Handle special characters: |, <, >, <<, >>
            if (tab[i][j] == '|' || tab[i][j] == '<' || tab[i][j] == '>')
            {
                int len = 1;
                if ((tab[i][j] == '<' || tab[i][j] == '>') && tab[i][j + 1] == tab[i][j])
                    len = 2;

                char *special = strndup(&tab[i][j], len);
                new_tab[new_tab_index++] = special;
                j += len;
            }
            else
            {
                // Extract non-special word/token
                int start = j;
                while (tab[i][j] && tab[i][j] != ' ' &&
                       tab[i][j] != '|' && tab[i][j] != '<' && tab[i][j] != '>')
                {
                    // handle >> and << safely
                    if ((tab[i][j] == '<' || tab[i][j] == '>') && tab[i][j + 1] == tab[i][j])
                        break;
                    j++;
                }
                char *word = strndup(&tab[i][start], j - start);
                new_tab[new_tab_index++] = word;
            }
        }
        i++;
    }

    new_tab[new_tab_index] = NULL;
    return new_tab;
}

int handling_input(char *argv, t_data *data)
{
    int i = 0;
    if (argv == NULL || argv[0] == '\0')
    {
        printf("Error: No input provided\n");
        return (1);
    }
    // you must handle Tokenization it
    int count = count_quotes(argv);
    if (count % 2 != 0)
    {
        printf("Error: Unmatched quotes\n");
        return (1);
    }
    char **tab = tokens(argv);
    if (tab == NULL) // protection against memory allocation failure
    {
        perror("Memory allocation failed");
        return (1);
    }
    if (ft_scan(tab) == 1)
    {
        tab = scan_token(tab); // protections ??
        return (1);
    }
    // print_tokens(tab);
    detect_sepical_token(tab, data);
    // here add the functions to check the token
    if (unclosed_quotes(tab) || brain(tab))
    {
        free_tab(tab); // Use free_tab to free memory
        return (1);
    }
    
    // Future: check redirections, build cmd structs here...

    while (tab[i])
    {
        printf("Token: [%s]\n", tab[i]);
        i++;
    }
    free_tab(tab); // Free the tokenized array
    return (0);
}
//  ""''
int main(int argc, char **argv, char **envp)
{
    t_data data;

    if (argc < 1 || envp == NULL)
    {
        fprintf(stderr, "Usage: %s\n", argv[0]);
        return (1);
    }

    data = (t_data){0};
    data.envp = envp; // Initialize environment variables

    // Set up signal handlers
    // signal(SIGINT, sig_handler);  // Handle SIGINT signal (Ctrl+C)
    // signal(SIGQUIT, sig_handler); // Handle SIGQUIT signal (Ctrl+\)

    while (1)
    {
        char *input = readline("minishell> "); // Read user input
        if (!input || handling_input(input, &data) == 1) // Check for EOF (Ctrl+D)
        {
            return (0); // Exit if EOF is detected
            break;
        }
        if (*input) // Add non-empty input to history
            add_history(input);
        data.cmds = ft_strdup(input); // Store the input in data->cmds
        free(input); // Free the input string after storing it

        if (get_input(&data) == -1) // Process the input
            continue; // Skip to the next iteration if input processing fails
        if (parse_input(&data) == -1) // Parse the input
            continue; // Skip to the next iteration if parsing fails
        // execute_commands(&data); // Execute the parsed commands
        // free(data.cmds);
        // free(input);
    }

    free_data(&data); // Free allocated memory in data before exiting
    return (0);
}