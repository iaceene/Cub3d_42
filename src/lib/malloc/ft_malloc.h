/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:16:24 by yaajagro          #+#    #+#             */
/*   Updated: 2025/06/02 13:19:10 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

typedef struct s_gb
{
	void			*ptr;
	struct s_gb		*next;
}					t_gb;

void	*ft_malloc(ssize_t len);

#endif
