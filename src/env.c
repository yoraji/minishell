/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoraji <yoraji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 04:55:50 by yoraji            #+#    #+#             */
/*   Updated: 2025/04/24 05:08:35 by yoraji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// 1.Loop through the string.
// 2.When you see $, read the variable name after it.
// 3.Look it up using getenv().
// 4.Replace $VAR with its value.

/*
    $? → last exit status.
    $$ → process ID (optional in minishell).
    $VAR where VAR isn’t defined → empty string.
    '$VAR' → should NOT expand (single quotes prevent expansion).
    "${VAR}" → optional support for braces.

*/
int is_expand_env(char **input)
{
    int i = 0;
    int j = 0;
    while(input[i])
    {
        j = 0;
        while(input[i][j])
        {
            if (input[i][j] == '$')
                return (1);
            j++;
        }
        i++;
    }
    return(0);
}

//
char **expand_env(char **input, char **envp)
{
    int i = 0;
    char **expanded = malloc(sizeof(char *) * 256); // Allocate memory for the expanded tokens
    if (!expanded)
        return NULL;

    int expanded_index = 0;
    while (input[i])
    {
        char *token = input[i];
        char *new_token = calloc(1, sizeof(char)); // Allocate memory for the expanded token
        if (!new_token)
        {
            free_tab(expanded);
            return NULL;
        }

        int j = 0;
        while (token[j])
        {
            if (token[j] == '$' && token[j + 1] && token[j + 1] != ' ')
            {
                j++; // Skip the '$'
                int start = j;
                while (token[j] && (isalnum(token[j]) || token[j] == '_'))
                    j++; // Read the variable name

                char *var_name = strndup(&token[start], j - start);
                if (!var_name)
                {
                    free(new_token);
                    free_tab(expanded);
                    return NULL;
                }

                char *var_value = getenv(var_name); // Get the value of the environment variable
                free(var_name);

                if (var_value)
                {
                    char *tmp = ft_strjoin(new_token, var_value);
                    free(new_token);
                    new_token = tmp;
                }
            }
            else
            {
                char *tmp = ft_strjoin(new_token, (char[]){token[j], '\0'});
                free(new_token);
                new_token = tmp;
                j++;
            }
        }

        expanded[expanded_index++] = new_token;
        i++;
    }

    expanded[expanded_index] = NULL;

    free_tab(input); // Free the original input tokens
    return expanded;
}
