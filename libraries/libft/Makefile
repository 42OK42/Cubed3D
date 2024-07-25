# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/11 14:20:12 by okrahl            #+#    #+#              #
#    Updated: 2024/07/25 15:41:08 by okrahl           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS			=	ft_isalnum.c\
				ft_isprint.c\
				ft_bzero.c\
				ft_isalpha.c\
				ft_isascii.c\
				ft_isdigit.c\
				ft_isprint.c\
				ft_memcpy.c\
				ft_memmove.c\
				ft_memset.c\
				ft_strlcpy.c\
				ft_strlcat.c\
				ft_toupper.c\
				ft_tolower.c\
				ft_strncpy.c\
				ft_strchr.c\
				ft_strrchr.c\
				ft_memcmp.c\
				ft_strnstr.c\
				ft_atoi.c\
				ft_calloc.c\
				ft_strdup.c\
				ft_substr.c\
				ft_strjoin.c\
				ft_strtrim.c\
				ft_split.c\
				ft_itoa.c\
				ft_strmapi.c\
				ft_striteri.c\
				ft_putchar_fd.c\
				ft_putstr_fd.c\
				ft_putendl_fd.c\
				ft_putnbr_fd.c\
				*ft_memchr.c\
				ft_strncmp.c\
				ft_memcmp.c\
				ft_lstadd_front.c\
				ft_lstadd_back.c\
				ft_lstdelone.c\
				ft_lstclear.c\
				ft_lstnew.c\
				ft_lstsize.c\
				ft_lstiter.c\
				ft_lstlast.c\
				ft_lstmap.c\
				ft_printf.c\
				printcs.c\
				print_math.c\
				print_pointer.c\
				print_umath.c\
				ft_putchar_fd.c\
				ft_putnbr_fd.c\
				get_next_line_utils.c \
				get_next_line.c \
				get_next_line_bonus.c \
				get_next_line_utils_bonus.c

OBJS			= $(SRCS:%.c=%.o)

BONUS_OBJS		= $(BONUSSRCS:%.c=%.o)

CC			= cc
RM			= rm -f
CFLAGS			= -Wall -Wextra -Werror -fPIC
HEADER			= libft.h ft_printf.h get_next_line.h get_next_line_bonus.h

NAME			= libft.a

$(NAME):		$(OBJS) $(HEADER)
				ar rcs $(NAME) $(OBJS)
				
all:			$(NAME)

clean:
				$(RM) $(OBJS) 
				$(RM) $(BONUS_OBJS)

fclean:			clean
				$(RM) $(NAME)

re:				fclean all

bonus:			$(BONUS_OBJS) $(HEADER)
				ar rcs $(NAME) $(BONUS_OBJS)

.PHONY: all clean fclean re bonus

