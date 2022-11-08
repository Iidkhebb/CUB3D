/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidkhebb <iidkhebb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 16:05:13 by iidkhebb          #+#    #+#             */
/*   Updated: 2022/11/08 22:46:16 by iidkhebb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	index;
	char	*out;

	if (!s)
		return (NULL);
	if (len > ft_strlen(s))
		len = ft_strlen(s);
	out = (char *)malloc(sizeof(char) * (len + 1));
	if (!out)
		return (0);
	index = start;
	i = 0;
	while (i < len && index < ft_strlen(s))
		out[i++] = ((char *)s)[index++];
	out[i] = '\0';
	return (out);
}
