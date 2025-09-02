/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build-in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youssef <youssef@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 03:02:53 by yoraji            #+#    #+#             */
/*   Updated: 2025/09/02 04:02:16 by youssef          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int is_builtin(char *cmd)
{
    if (cmd == NULL)
        return 0;
    if (ft_strcmp(cmd, "cd") == 0 || ft_strcmp(cmd, "echo") == 0 ||
        ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "env") == 0 ||
        ft_strcmp(cmd, "export") == 0 || ft_strcmp(cmd, "unset") == 0 ||
        ft_strcmp(cmd, "exit") == 0)
        return 1;
    return 0;
}

int execute_builtin(ASTNode *node, t_data *data)
{
    if (!node || !node->args || !node->args[0])
        return -1;

    // Check if the command is a built-in
    if (is_builtin(node->args[0]))
    {
        if (strcmp(node->args[0], "cd") == 0)
            return builtin_cd(node);
        else if (strcmp(node->args[0], "echo") == 0)
            return builtin_echo(node->args);
        else if (strcmp(node->args[0], "pwd") == 0)
            return builtin_pwd();
        else if (strcmp(node->args[0], "env") == 0)
            return builtin_env(data->envp);
        else if (strcmp(node->args[0], "export") == 0)
            return builtin_export(node->args, data->envp);
        else if (strcmp(node->args[0], "unset") == 0)
            return builtin_unset(node->args, data->envp);
        else if (strcmp(node->args[0], "exit") == 0)
            return builtin_exit(node->args);
    }

    // If not a built-in, execute as an external command
    execvp(node->args[0], node->args); // Execute the external command
    perror("execvp"); // If execvp fails
    return -1;
}

int detect_cmd(char **tab)
{
    if (tab)
    {
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