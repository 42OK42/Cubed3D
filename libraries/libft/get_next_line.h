/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 14:36:33 by okrahl            #+#    #+#             */
/*   Updated: 2024/09/11 15:55:36 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include "libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char *s1, char *s2);
char	*allocate_memory2(size_t total_length);
size_t	ft_strlen(const char *s);
char	*get_next_line(int fd);
char	*ft_line(char	*read);
char	*ft_next(char	*read);
char	*ft_read(int fd, char *result);
char	*ft_free(char *read, char *buffer);

#endif
