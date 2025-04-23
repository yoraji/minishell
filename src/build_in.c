/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoraji <yoraji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 03:02:53 by yoraji            #+#    #+#             */
/*   Updated: 2025/04/22 05:19:27 by yoraji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int     is_builtin(char *cmd)
{
    // Check if the command is a built-in command
    if (strcmp(cmd, "cd") == 0 || strcmp(cmd, "echo") == 0 ||
        strcmp(cmd, "export") == 0 || strcmp(cmd, "unset") == 0 ||
        strcmp(cmd, "env") == 0 || strcmp(cmd, "exit") == 0)
    {
        return 1; // Built-in command
    }
    return 0; // Not a built-in command
}

// int     execute_builtin(t_cmd *cmd)
// {
//     if (strcmp(cmd->cmd, "cd") == 0)
//         return builtin_cd(cmd->args);
//     else if (strcmp(cmd->cmd, "echo") == 0)
//         return builtin_echo(cmd->args);
//     else if (strcmp(cmd->cmd, "pwd") == 0)
//         return builtin_pwd();
//     else if (strcmp(cmd->cmd, "env") == 0)
//         return builtin_env(cmd->envp);
//     else if (strcmp(cmd->cmd, "export") == 0)
//         return builtin_export(cmd->args, cmd->envp);
//     else if (strcmp(cmd->cmd, "unset") == 0)
//         return builtin_unset(cmd->args, cmd->envp);
//     else if (strcmp(cmd->cmd, "exit") == 0)
//         return builtin_exit(cmd->args);
//     return -1; // Not a built-in command
// }

int     builtin_cd(char **args)
{
    // Change directory command
    if (args[1] == NULL)
    {
        fprintf(stderr, "cd: missing argument\n"); // ??
        return -1;
    }
    if (chdir(args[1]) != 0) // ??
    {
        perror("cd"); // ??
        return -1;
    }
    return 0;
}

int     builtin_echo(char **args)
{
    // Echo command
    int i = 1;
    int newline = 1;

    if (args[1] && strcmp(args[1], "-n") == 0)
    {
        newline = 0;
        i++;
    }
    while(args[0][i])
    {
        if (newline == 1 && args[0][i])
        printf("%s", args[i]);
        if (args[i + 1]) // ?? 
            printf(" ");
        if (newline == 1 && args[0][i + 1] == '\0')
            printf("\n");
        i++;
    }
    return 0;
}

int     builtin_pwd(void)
{
    // Print working directory command
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        printf("%s\n", cwd);
        return 0;
    }
    else
    {
        perror("pwd");
        return -1;
    }
}

int detect_cmd(char **tab)
{
    int i = 0;
    if (tab)
    {
        // ?? !!
        if (strcmp(tab[i], "cd") == 0 || strcmp(tab[i], "echo") == 0 ||
            strcmp(tab[i], "export") == 0 || strcmp(tab[i], "unset") == 0 ||
            strcmp(tab[i], "env") == 0 || strcmp(tab[i], "ls") == 0 ||
            strcmp(tab[i], "cat") == 0 || strcmp(tab[i], "exit") == 0)
        {
            return 1;
        }
        i++;
    }
    return 0;
}