/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youssef <youssef@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 05:21:09 by yoraji            #+#    #+#             */
/*   Updated: 2025/05/05 09:00:41 by youssef          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"


int check_sepicail_operators(char *tab)
{
    int i = 0;
    if(!tab)
    {
        printf("Error: Invalid input (tab is NULL)\n");
        return (1);
    }
    if(ft_strcmp(tab, "|") == 0 || ft_strcmp(tab, "<") == 0 || ft_strcmp(tab, ">") == 0 ||
       ft_strcmp(tab, "<<") == 0 || ft_strcmp(tab, ">>") == 0)
    {
        printf("Syntax error near unexpected token `%s'\n", tab);
        return (1);
    }
    return (0);
}

int invalid_pipe_position(char **tab)
{
    int i;

    // Check if tab is NULL
    if (!tab)
    {
        printf("Error: Invalid input (tab is NULL)\n");
        return (1);
    }

    i = 0;
    // Check if the first token is NULL
    if (!tab[0])
    {
        printf("Syntax error near unexpected token `|'\n");
        return (1);
    }
    while (tab[i])
    {
        // Check if the current token is a pipe
        if (strcmp(tab[i], "|") == 0)
        {
            // Check if the pipe is at the beginning, end, or followed by another pipe
            if (i == 0 || tab[i + 1] == NULL || (tab[i + 1] && strcmp(tab[i + 1], "|") == 0))
            {
                printf("Syntax error near unexpected token `|'\n");
                return (1);
            }
        }
        i++;
    }
    return (0);
}

int No_target_red(t_data *data)
{
    int i;

    i = 0;
    while (data->tab[i])
    {
        if (ft_strcmp(data->tab[i], "<") == 0 || ft_strcmp(data->tab[i], ">") == 0) // ??
        {
            if (data->tab[i + 1] == NULL || ft_strcmp(data->tab[i + 1], "|") == 0) // ls > | wc
            {
                printf("Syntax error near unexpected token `newline'\n");
                return (1);
            }
        }
        i++;
    }
    return (0);
}

int in_range(char c)
{
    if (c == '|' || c == '<' || c == '>')
        return (1);
    return (0);
}

int invalid_token(t_data *data)
{
    int i;
    int j;

    i = 0;
    while (data->tab[i])
    {
        j = 0;
        int counter = 0;
        while (data->tab[i][j])
        {
            if (in_range(data->tab[i][j]))
            {
                counter++;
                if (counter > 2)
                {
                    printf("Syntax error near unexpected token `%c'\n", data->tab[i][j]);
                    return (1);
                }
            }
            else
                counter = 0;
            j++;
        }
        i++;
    }
    return (0);
}

int check_cd(char **tab)
{
    if (!tab || !tab[0]) // Ensure the input is valid
        return (1);

    if (tab[1] && tab[2]) // Check if there are too many arguments
    {
        printf("cd: too many arguments\n");
        return (1);
    }

    if (tab[1] && !is_directory(tab[1])) // Check if the argument is a valid directory
    {
        printf("cd: %s: No such file or directory\n", tab[1]);
        return (1);
    }

    return (0); // No errors
}

int parsing(t_data *data)
{
    // Validate input
    if (!data || !data->tab)
    {
        printf("Error: Invalid input data\n");
        return (1);
    }
    // Check if the command is valid
    if (detect_cmd(data->tab) == 0)
    {
        printf("Command not found\n");
        return (1);
    }
    // Check for syntax errors in pipes, redirections, and tokens
    if (invalid_pipe_position(data->tab) || No_target_red(data) || invalid_token(data))
    {
        return (1); // Error messages are already printed in these functions
    }
    // Handle specific commands with additional syntax checks
    if (ft_strcmp(data->tab[0], "cd") == 0 && check_cd(data->tab))
    {
        printf("Invalid cd command\n");
        return (1);
    }
    // else if (ft_strcmp(data->tab[0], "echo") == 0)
    // {
    //     // Add specific checks for `echo` if needed
    //     return (0); // No specific syntax error for `echo`
    // }
    // else if (ft_strcmp(data->tab[0], "export") == 0)
    // {
    //     // Add specific checks for `export` if needed
    //     return (0); // No specific syntax error for `export`
    // }
    // else if (ft_strcmp(data->tab[0], "unset") == 0)
    // {
    //     // Add specific checks for `unset` if needed
    //     return (0); // No specific syntax error for `unset`
    // }
    // else if (ft_strcmp(data->tab[0], "env") == 0)
    // {
    //     // Add specific checks for `env` if needed
    //     return (0); // No specific syntax error for `env`
    // }
    // else if (ft_strcmp(data->tab[0], "exit") == 0)
    // {
    //     // Add specific checks for `exit` if needed
    //     return (0); // No specific syntax error for `exit`
    // }
    // else if (ft_strcmp(data->tab[0], "cat") == 0)
    // {
    //     // Add specific checks for `cat` if needed
    //     return (0); // No specific syntax error for `cat`
    // }
    // printf("Valid Syntax\n");
    return (0);
}
