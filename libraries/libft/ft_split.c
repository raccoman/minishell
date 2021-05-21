/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiordan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 11:13:45 by mgiordan          #+#    #+#             */
/*   Updated: 2021/01/13 11:13:48 by mgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	calc_word_len(const char *str, char del)
{
	size_t	i;

	if (str == NULL)
		return (0);
	i = 0;
	while (str[i] && str[i] != del)
		i++;
	return (i);
}

int	calc_word_count(const char *str, char del)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] != del && (i == 0 || str[i - 1] == del))
			count++;
		i++;
	}
	return (count);
}

char	**actual_split(char const *str, char del, char **splitted)
{
	int		ret_index;
	int		i;
	int		count;
	char	*word;

	ret_index = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] != del && (i == 0 || str[i - 1] == del))
		{
			count = calc_word_len(str + i, del);
			word = malloc(count + 1);
			if (word == NULL)
				return (NULL);
			ft_strlcpy(word, str + i, count + 1);
			splitted[ret_index++] = word;
			i += count;
		}
		else
			i++;
	}
	splitted[ret_index] = NULL;
	return (splitted);
}

char	**ft_split(char const *str, char del)
{
	int		count;
	char	**splitted;

	if (str == NULL)
		return (NULL);
	count = calc_word_count(str, del);
	splitted = malloc((count + 1) * sizeof(char *));
	if (splitted == NULL)
		return (NULL);
	return (actual_split(str, del, splitted));
}
