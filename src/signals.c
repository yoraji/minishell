/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoraji <yoraji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 03:04:06 by yoraji            #+#    #+#             */
/*   Updated: 2025/04/22 06:43:30 by yoraji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void sig_handler(int signum)
{
    if (signum == SIGINT)
    {
        write(1, "\n", 1);
        // Handle SIGINT signal
    }
    else if (signum == SIGQUIT)
    {
        write(1, "Quit: 3\n", 8);
        // Handle SIGQUIT signal
    }
}

void    setup_signals(void)
{
    // Set up signal handlers for SIGINT and SIGQUIT
    // signal(SIGINT, sig_handler);
    signal(SIGINT, sig_handler);  // Handle SIGINT signal (Ctrl+C)
    signal(SIGQUIT, sig_handler); // Handle SIGQUIT signal (Ctrl+\)
    return ;   
}
