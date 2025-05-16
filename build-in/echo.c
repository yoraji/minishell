/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youssef <youssef@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 08:51:57 by yoraji            #+#    #+#             */
/*   Updated: 2025/05/06 07:43:45 by youssef          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int builtin_echo(char **args)
{
    int i = 1;
    int newline = 1;

    // Check for the "-n" flag
    if (args[1] && ft_strcmp(args[1], "-n") == 0)
    {
        newline = 0;
        i++;
    }

    // Iterate over the arguments and print them
    while (args[i])
    {
        printf("%s", args[i]);
        if (args[i + 1]) // Print a space if there are more arguments
            printf(" ");
        i++;
    }

    // Print a newline if the "-n" flag is not present
    if (newline)
        printf("\n");

    return 0;
}