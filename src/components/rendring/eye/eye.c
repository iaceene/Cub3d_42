/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eye.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 16:05:38 by iezzam            #+#    #+#             */
/*   Updated: 2025/05/29 16:09:30 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void update_eye_animation(t_cub *cub)
{
  static int direction = -1;
  static int is_cycling = 1;

  cub->eye_anim_tick++;

  if (is_cycling && cub->eye_anim_tick > cub->eye_anim_speed)
  {
    cub->eye_anim_tick = 0;
    cub->eye_anim_frame += direction;

    if (cub->eye_anim_frame >= MAX_EYE - 1 || cub->eye_anim_frame <= 0)
    {
      is_cycling = 0;
      cub->eye_pause_timer = 0;
      direction *= -1;
    }
  }
  else if (!is_cycling)
  {
    cub->eye_pause_timer++;
    if (cub->eye_pause_timer > cub->eye_pause_duration)
    {
      is_cycling = 1;
    }
  }
}

void draw_eye(t_cub *cub)
{
  t_img *eye = &cub->texture->eye[cub->eye_anim_frame];
  if (!eye->addr)
    return;

  for (int y = 0; y < HEIGHT; y++)
  {
    for (int x = 0; x < WIDTH; x++)
    {
      int tex_x = x * eye->width / WIDTH;
      int tex_y = y * eye->height / HEIGHT;

      char *src_pixel = eye->addr + (tex_y * eye->line_length + tex_x * (eye->bits_per_pixel / 8));
      unsigned int color = *(unsigned int *)src_pixel;
      if (color == 0X000000)
        my_pixel_put_img(&cub->data.img, x, y, color);
    }
  }
}
