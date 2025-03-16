/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 13:16:07 by pde-petr          #+#    #+#             */
/*   Updated: 2025/03/16 13:25:13 by pde-petr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdlib.h"

int message_error(char *first_message, char *last_message)
{
    last_message = ft_strjoin(last_message, "\n");
    if (last_message == NULL)
        return 1;
    first_message = ft_strjoin(first_message, last_message);
    if (first_message == NULL)
    {
        free(last_message);
        return 1;
    }
    ft_putstr_fd(first_message, 2);
    free(last_message);
    free(first_message);
    return 0;
}