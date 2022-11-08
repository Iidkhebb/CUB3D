/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidkhebb <iidkhebb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 22:48:26 by iidkhebb          #+#    #+#             */
/*   Updated: 2022/11/08 22:48:27 by iidkhebb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_add_char(char *str, char *c)
{
	int		len;
	char	*n;
	int		i;

	i = -1;
	len = 0;
	while (str[len++])
	{
	}
	n = (char *) malloc(len + 2);
	if (n == NULL)
		return (free(str), NULL);
	while (str[++i])
		n[i] = str[i];
	n[i++] = *c;
	n[i] = 0;
	return (free(str), n);
}
