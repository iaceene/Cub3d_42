/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 08:49:34 by iezzam            #+#    #+#             */
/*   Updated: 2025/05/29 17:26:08 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

float calculate_brightness(float dist, float max_distance, float min_brightness, float max_brightness)
{
  float brightness = 1.0f - (dist / max_distance);
  return fmaxf(fminf(brightness, max_brightness), min_brightness);
}

unsigned int apply_shading(unsigned int color, float brightness)
{
  int r = ((color >> 16) & 0xFF) * brightness;
  int g = ((color >> 8) & 0xFF) * brightness;
  int b = (color & 0xFF) * brightness;
  int alpha = (color >> 24) & 0xFF;

  return (alpha << 24) | (r << 16) | (g << 8) | b;
}

void draw_wall(t_cub *cub, int screen_x, float ray_dx, float ray_dy,
               float ray_x, float ray_y, int side, float dist)
{
  float wall_height = (BLOCK / dist) * (WIDTH / 2);
  int start_y = (HEIGHT - wall_height) / 2;
  if (start_y < 0)
    start_y = 0;
  int end_y = start_y + wall_height;
  if (end_y > HEIGHT)
    end_y = HEIGHT;

  t_img *tex;
  float wall_hit;

  if (side == 0)
  {
    if (ray_dx < 0)
      tex = &cub->texture->we_img;
    else
      tex = &cub->texture->ea_img;
    wall_hit = fmod(ray_y, BLOCK) / BLOCK;
  }
  else
  {
    if (ray_dy < 0)
      tex = &cub->texture->no_img;
    else
      tex = &cub->texture->so_img;
    wall_hit = fmod(ray_x, BLOCK) / BLOCK;
  }

  int tex_x = (int)(wall_hit * tex->width);
  if ((side == 0 && ray_dx > 0) || (side == 1 && ray_dy < 0))
    tex_x = tex->width - tex_x - 1;

  float step = (float)tex->height / wall_height;
  float tex_pos = (start_y - HEIGHT / 2 + wall_height / 2) * step;

  float max_distance = BLOCK * 6;
  float min_brightness = 0.05f;
  float max_brightness = 1.2f;
  float brightness = calculate_brightness(dist, max_distance, min_brightness, max_brightness);

  if (side == 1)
    brightness *= 0.8f;

  int y = start_y;
  while (y < end_y)
  {
    int tex_y = (int)tex_pos & (tex->height - 1);
    tex_pos += step;
    char *pixel = tex->addr + (tex_y * tex->line_length + tex_x * (tex->bits_per_pixel / 8));
    unsigned int color = *(unsigned int *)pixel;

    unsigned int shaded_color = apply_shading(color, brightness);

    my_pixel_put(screen_x, y, &cub->data.img, shaded_color);
    y++;
  }
}

void draw_door(t_cub *cub, int screen_x, float ray_dx, float ray_dy,
               float ray_x, float ray_y, int side, float dist)
{
  float wall_height = (BLOCK / dist) * (WIDTH / 2);
  int start_y = (HEIGHT - wall_height) / 2;
  if (start_y < 0)
    start_y = 0;
  int end_y = start_y + wall_height;
  if (end_y > HEIGHT)
    end_y = HEIGHT;

  t_img *tex = NULL;
  if (cub->door_anim_active)
    tex = &cub->door_textures[cub->door_anim_frame];
  else
    tex = &cub->door_textures[0];

  if (!tex || !tex->img)
    return;

  float wall_hit;
  if (side == 0)
    wall_hit = fmod(ray_y, BLOCK) / BLOCK;
  else
    wall_hit = fmod(ray_x, BLOCK) / BLOCK;

  int tex_x = (int)(wall_hit * tex->width);
  if ((side == 0 && ray_dx > 0) || (side == 1 && ray_dy < 0))
    tex_x = tex->width - tex_x - 1;

  float step = (float)tex->height / wall_height;
  float tex_pos = (start_y - HEIGHT / 2 + wall_height / 2) * step;

  float max_distance = BLOCK * 6;
  float min_brightness = 0.05f;
  float max_brightness = 1.2f;
  float brightness = calculate_brightness(dist, max_distance, min_brightness, max_brightness);

  if (side == 1)
    brightness *= 0.8f;

  int y = start_y;
  while (y < end_y)
  {
    int tex_y = (int)tex_pos & (tex->height - 1);
    tex_pos += step;
    char *pixel = tex->addr + (tex_y * tex->line_length + tex_x * (tex->bits_per_pixel / 8));
    unsigned int color = *(unsigned int *)pixel;
    unsigned int shaded_color = apply_shading(color, brightness);

    my_pixel_put(screen_x, y, &cub->data.img, shaded_color);
    y++;
  }
}

void cast_ray(t_cub *cub, float ray_angle, int screen_x)
{
  float ray_dir_x = cos(ray_angle);
  float ray_dir_y = sin(ray_angle);

  int map_x = (int)cub->player.x / BLOCK;
  int map_y = (int)cub->player.y / BLOCK;

  float side_dist_x;
  float side_dist_y;

  float delta_dist_x = fabs(1 / ray_dir_x);
  float delta_dist_y = fabs(1 / ray_dir_y);

  int step_x;
  int step_y;
  int side;

  float pos_x = cub->player.x;
  float pos_y = cub->player.y;

  if (ray_dir_x < 0)
  {
    step_x = -1;
    side_dist_x = (pos_x - map_x * BLOCK) * delta_dist_x / BLOCK;
  }
  else
  {
    step_x = 1;
    side_dist_x = ((map_x + 1) * BLOCK - pos_x) * delta_dist_x / BLOCK;
  }

  if (ray_dir_y < 0)
  {
    step_y = -1;
    side_dist_y = (pos_y - map_y * BLOCK) * delta_dist_y / BLOCK;
  }
  else
  {
    step_y = 1;
    side_dist_y = ((map_y + 1) * BLOCK - pos_y) * delta_dist_y / BLOCK;
  }

  char hit_tile = ' ';
  while (1)
  {
    if (side_dist_x < side_dist_y)
    {
      map_x += step_x;
      side_dist_x += delta_dist_x;
      side = 0;
    }
    else
    {
      map_y += step_y;
      side_dist_y += delta_dist_y;
      side = 1;
    }

    hit_tile = cub->data.map.map[map_y][map_x];
    if (hit_tile == '1' || hit_tile == '2' || hit_tile == '3')
      break;
  }

  float hit_x, hit_y;
  if (side == 0)
  {
    hit_x = cub->player.x + (map_x * BLOCK - cub->player.x + (1 - step_x) * BLOCK / 2) / ray_dir_x * ray_dir_x;
    hit_y = cub->player.y + (map_x * BLOCK - cub->player.x + (1 - step_x) * BLOCK / 2) / ray_dir_x * ray_dir_y;
  }
  else
  {
    hit_x = cub->player.x + (map_y * BLOCK - cub->player.y + (1 - step_y) * BLOCK / 2) / ray_dir_y * ray_dir_x;
    hit_y = cub->player.y + (map_y * BLOCK - cub->player.y + (1 - step_y) * BLOCK / 2) / ray_dir_y * ray_dir_y;
  }

  float dist = use_fixed_dist(cub->player.x, cub->player.y, hit_x, hit_y, cub);

  if (hit_tile == '2')
    draw_door(cub, screen_x, ray_dir_x, ray_dir_y, hit_x, hit_y, side, dist);
  else
    draw_wall(cub, screen_x, ray_dir_x, ray_dir_y, hit_x, hit_y, side, dist);
}

/************************************************ */

