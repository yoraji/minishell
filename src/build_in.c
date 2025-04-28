/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoraji <yoraji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 03:02:53 by yoraji            #+#    #+#             */
/*   Updated: 2025/04/26 08:44:05 by yoraji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int is_directory(char *path) {
    struct stat path_stat;
    if (stat(path, &path_stat) != 0) {
        printf("path is not exist\n");
        return 0;
    }
    return 1;
}


// int     execute_builtin(t_data *data)
// {
    // if (strcmp(data->tab, "cd") == 0)
    //     return builtin_cd(cmd->args);
    // else if (strcmp(data->tab, "echo") == 0)
    //     return builtin_echo(cmd->args);
    // else if (strcmp(data->tab, "pwd") == 0)
    //     return builtin_pwd();
    // else if (strcmp(data->tab, "env") == 0)
    //     return builtin_env(cmd->envp);
    // else if (strcmp(data->tab, "export") == 0)
    //     return builtin_export(cmd->args, cmd->envp);
    // else if (strcmp(data->tab, "unset") == 0)
    //     return builtin_unset(cmd->args, cmd->envp);
    // else if (strcmp(data->tab, "exit") == 0)
    //     return builtin_exit(cmd->args);
    // return -1; // Not a built-in command
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

    if (args[1] && ft_strcmp(args[1], "-n") == 0)
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