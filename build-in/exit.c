/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youssef <youssef@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 08:35:49 by youssef           #+#    #+#             */
/*   Updated: 2025/05/08 09:57:24 by youssef          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// header 
#include "../includes/minishell.h"


int builtin_exit(char **args)
{
    int status = 0;

    if (args[1])
    {
        if (args[2])
        {
            fprintf(stderr, "exit: too many arguments\n");
            return 1;
        }
        status = ft_atoi(args[1]);
    }

    printf("exit\n");
    exit(status);
}