/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoraji <yoraji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 04:55:50 by yoraji            #+#    #+#             */
/*   Updated: 2025/04/24 03:04:53 by yoraji           ###   ########.fr       */
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

//this functrion should replace the $input and slpit as a token
char **expand_env(char **input)
{
    char  *new_input;

    
    free (input);
    return new_input
}