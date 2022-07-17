/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdrowzee <jdrowzee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 15:11:29 by jdrowzee          #+#    #+#             */
/*   Updated: 2022/07/17 18:01:21 by jdrowzee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	get_next_line(char **line)
{
	char	buffer;

	*line = (char *)malloc(1);
	if (*line == NULL)
		return (-1);
	(*line)[0] = 0;
	read(0, &buffer, 1);
	while (buffer != '\n' && buffer != '\0')
	{
		*line = sum(*line, buffer);
		if (*line == 0)
			return (-1);
	}
	if (buffer == '\n')
		return (1);
	return (0);
}
