/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youssef <youssef@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 08:50:44 by yoraji            #+#    #+#             */
/*   Updated: 2025/05/05 08:52:22 by youssef          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int builtin_env(char **envp)
{
    if (!envp)
        return -1;
    for (int i = 0; envp[i]; i++)
        printf("%s\n", envp[i]);
    return 0;
}