void update_enemy_animation(t_cub *cub)
{
  cub->enemy_anim_tick++;
  if (cub->enemy_anim_tick > cub->enemy_anim_speed)
  {
    cub->enemy_anim_tick = 0;
    cub->enemy_anim_frame = (cub->enemy_anim_frame + 1) % MAX_ENEMY;
  }
}

void calculate_enemy_sprites(t_cub *cub)
{
  for (int i = 0; i < cub->enemy_count; i++)
  {
    if (!cub->enemies[i].alive)
      continue;

    float dx = cub->enemies[i].x - cub->player.x;
    float dy = cub->enemies[i].y - cub->player.y;
    cub->enemies[i].dist = sqrt(dx * dx + dy * dy);

    float angle = atan2(dy, dx) - cub->player.angle;
    while (angle > PI)
      angle -= 2 * PI;
    while (angle < -PI)
      angle += 2 * PI;

    if (fabs(angle) < PI / 2)
    {
      cub->enemies[i].sprite_x = (int)((WIDTH / 2) * (1 + angle / (PI / 3)));
    }
    else
    {
      cub->enemies[i].sprite_x = -1;
    }
  }
}

void sort_enemies_by_distance(t_cub *cub)
{
  int i = 0;
  while (i < cub->enemy_count - 1)
  {
    int j = 0;
    while (j < cub->enemy_count - i - 1)
    {
      if (cub->enemies[j].dist < cub->enemies[j + 1].dist)
      {
        t_enemy temp = cub->enemies[j];
        cub->enemies[j] = cub->enemies[j + 1];
        cub->enemies[j + 1] = temp;
      }
      j++;
    }
    i++;
  }
}

