/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build-in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoraji <yoraji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 03:02:53 by yoraji            #+#    #+#             */
/*   Updated: 2025/04/29 09:33:03 by yoraji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


// int     execute_builtin(ASTNode *node, t_data *data)
// {
//     if (strcmp(data->tab, "cd") == 0)
//         return builtin_cd(ASTNode *node->args);
//     else if (strcmp(data->tab, "echo") == 0)
//         return builtin_echo(cmd->args);
//     else if (strcmp(data->tab, "pwd") == 0)
//         return builtin_pwd();
//     else if (strcmp(data->tab, "env") == 0)
//         return builtin_env(cmd->envp);
//     else if (strcmp(data->tab, "export") == 0)
//         return builtin_export(cmd->args, cmd->envp);
//     else if (strcmp(data->tab, "unset") == 0)
//         return builtin_unset(cmd->args, cmd->envp);
//     else if (strcmp(data->tab, "exit") == 0)
//         return builtin_exit(cmd->args);
//     return -1; // Not a built-in command
// }


int detect_cmd(char **tab)
{
    if (tab)
    {
        // ?? !!
        if (ft_strcmp(tab[0], "cd") == 0 || ft_strcmp(tab[0], "echo") == 0 ||
            ft_strcmp(tab[0], "export") == 0 || ft_strcmp(tab[0], "unset") == 0 ||
            ft_strcmp(tab[0], "env") == 0 || ft_strcmp(tab[0], "ls") == 0 ||
            ft_strcmp(tab[0], "cat") == 0 || ft_strcmp(tab[0], "exit") == 0)
        {
            return 1;
        }
    }
    return 0;
}