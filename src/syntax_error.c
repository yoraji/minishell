/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoraji <yoraji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 05:21:09 by yoraji            #+#    #+#             */
/*   Updated: 2025/04/22 10:44:52 by yoraji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int detect_cmd_v1(char **tab)
{
    if (strcmp(tab[0], "cd") == 0 ||
        strcmp(tab[0], "echo") == 0 ||
        strcmp(tab[0], "export") == 0 ||
        strcmp(tab[0], "unset") == 0 ||
        strcmp(tab[0], "env") == 0 ||
        strcmp(tab[0], "exit") == 0 ||
        strcmp(tab[0], "ls") == 0 ||
        strcmp(tab[0], "cat") == 0)
    {
        return 1;
    }
    return 0;
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

int No_target_red(t_data *data)
{
    int i;

    i = 0;
    while (data->tab[i])
    {
        if (strcmp(data->tab[i], "<") == 0 || strcmp(data->tab[i], ">") == 0) // ??
        {
            if (data->tab[i + 1] == NULL || strcmp(data->tab[i + 1], "|") == 0) // ls > | wc
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
            {
                counter = 0;
            }
            j++;
        }
        i++;
    }
    return (0);
}

int syntax_error(t_data *data)
{
    if(invalid_pipe_position(data->tab) == 1)
        return (1);
    printf("Invalid pipe position\n");
    if (No_target_red(data) == 1)
        return (1);
    printf("No target redirection\n");
    if (invalid_token(data) == 1)
        return (1);
    return (0);
}
