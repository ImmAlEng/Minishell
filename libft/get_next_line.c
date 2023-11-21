/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iengels < iengels@student.42vienna.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 17:37:55 by iengels           #+#    #+#             */
/*   Updated: 2023/02/25 20:25:03 by iengels          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_next_line(int fd)
{
	static char		*swap;
	char			*out;
	unsigned int	i;

	i = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	swap = ft_buffer(fd, swap);
	if (swap == NULL)
		return (NULL);
	out = ft_return(swap);
	while (swap[i] != '\n' && swap[i] != '\0')
		i++;
	swap = ft_temp(swap, i);
	return (out);
}

char	*ft_gnl_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*temp;

	i = -1;
	j = 0;
	if (!s1)
	{
		s1 = (char *)malloc(sizeof(char) * 1);
		if (!s1 || !s2)
			return (NULL);
		s1[0] = '\0';
	}
	temp = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!temp)
		return (NULL);
	while (s1[++i])
		temp[i] = s1[i];
	while (s2[j])
		temp[i++] = s2[j++];
	temp[i] = '\0';
	free(s1);
	return (temp);
}

char	*ft_buffer(int fd, char *swap)
{
	int		check;
	char	*buffer;

	check = 42;
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	while (!(ft_strchr(swap, '\n')) && check > 0)
	{
		check = read(fd, buffer, BUFFER_SIZE);
		if (check == -1)
		{
			free(buffer);
			free(swap);
			return (NULL);
		}
		buffer[check] = '\0';
		swap = ft_gnl_strjoin(swap, buffer);
	}
	free(buffer);
	return (swap);
}

char	*ft_return(char *swap)
{
	unsigned int	i;
	char			*s;

	i = 0;
	if (!swap[0])
		return (NULL);
	while (swap[i] != '\n' && swap[i] != '\0')
		i++;
	if (swap[i] == '\n')
		i++;
	s = (char *)malloc(sizeof(char) * (i + 1));
	if (!s)
		return (NULL);
	s[i] = '\0';
	while (i--)
		s[i] = swap[i];
	return (s);
}

char	*ft_temp(char *swap, int i)
{
	char			*s;
	unsigned int	c;

	c = 0;
	if (!swap[i])
	{
		free(swap);
		return (NULL);
	}
	if (swap[i] == '\n')
		i++;
	while (swap[i + c] != '\0')
		c++;
	s = (char *)malloc(sizeof(char) * (c + 1));
	if (!s)
		return (NULL);
	s[c] = '\0';
	while (c--)
		s[c] = swap[i + c];
	free(swap);
	return (s);
}
