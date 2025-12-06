/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmangeot <jmangeot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 14:58:34 by jmangeot          #+#    #+#             */
/*   Updated: 2025/12/06 15:23:19 by jmangeot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "../Libft/libft.h"

static int	rot_left(ssize_t *lock_pos, ssize_t move)
{
	size_t	zero_passed;
	size_t	temp;

	zero_passed = move / 100;
	move %= 100;
	if (move < 0)
		move *= -1;
	temp = *lock_pos;
	*lock_pos -= move;
	if (*lock_pos < 0)
	{
		*lock_pos *= -1;
		*lock_pos = 100 - *lock_pos;
		if (*lock_pos && temp)
			zero_passed++;
	}
	return (zero_passed);
}

static int rot_right(ssize_t *lock_pos, ssize_t move)
{
	size_t zero_passed;

	zero_passed = move / 100;
	move %= 100;
	*lock_pos += move;
	if (*lock_pos > 99)
	{
		*lock_pos -= 100;
		if (*lock_pos)
			zero_passed++;
	}
	return (zero_passed);
}

int	main(void)
{
	ssize_t	lock_pos;
	size_t	count;
	char	*current_move;
	int		file_desc;
	size_t	nb;
	size_t	zero_passed;

	count = 0;
	zero_passed = 0;
	nb = 1;
	lock_pos = 50;
	file_desc = open("comb", O_RDONLY);
	if (file_desc < 0)
		return (1);
	while (1)
	{
		current_move = get_next_line(file_desc);
		if (!current_move)
			break ;
		if (*current_move == 'L')
			zero_passed += rot_left(&lock_pos, ft_atoi(current_move + 1));
		else
			zero_passed += rot_right(&lock_pos, ft_atoi(current_move + 1));
		ft_printf("\nmove %i : %s %d - %d\n", nb, current_move, lock_pos, zero_passed);
		if (lock_pos == 0)
			count++;
		nb++;
		free(current_move);
	}
	ft_printf("%d + %d = %d", count, zero_passed, count + zero_passed);
	return (0);
}
