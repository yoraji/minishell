/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoraji <yoraji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 08:51:57 by yoraji            #+#    #+#             */
/*   Updated: 2025/04/29 11:07:37 by yoraji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int     builtin_echo(char **args)
{
    // Echo command
    int i = 1;
    int newline = 1;

    if (args[1] && ft_strcmp(args[1], "-n") == 0) // -nnn
    {
        newline = 0;
        i++;
    }
    while(args[0][i])
    {
        printf("%s", args[i]);
        if (args[i + 1]) // ??
            printf(" ");
        if (newline == 1 && args[0][i + 1] == '\0')
            printf("\n");
        i++;
    }
    return 0;
}