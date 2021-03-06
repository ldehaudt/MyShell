/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldehaudt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 16:36:11 by ldehaudt          #+#    #+#             */
/*   Updated: 2018/04/19 12:50:10 by ldehaudt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strcpy(char *dst, const char *src)
{
	int n;

	n = 0;
	while (src[n])
	{
		dst[n] = src[n];
		n++;
	}
	dst[n] = '\0';
	return (dst);
}
