/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoraji <yoraji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 08:50:53 by yoraji            #+#    #+#             */
/*   Updated: 2025/04/29 14:22:47 by yoraji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


int is_directory(char *path)
{
    struct stat path_stat;
    if (stat(path, &path_stat) != 0) {
        perror("cd");
        return 0;
    }
    if (!S_ISDIR(path_stat.st_mode)) {
        printf("cd: %s: Not a directory\n", path);
        return 0;
    }
    if (access(path, X_OK) != 0) {
        printf("cd: %s: Permission denied\n", path);
        return 0;
    }
    return 1;
}
// for perotection
// Duplicate the string to avoid potential issues with modifying the returned pointer

char *get_env_value(const char *name) {
    char *value = getenv(name);
    if (value == NULL)
        return NULL;
    return strdup(value);
}

char *set_env_value(const char *name, const char *value) {
    if (setenv(name, value, 1) != 0) {
        perror("setenv");
        return NULL;
    }
    return strdup(value);
}

int builtin_cd(ASTNode *node){
    char *path;
    char cwd[1024];
    char *oldpwd;

    if (!node || node->type != NODE_COMMAND || !node->args) {
        fprintf(stderr, "cd: missing argument\n");
        return -1;
    }
    if (!node->args[1] || ft_strcmp(node->args[1], "~") == 0 ||
        ft_strcmp(node->args[1], "$HOME") == 0 || ft_strcmp(node->args[1], "--") == 0) {
        path = get_env_value("HOME");
        if (!path) {
            fprintf(stderr, "cd: HOME not set\n");
            return -1;
        }
    } else if (ft_strcmp(node->args[1], "-") == 0) {
        path = get_env_value("OLDPWD");
        if (!path) {
            fprintf(stderr, "cd: OLDPWD not set\n");
            return -1;
        }
        printf("%s\n", path);
    } else
        path = node->args[1];
    if (!is_directory(path))
        return -1;
    oldpwd = get_env_value("PWD");
    if (chdir(path) != 0) {
        perror("cd");
        return -1;
    }

    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        perror("getcwd");
        return -1;
    }

    if (oldpwd)
        set_env_value("OLDPWD", oldpwd);
    set_env_value("PWD", cwd);
    return 0;
}

