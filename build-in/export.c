/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youssef <youssef@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 08:50:35 by yoraji            #+#    #+#             */
/*   Updated: 2025/05/08 10:04:56 by youssef          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


int builtin_export(char **args, char **envp)
{
    if (!args || !envp)
        return -1;
    int i = 1;
    while (args[i])
    {
        char *key = strtok(args[i], "=");// ??
        char *value = strtok(NULL, "="); // ??
        
        if (key && value)
        {
            // Check if the key already exists in the environment
            int j = 0;
            while (envp[j])
            {
                if (strncmp(envp[j], key, strlen(key)) == 0 && envp[j][strlen(key)] == '=')
                {
                    // Update the existing key with the new value
                    char *new_entry = malloc(strlen(key) + strlen(value) + 2);
                    if (!new_entry)
                    {
                        perror("malloc");
                        return -1;
                    }
                    sprintf(new_entry, "%s=%s", key, value);
                    free(envp[j]);
                    envp[j] = new_entry;
                    break;
                }
                j++;
            }
            // If the key does not exist, add it to the environment
            if (!envp[j])
            {
                char *new_entry = malloc(strlen(key) + strlen(value) + 2);
                if (!new_entry)
                {
                    perror("malloc");
                    return -1;
                }
                sprintf(new_entry, "%s=%s", key, value);
                envp[j] = new_entry;
                envp[j + 1] = NULL;
            }
        }
        else
        {
            fprintf(stderr, "export: invalid argument: %s\n", args[i]);
            return -1;
        }
        i++;
    }
    return 0;
}