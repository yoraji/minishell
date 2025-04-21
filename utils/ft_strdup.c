/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoraji <yoraji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 21:22:46 by yoraji            #+#    #+#             */
/*   Updated: 2025/04/19 21:42:22 by yoraji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*ptr;
	size_t			i;

	i = 0;
	ptr = malloc(count * size);
	if (!ptr)
		return (NULL);
	while (i < count * size)
		ptr[i++] = 0;
	return ((void *)(ptr));
}

char	*ft_strdup(const char *s)
{
	size_t		len;
	char		*ptr;

	len = ft_strlen((char *)s);
	ptr = malloc(len + 1);
	if (!ptr)
		return (NULL);
	ft_memcpy(ptr, s, len);
	ptr[len] = '\0';
	return (ptr);
}
