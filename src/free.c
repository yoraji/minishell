/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoraji <yoraji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 05:33:42 by yoraji            #+#    #+#             */
/*   Updated: 2025/04/22 05:34:25 by yoraji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void free_tab(char **tab)
{
    int i;

    if (!tab) 
        return;
    i = 0;
    while (tab[i])
    {
        free(tab[i]);
        tab[i] = NULL; // Set to NULL to avoid double free
        i++;
    }
    free(tab);
    tab = NULL; // Set the pointer to NULL after freeing
}

void   free_data(t_data *data)
{
    // Function to free allocated memory in data
    if (data->envp)
        free(data->envp);
    if (data->cmds)
        free(data->cmds);
    if (data->pipes)
        free(data->pipes);
    if (data->redirs)
        free(data->redirs);
    if (data->hdocs)
        free(data->hdocs);
}
