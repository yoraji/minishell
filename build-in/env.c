/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youssef <youssef@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 08:50:44 by yoraji            #+#    #+#             */
/*   Updated: 2025/05/08 09:56:22 by youssef          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int builtin_env(char **envp)
{
    if (!envp)
        return -1;
    int i=0;
    while(envp[i])
    {
        printf("%s\n", envp[i]);
        i++;
    }
   return 0;
}