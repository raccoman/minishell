/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_append_element.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiordan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 15:10:30 by mgiordan          #+#    #+#             */
/*   Updated: 2021/05/21 15:10:32 by mgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_append_element(char **matrix, char *element)
{
	int		i;
	char	**result;

	if (!matrix)
	{
		result = malloc(2 * sizeof(char *));
		result[0] = element;
		result[1] = 0;
		return (result);
	}
	i = 0;
	while (matrix[i])
		i++;
	result = malloc((i + 2) * sizeof(char *));
	i = -1;
	while (matrix[++i])
		result[i] = matrix[i];
	result[i++] = element;
	result[i] = 0;
	free(matrix);
	return (result);
}
