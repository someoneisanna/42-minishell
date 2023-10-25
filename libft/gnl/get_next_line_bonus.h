/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 12:42:01 by ataboada          #+#    #+#             */
/*   Updated: 2023/10/06 17:22:34 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

// ---------------------------------- INCLUDES ---------------------------------

# include <unistd.h>
# include <stdlib.h>

// ---------------------------------- DEFINES ----------------------------------

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# ifndef MAX_O
#  define MAX_O 1024
# endif

// ---------------------------------- PROTOTYPES -------------------------------

char	*get_next_line(int fd);
char	*gnl_read_file(int fd, char *storage);
char	*gnl_get_current_line(char *storage);
char	*gnl_update_storage(char *storage);

size_t	gnl_strclen(const char *str, int c);
char	*gnl_strchr(const char *str, int c);
void	*gnl_memcpy(void *dest, const void *src, size_t n);
char	*gnl_merge_strs(char *s1, char const *s2);
char	*gnl_dupstr(const char *s, size_t n);

#endif
