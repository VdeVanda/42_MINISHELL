/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_exit2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabatist <vabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 19:02:23 by vabatist          #+#    #+#             */
/*   Updated: 2025/09/03 20:42:54 by vabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Frees an array of strings.
 *
 * This function iterates through a NULL-terminated array of strings,
 * freeing each individual string and then freeing the array itself.
 * It ensures that all allocated memory for the array is properly released.
 *
 * @param arr The array of strings to free
 */
void	free_arr2(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		if (arr[i])
			free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
	arr = NULL;
}