float cast_single_ray(t_cub *cub, float ray_angle)
{
  float ray_dir_x = cos(ray_angle);
  float ray_dir_y = sin(ray_angle);

  int map_x = (int)cub->player.x / BLOCK;
  int map_y = (int)cub->player.y / BLOCK;

  float side_dist_x, side_dist_y;
  float delta_dist_x = fabs(1 / ray_dir_x);
  float delta_dist_y = fabs(1 / ray_dir_y);

  int step_x;
  if (ray_dir_x < 0)
    step_x = -1;
  else
    step_x = 1;

  int step_y;
  if (ray_dir_y < 0)
    step_y = -1;
  else
    step_y = 1;

  if (ray_dir_x < 0)
    side_dist_x = (cub->player.x - map_x * BLOCK) * delta_dist_x / BLOCK;
  else
    side_dist_x = ((map_x + 1) * BLOCK - cub->player.x) * delta_dist_x / BLOCK;

  if (ray_dir_y < 0)
    side_dist_y = (cub->player.y - map_y * BLOCK) * delta_dist_y / BLOCK;
  else
    side_dist_y = ((map_y + 1) * BLOCK - cub->player.y) * delta_dist_y / BLOCK;

  while (1)
  {
    if (side_dist_x < side_dist_y)
    {
      map_x += step_x;
      side_dist_x += delta_dist_x;
    }
    else
    {
      map_y += step_y;
      side_dist_y += delta_dist_y;
    }

    char tile = cub->data.map.map[map_y][map_x];
    if (tile == '1' || tile == '2' || tile == '3')
      break;
  }

  float dist;
  if (side_dist_x < side_dist_y)
    dist = side_dist_x * BLOCK;
  else
    dist = side_dist_y * BLOCK;

  return dist;
}

void draw_enemy(t_cub *cub)
{
  update_enemy_animation(cub);
  calculate_enemy_sprites(cub);
  sort_enemies_by_distance(cub);

  t_img *tex = &cub->texture->enemy[cub->enemy_anim_frame];
  if (!tex->img)
    return;

  int i = 0;
  while (i < cub->enemy_count)
  {
    if (!cub->enemies[i].alive || cub->enemies[i].sprite_x < 0)
    {
      i++;
      continue;
    }

    float dist = cub->enemies[i].dist;
    if (dist < 10.0f)
    {
      i++;
      continue;
    }

    float angle = atan2(cub->enemies[i].y - cub->player.y,
                        cub->enemies[i].x - cub->player.x);
    float ray_dist = cast_single_ray(cub, angle);
    if (ray_dist < dist - 10.0f)
    {
      i++;
      continue;
    }

    int sprite_size = (int)(HEIGHT / dist * BLOCK);
    int draw_x = cub->enemies[i].sprite_x - sprite_size / 2;
    int draw_y = (HEIGHT - sprite_size) / 2;

    float brightness = fmaxf(0.1f, 1.0f - (dist / (BLOCK * 8)));

    int y = 0;
    while (y < sprite_size)
    {
      int screen_y = draw_y + y;
      if (screen_y < 0 || screen_y >= HEIGHT)
      {
        y++;
        continue;
      }

      int x = 0;
      while (x < sprite_size)
      {
        int screen_x = draw_x + x;
        if (screen_x < 0 || screen_x >= WIDTH)
        {
          x++;
          continue;
        }

        int tex_x = x * tex->width / sprite_size;
        int tex_y = y * tex->height / sprite_size;

        unsigned int color = *(unsigned int *)(tex->addr +
                                               (tex_y * tex->line_length + tex_x * (tex->bits_per_pixel / 8)));

        if ((color & 0x00FFFFFF) != 0)
        {
          int r = ((color >> 16) & 0xFF) * brightness;
          int g = ((color >> 8) & 0xFF) * brightness;
          int b = (color & 0xFF) * brightness;
          my_pixel_put(screen_x, screen_y, &cub->data.img, (r << 16) | (g << 8) | b);
        }
        x++;
      }
      y++;
    }
    i++;
  }
}
int game_loop(t_cub *cub)
{
  handle_movement(cub);
  clear_image(cub);
  draw_split_background(cub);

  float ray_step = (PI / 3) / WIDTH;
  float ray_angle = cub->player.angle - (PI / 6);

  int x = 0;
  while (x < WIDTH)
  {
    cast_ray(cub, ray_angle, x);
    ray_angle += ray_step;
    x++;
  }

  draw_enemy(cub);
  render_draw_minimap(cub);
  draw_weapon(cub);

  update_eye_animation(cub);
  draw_eye(cub);
  update_door_animation(cub);
  // update_door_close(cub);
  mlx_put_image_to_window(cub->data.mlx, cub->data.win, cub->data.img.img, 0, 0);
  return 0;
}