/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youssef <youssef@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 08:49:57 by yoraji            #+#    #+#             */
/*   Updated: 2025/05/05 08:42:22 by youssef          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int builtin_unset(char **args, char **envp)
{
    int i = 1;
    while (args[i])
    {
        int j = 0;
        while (envp[j])
        {
            if (strncmp(envp[j], args[i], strlen(args[i])) == 0 && envp[j][strlen(args[i])] == '=')
            {
                int k = j;
                while (envp[k])
                {
                    envp[k] = envp[k + 1];
                    k++;
                }
                break;
            }
            j++;
        }
        i++;
    }
    return 0;
}