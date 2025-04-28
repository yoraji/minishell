/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_engine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoraji <yoraji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 09:10:28 by yoraji            #+#    #+#             */
/*   Updated: 2025/04/27 06:45:25 by yoraji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"


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

// OLD VERSION THAT HAVE PROBLEM IN SPACES
// char *extract_token(char *input, int *i)
// {
//     char *result = calloc(1, sizeof(char)); // ??
//     if (!result)
//         return NULL;
//     while (input[*i] && ft_isspace(input[*i])) // Skip whitespace
//         (*i)++;

//     while (input[*i] && !ft_isspace(input[*i])) // ??
//     {
//         char quote = 0;

//         // Handle quotes
//         if (input[*i] == '\'' || input[*i] == '"')
//         {
//             quote = input[(*i)];
//             (*i)++; // ??
//             (*i)++; // ??
//             int qstart = *i;
//             while (input[*i] && input[*i] != quote) // Skip until closing quote
//                 (*i)++;
//             int len = *i - qstart + 1; // Include closing quote
//             char *seg = strndup(input + qstart, len);
//             if (!seg)
//             {
//                 free(result);
//                 return NULL;
//             }
//             char *tmp = ft_strjoin(result, seg);
//             free(result);
//             result = tmp;
//             free(seg);
//             if (input[*i] == quote)
//                 (*i)++;
//         }
//         // Handle escape characters
//         else if (input[*i] == '\\')
//         {
//             (*i)++; // Skip the backslash
//             if (input[*i]) // Ensure there is a character after the backslash
//             {
//                 char escaped[2] = {input[*i], '\0'};
//                 char *tmp = ft_strjoin(result, escaped);
//                 free(result);
//                 result = tmp;
//                 (*i)++;
//             }
//         }
//         else
//         {
//             // Handle regular characters
//             int wstart = *i;
//             while (input[*i] && !ft_isspace(input[*i]) && input[*i] != '\'' && input[*i] != '"' && input[*i] != '\\')
//                 (*i)++;
//             int len = *i - wstart;
//             char *segment = strndup(input + wstart, len);
//             if (!segment)
//             {
//                 free(result);
//                 return NULL;
//             }

//             char *tmp = ft_strjoin(result, segment);
//             free(result);
//             result = tmp;
//             free(segment);
//         }
//     }
//     return result;
// }


// sugestion
char *extract_token(char *input, int *i)
{
    char *result = calloc(1, sizeof(char));
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
            quote = input[*i];
            char *tmp = ft_strjoin(result, (char[]){quote, '\0'}); // Include the opening quote
            free(result);
            result = tmp;
            (*i)++;
            while (input[*i] && input[*i] != quote)
            {
                if (input[*i] == '\\') // Handle escaped quotes
                    (*i)++;
                tmp = ft_strjoin(result, (char[]){input[*i], '\0'});
                free(result);
                result = tmp;
                (*i)++;
            }
            if (input[*i] == quote)
            {
                tmp = ft_strjoin(result, (char[]){quote, '\0'});
                free(result);
                result = tmp;
                (*i)++;
            }
            else
            {
                printf("Error: Unmatched %c quote in token: %s\n", quote, result);
                free(result);
                return NULL;
            }
        }
        // Handle escape characters
        else if (input[*i] == '\\')
        {
            (*i)++;
            if (input[*i]) // Ensure there is a character after the backslash
            {
                char *tmp = ft_strjoin(result, (char[]){input[*i], '\0'});
                free(result);
                result = tmp;
                (*i)++;
            }
        }
        else if (input[*i] == '|' || input[*i] == '<' || input[*i] == '>')
        {

            char *tmp = ft_strjoin(result, (char[]){input[*i], '\0'});
            free(result);
            result = tmp;
            (*i)++;
            return result;
        }
        else
        {
            // Handle other characters
            char *tmp = ft_strjoin(result, (char[]){input[*i], '\0'});
            free(result);
            result = tmp;
            (*i)++;
        }
    }
    return result;
}


char **tokens(char *input)
{
    char **tokens = malloc(sizeof(char *) * 128);
    if (!tokens) return NULL;
    int count = 0;
    int i = 0, t = 0;
    while (input[i])
    {
        while (input[i] && ft_isspace(input[i]))
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

int not_encarder(char **tab)
{
    int i = 0;
    while (tab[i])
    {
        int last = ft_strlen(tab[i]) - 1;
        if ((tab[i][0] == '\'' || tab[i][0] == '"') && (tab[i][last] == '\'' || tab[i][last] == '"'))
        {
            if (ft_scan(tab))
                return 1;
        }
        i++;
    }
    return 0;
}

int brain(char **tab)
{
    int i = 0;

    // Check if the first token is a valid command
    if (detect_cmd(tab) == 0 || invalid_pipe_position(tab))
    {
        printf("Error: Command not found: %s\n", tab[0]);
        return (1);
    }
    // Validate subsequent tokens
    while (tab[i])
    {
        // Skip logical operators
        if (ft_strcmp(tab[i], "&&") == 0 || ft_strcmp(tab[i], "||") == 0)
        {
            i++;
            // Ensure the next token is a valid command
            if (tab[i] && detect_cmd(&tab[i]) == 0)
            {
                printf("Error: Command not found: %s\n", tab[i]);
                return (1);
            }
            continue;
        }
        // Skip arguments (not commands)
        if (i > 0 && ft_strcmp(tab[i - 1], "&&") != 0 && ft_strcmp(tab[i - 1], "||") != 0)
        {
            i++;
            continue;
        }
        // Check if the token is a valid command
        // if (detect_cmd_v1(&tab[i]) == 0)
        // {
        //     printf("Error: Command not found: %s\n", tab[i]);
        //     return (1);
        // }
        i++;
    }
    return (0);
}

void detect_sepical_token(char **tab, t_data *data)
{
    // Function to detect special tokens (pipes, redirections, etc.)
    // This function should handle detecting special tokens in the input
    int i = 0;
    while (tab[i])
    {
        if (ft_strcmp(tab[i], "|") == 0) // ??
            data->pipe_count++;
        else if (ft_strcmp(tab[i], ">") == 0)
            data->redir_count_right++;
        else if (ft_strcmp(tab[i], "<") == 0)
            data->redir_count_left++;
        else if (ft_strcmp(tab[i], ">>") == 0)
            data->double_redir_count_right++;
        else if (ft_strcmp(tab[i], "<<") == 0)
            data->double_redir_count_left++;
        i++;
    }
}

int ft_scan(char **tab)
{
    int i = 0;
    int j = 0;

    while (tab[i])
    {
        j = 0;
        char quote = 0;

        // Handle tokens with quotes
        while (tab[i][j])
        {
            if (tab[i][j] == '\'' || tab[i][j] == '"')
            {
                if (quote == 0) // Start of a quoted section
                    quote = tab[i][j];
                else if (quote == tab[i][j]) // End of the quoted section
                    quote = 0;
            }
            else if (quote == 0 && (tab[i][j] == '|' || tab[i][j] == '<' || tab[i][j] == '>'))
            {
                // Check if special characters are improperly placed
                if (isalnum(tab[i][j + 1]) && isalnum(tab[i][j - 1]))
                    return 1;
            }
            j++;
        }

        // If the token ends with an unclosed quote, return an error
        if (quote != 0)
        {
            printf("Error: Unmatched %c quote in token: %s\n", quote, tab[i]);
            return 1;
        }

        i++;
    }
    return 0; // Return 0 if no errors are found
}


//  3. Quote Removal
//  4. Environment Variable Expansion
//  5. handling the herdoc "<<"

int handling_input(char *argv, t_data *data)
{
    int i = 0;
    if (argv == NULL || argv[0] == '\0')
    {
        printf("Error: No input provided\n");
        return (1);
    }
    char **tab = tokens(argv);
    if (tab == NULL) // protection against memory allocation failure
    {
        perror("Memory allocation failed"); // ??
        return (1);
    }
    // print_tokens(tab);
    // // printf("after tokens\n");
    // return 0;
    // if (is_expand_env(tab) == 1)
    //     tab = expand_env(tab, data->envp);
    // if (ft_scan(tab) == 1)
    // {
    //     tab = scan_token(tab); // protections ??
    //     if (tab == NULL) // protection against memory allocation failure
    //     {
    //         perror("Memory allocation failed");
    //         return (1);
    //     }

    //  }
     // printf("after tokens\n");
    // return 0;
    // printf("after scan_token\n");
    // print_tokens(tab);
    detect_sepical_token(tab, data);
    // here add the functions to check the token
    // if (unclosed_quotes(tab) || brain(tab))
    // {
    //     free_tab(tab); // Use free_tab to free memory
    //     return (1);
    // }
    // Future: check redirections, build cmd structs here...
    // free_tab(tab); // Free the tokenized array

    // Future: check redirections, build cmd structs here...

    while (tab[i])
    {
        printf("Token: [%s]\n", tab[i]);
        i++;
    }

    data->tab = tab; // Store the tokenized array in data
    // free_tab(tab); // Free the tokenized array
    return (0);
}


char **scan_token(char **tab)
{
    int i = 0;
    char **new_tab = malloc(sizeof(char *) * 256);
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

                char *special = strndup(&tab[i][j], len); // ??
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
                char *word = strndup(&tab[i][start], j - start); // ??
                new_tab[new_tab_index++] = word;
            }
        }
        i++;
    }
    new_tab[new_tab_index] = NULL;
    return new_tab;

}
