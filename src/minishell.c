/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youssef <youssef@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 06:42:15 by yoraji            #+#    #+#             */
/*   Updated: 2025/05/08 11:41:36 by youssef          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */

#include "../includes/minishell.h"


int    get_input(t_data *data)
{
    // Function to get input from the user
    // This function should handle reading input and storing it in data->cmds
    return -1;
}


// problem of escape char you have to handle it
//  1. Tokenization
//  2. Syntax Checking
//  6. Command Splitting and Structuring  ((Convert tokens into an executable structure (usually a tree or list of structs))
//  7. build-in detection
//  8. Execution Engine
//  9. Signal Handling
//  10. Exit Status Tracking


// char envp
int main(int argc, char **argv, char **envp)
{
    t_data data; // allocation in the stack

    if (argc < 1 || envp == NULL)
    {
        fprintf(stderr, "Usage: %s\n", argv[0]);
        return (1);
    }
    (void)argv;
    (void)argc;

    data = (t_data){0};
    data.envp = envp; // Initialize environment variables
    int flag = 0;

    while (1)
    {
        char *input = readline("minishell> "); // Read user input
        if (!input) // Check for EOF (Ctrl+D)
            return (0); // Exit if EOF is detected
        if (*input && handling_input(input, &data) == 1) // Add non-empty input to history
            printf("Error: No input provided\n");
        if (parsing(&data) == 1)
        {
            printf("Error: Parsing failed\n");
            free(input); // Free the input string if parsing fails
            flag = 1;
            continue; // Skip to the next iteration
        }
        ASTNode *root = build_node(data.tab); // Build the node structure
        print_ast(root, 0); // Print the AST
        if (execute_builtin(root, &data) == -1)
        {
            printf("Error: Command execution failed\n");
        }
        if (flag == 1 && is_builtin(data.tab[0]) == 1)
            execute_builtin(root, &data); // Pass the ASTNode and t_data
        add_history(input);
        free(input); // Free the input string after storing it
        if (get_input(&data) == -1) // Process the input
            continue; // Skip to the next iteration if input processing fails
    }

    free_data(&data); // Free allocated memory in data before exiting
    return (0);
}
