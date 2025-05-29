/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 16:15:19 by iezzam            #+#    #+#             */
/*   Updated: 2025/05/29 16:15:37 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"




void update_door_animation(t_cub *cub)
{
  if (!cub->door_anim_active)
    return;

  cub->door_anim_tick++;
  if (cub->door_anim_tick > 8)
  {
    cub->door_anim_tick = 0;
    cub->door_anim_frame++;

    if (cub->door_anim_frame >= 4)
    {
      cub->door_anim_frame = 0;
      cub->door_anim_active = 0;

      cub->data.map.map[cub->door_y][cub->door_x] = 'D';
    }
  }
}

void update_door_close(t_cub *cub)
{
  if (!cub->door_opened)
    return;

  if (cub->door_anim_active)
    return;

  int px = (int)(cub->player.x / BLOCK);
  int py = (int)(cub->player.y / BLOCK);

  int fx = px + (int)round(cos(cub->player.angle));
  int fy = py + (int)round(sin(cub->player.angle));
  int player_is_facing_door = (fx == cub->door_x && fy == cub->door_y);
  int player_is_on_door = (px == cub->door_x && py == cub->door_y);

  if (!player_is_facing_door && !player_is_on_door)
  {
    cub->door_anim_tick = 0;
    cub->door_anim_frame = 0;
    cub->door_anim_active = 0;
    cub->door_opened = 0;
    cub->data.map.map[cub->door_y][cub->door_x] = '2';
  }
}
