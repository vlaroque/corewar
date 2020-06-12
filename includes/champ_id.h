/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   champ_id.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaroque <vlaroque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 15:56:25 by vlaroque          #+#    #+#             */
/*   Updated: 2020/06/12 15:56:28 by vlaroque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHAMP_ID_H
# define CHAMP_ID_H

/*
** used for bonus of champs number id
*/

typedef struct			s_champid
{
	int					id;
	int					carry;
	int					carried_nbr;
}						t_champid;

#endif
