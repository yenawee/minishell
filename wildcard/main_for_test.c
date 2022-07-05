/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_for_test.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonjan <hyeonjan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 22:22:28 by hyeonjan          #+#    #+#             */
/*   Updated: 2022/07/05 22:22:28 by hyeonjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(void)
{
	char		**file_names = ft_alert_calloc(2, sizeof(char **));
	file_names[0] = "qwe_123_abc_5858_abc_eee_123_edf";

	t_wildcard	**wildcards = ft_alert_calloc(2, sizeof(void *));

	wildcards[0] = str_to_t_wildcard(ft_strdup("qwe****abc*****eee*edf"));
	wildcards[0]->total_len = 12;
	
	// wildcards[0] = ft_alert_calloc(1, sizeof(t_wildcard));
	// wildcards[0]->front_token = "qwe";
	// wildcards[0]->rear_token = "edf";
	// ft_lstadd_back(&wildcards[0]->middle_tokens, ft_lstnew("abc"));
	// ft_lstadd_back(&wildcards[0]->middle_tokens, ft_lstnew("eee"));
	// wildcards[0]->total_len = 12;
	match_wildcard(file_names, 1, wildcards, 1);
}