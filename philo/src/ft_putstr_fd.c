/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 19:46:38 by sarchoi           #+#    #+#             */
/*   Updated: 2022/03/16 19:47:16 by sarchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int ft_strlen(const char *str)
{
  int i;

  i = 0;
  while (str[i])
    i++;
  return (i);
}

void  ft_putstr_fd(char *s, int fd)
{
  write(fd, s, ft_strlen(s));
}
