/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoraji <yoraji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 21:39:36 by yoraji            #+#    #+#             */
/*   Updated: 2025/04/19 21:40:14 by yoraji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
    const unsigned char		*s;
    unsigned char			*d;
    size_t					i;

    i = 0;
    if (!src && !dest)
        return (0);
    s = (const unsigned char *)src;
    d = (unsigned char *)dest;
    while (i < n)
    {
        d[i] = s[i];
        i++;
    }
    return (dest);
}
