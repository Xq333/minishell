/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleleux <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 15:28:53 by eleleux           #+#    #+#             */
/*   Updated: 2023/03/12 15:04:59 by eleleux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*recipe;
	int		i;
	int		j;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (recipe = ft_strdup(s2));
	if (!s2)
		return (recipe = ft_strdup(s1));
	recipe = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!recipe)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		recipe[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
		recipe[i++] = s2[j++];
	recipe[i] = '\0';
	return (recipe);
}
