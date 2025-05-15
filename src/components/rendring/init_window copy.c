#include "../../include/cub3d.h"

bool touch_one(float px, float py, t_cub *cub);

int close_window(t_cub *cub)
{
	mlx_destroy_window(cub->data.mlx, cub->data.win);
	exit(0);
	return (0);
}

// void init_player(t_player *player, t_cub *cub)
// {
// 	player->angle = PI / 2;

// 	player->key_up = false;
// 	player->key_down = false;
// 	player->key_left = false;
// 	player->key_right = false;

// 	player->left_rotate = false;
// 	player->right_rotate = false;

// 	int y = 0;
// 	int x = 0;
// 	while (cub->data.map.map[y])
// 	{
// 		x = 0;
// 		while (cub->data.map.map[y][x])
// 		{
// 			if (cub->data.map.map[y][x] == 'N')
// 			{
// 				player->x = x * BLOCK + BLOCK / 2;
// 				player->y = y * BLOCK + BLOCK / 2;
// 				cub->data.map.map[y][x] = '0';
// 				return;
// 			}
// 			x++;
// 		}
// 		y++;
// 	}
// }

// int key_press(int key, t_cub *cub)
// {
// 	if (key == XK_Escape)
// 		close_window(cub);
// 	if (key == 119 || key == 65362)
// 		cub->player.key_up = true;
// 	if (key == 115 || key == 65364)
// 		cub->player.key_down = true;
// 	if (key == 97 || key == 65361)
// 		cub->player.key_left = true;
// 	if (key == 100 || key == 65363)
// 		cub->player.key_right = true;
// 	if (key == LEFT)
// 		cub->player.left_rotate = true;
// 	if (key == RIGHT)
// 		cub->player.right_rotate = true;
// 	return (0);
// }

// int key_release(int key, t_cub *cub)
// {
// 	if (key == XK_Escape)
// 		close_window(cub);
// 	if (key == 119 || key == 65362)
// 		cub->player.key_up = false;
// 	if (key == 115 || key == 65364)
// 		cub->player.key_down = false;
// 	if (key == 97 || key == 65361)
// 		cub->player.key_left = false;
// 	if (key == 100 || key == 65363)
// 		cub->player.key_right = false;
// 	if (key == LEFT)
// 		cub->player.left_rotate = false;
// 	if (key == RIGHT)
// 		cub->player.right_rotate = false;

// 	return (0);
// }

// void handle_movement(t_cub *cub)
// {

// 	int speed = 100;
// 	float angle_speed = 0.10;
// 	float cos_angle = cos(cub->player.angle);
// 	float sin_angle = sin(cub->player.angle);
// 	float new_x = cub->player.x;
// 	float new_y = cub->player.y;

// 	if (cub->player.left_rotate)
// 		cub->player.angle -= angle_speed;
// 	if (cub->player.right_rotate)
// 		cub->player.angle += angle_speed;
// 	if (cub->player.angle > 2 * PI)
// 		cub->player.angle = 0;
// 	if (cub->player.angle < 0)
// 		cub->player.angle = 2 * PI;

// 	if (cub->player.key_up)
// 	{
// 		new_x += cos_angle * speed;
// 		new_y += sin_angle * speed;
// 	}
// 	if (cub->player.key_down)
// 	{
// 		new_x -= cos_angle * speed;
// 		new_y -= sin_angle * speed;
// 	}
// 	if (cub->player.key_left)
// 	{
// 		new_x += sin_angle * speed;
// 		new_y -= cos_angle * speed;
// 	}
// 	if (cub->player.key_right)
// 	{
// 		new_x -= sin_angle * speed;
// 		new_y += cos_angle * speed;
// 	}

// 	if (!touch_one(new_x, new_y, cub))
// 	{
// 		cub->player.x = new_x;
// 		cub->player.y = new_y;
// 	}
// }

// void clear_image(t_cub *cub)
// {
// 	int x = 0;
// 	int y = 0;
// 	while (y < HEIGHT)
// 	{
// 		x = 0;
// 		while (x < WIDTH)
// 		{
// 			my_pixel_put(x, y, &cub->data.img, 0);
// 			x++;
// 		}
// 		y++;
// 	}
// }

// bool touch_one(float px, float py, t_cub *cub)
// {
// 	int x = px / BLOCK;
// 	int y = py / BLOCK;

// 	if (cub->data.map.map[y][x] == '1')
// 		return true;
// 	return false;
// }

// void draw_square(int x, int y, int size, int color, t_cub *cub)
// {
// 	int i = 0;
// 	while (i < size)
// 	{
// 		my_pixel_put(x + i, y, &cub->data.img, color);
// 		i++;
// 	}
// 	i = 0;
// 	while (i < size)
// 	{
// 		my_pixel_put(x, y + i, &cub->data.img, color);
// 		i++;
// 	}
// 	i = 0;
// 	while (i < size)
// 	{
// 		my_pixel_put(x + size, y + i, &cub->data.img, color);
// 		i++;
// 	}
// 	i = 0;
// 	while (i < size)
// 	{
// 		my_pixel_put(x + i, y + size, &cub->data.img, color);
// 		i++;
// 	}
// }

// float world_to_minimap_x(float x)
// {
// 	return x * BLOCK_SIZE / BLOCK;
// }

// float world_to_minimap_y(float y)
// {
// 	return y * BLOCK_SIZE / BLOCK;
// }

// void draw_minimap(t_cub *cub)
// {
// 	char **map;
// 	map = cub->data.map.map;
// 	for (int y = 0; map[y] && y < MAP_HEIGHT; y++)
// 	{
// 		for (int x = 0; map[y][x] && x < MAP_WIDTH; x++)
// 		{
// 			if (cub->data.map.map[y][x] == '1')
// 			{
// 				draw_square(x * BLOCK_SIZE, y * BLOCK_SIZE,
// 							BLOCK_SIZE, 0x27d632, cub);
// 			}
// 		}
// 	}

// 	float mini_player_x = world_to_minimap_x(cub->player.x);
// 	float mini_player_y = world_to_minimap_y(cub->player.y);

// 	draw_square(mini_player_x - PLAYER_SIZE / 2,
// 				mini_player_y - PLAYER_SIZE / 2,
// 				PLAYER_SIZE, 0xFF0000, cub);

// 	float line_length = PLAYER_SIZE * 2;
// 	float end_x = mini_player_x + cos(cub->player.angle) * line_length;
// 	float end_y = mini_player_y + sin(cub->player.angle) * line_length;

// 	float dx = end_x - mini_player_x;
// 	float dy = end_y - mini_player_y;
// 	float steps = fmax(fabs(dx), fabs(dy));
// 	float x_inc = dx / steps;
// 	float y_inc = dy / steps;
// 	float x = mini_player_x;
// 	float y = mini_player_y;

// 	for (int i = 0; i < steps; i++)
// 	{
// 		my_pixel_put((int)x, (int)y, &cub->data.img, 0x00FF00);
// 		x += x_inc;
// 		y += y_inc;
// 	}
// }

// float distance(float x, float y)
// {
// 	return sqrt(x * x + y * y);
// }

// float fixed_dist(float x1, float y1, float x2, float y2, t_cub *game)
// {
// 	float delta_x = x2 - x1;
// 	float delta_y = y2 - y1;
// 	float angle = atan2(delta_y, delta_x) - game->player.angle;
// 	float fix_dist = distance(delta_x, delta_y) * cos(angle);
// 	return fix_dist;
// }

// void cast_ray(t_cub *cub, float start_x, int i)
// {
// 	float cos_angle = cos(start_x);
// 	float sin_angle = sin(start_x);
// 	float ray_x = cub->player.x;
// 	float ray_y = cub->player.y;

// 	while (!touch_one(ray_x, ray_y, cub))
	{
		// my_pixel_put(ray_x, ray_y, &cub->data.img, 0xFF0000);
		ray_x += cos_angle;
		ray_y += sin_angle;
	}
	float dist = fixed_dist(cub->player.x, cub->player.y, ray_x, ray_y, cub);
	float height = (BLOCK / dist) * (WIDTH / 2);
	int start_y = (HEIGHT - height) / 2;
	int end = start_y + height;

	while (start_y < end && start_y < WIDTH)
	{
		my_pixel_put(i, start_y, &cub->data.img, 255);
		start_y++;
	}
}

int game_loop(t_cub *cub)
{
	handle_movement(cub);
	clear_image(cub);

	float fraction = PI / 3 / WIDTH;
	float start_x = cub->player.angle - PI / 6;
	int i = 0;
	while (i < WIDTH)
	{
		cast_ray(cub, start_x, i);
		start_x += fraction;
		i++;
	}

	draw_minimap(cub);
	mlx_put_image_to_window(cub->data.mlx, cub->data.win, cub->data.img.img, 0, 0);
	return (0);
}

int hook_window(t_cub *cub)
{
	mlx_hook(cub->data.win, 17, 0, close_window, cub);
	mlx_hook(cub->data.win, 2, 1L << 0, key_press, cub);
	mlx_hook(cub->data.win, 3, 1L << 1, key_release, cub);
	mlx_loop_hook(cub->data.mlx, game_loop, cub);

	mlx_loop(cub->data.mlx);
	return (0);
}

int init_image(t_cub *cub)
{
	cub->data.img.img = mlx_new_image(cub->data.mlx, WIDTH, HEIGHT);
	if (!cub->data.img.img)
		return (perror("Fail to open img"), 1);
	cub->data.img.addr = mlx_get_data_addr(cub->data.img.img, &cub->data.img.bits_per_pixel,
										   &cub->data.img.line_length, &cub->data.img.endian);
	cub->data.img.mlx = cub->data.mlx;
	cub->data.img.win = cub->data.win;
	return (0);
}

int init_window(t_cub *cub)
{
	cub->data.mlx = mlx_init();
	if (!cub->data.mlx)
		return (ft_putendl_fd("Error\nFail to create connection", 2), 1);
	cub->data.win = mlx_new_window(cub->data.mlx, WIDTH, HEIGHT, "Cub3d");
	if (!cub->data.win)
		return (ft_putendl_fd("Error\nFail to open window", 2), 1);
	init_player(&cub->player, cub);
	if (init_image(cub))
		return 1;
	if (hook_window(cub))
		return (1);
	return (0);
}	














// *********************************************
#include "../../include/cub3d.h"


void load_texture(t_cub *cub, t_img *img, char *path)
{
    int w, h;
    img->img = mlx_xpm_file_to_image(cub->data.mlx, path, &w, &h);
    if (!img->img)
    {
        fprintf(stderr, "Failed to load texture: %s\n", path);
        exit(1);
    }
    img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length, &img->endian);
}

void init_textures(t_cub *cub)
{
    cub->texture = malloc(sizeof(t_texture));
    cub->texture->no_path = ft_strdup(IMG_NORTH);
    cub->texture->so_path = ft_strdup(IMG_SOUTH);
    cub->texture->we_path = ft_strdup(IMG_WEST);
    cub->texture->ea_path = ft_strdup(IMG_EAST);

    load_texture(cub, &cub->texture->no_img, cub->texture->no_path);
    load_texture(cub, &cub->texture->so_img, cub->texture->so_path);
    load_texture(cub, &cub->texture->we_img, cub->texture->we_path);
    load_texture(cub, &cub->texture->ea_img, cub->texture->ea_path);
}

void cast_ray(t_cub *cub, float ray_angle, int column)
{
    float ray_x = cub->player.x;
    float ray_y = cub->player.y;
    float cos_angle = cos(ray_angle);
    float sin_angle = sin(ray_angle);

    while (!touch_one(ray_x, ray_y, cub))
    {
        ray_x += cos_angle;
        ray_y += sin_angle;
    }

    float dist = use_fixed_dist(cub->player.x, cub->player.y, ray_x, ray_y, cub);
    float wall_height = (BLOCK / dist) * (WIDTH / 2);
    int start_y = (HEIGHT - wall_height) / 2;
    int end_y = start_y + wall_height;
    if (start_y < 0)
        start_y = 0;
    if (end_y > HEIGHT)
        end_y = HEIGHT;

    t_img *tex = &cub->texture->we_img; // Default texture

    // Basic wall orientation logic
    float hit_x = fmod(ray_x, BLOCK);
    float hit_y = fmod(ray_y, BLOCK);
    if (fabs(hit_x) < fabs(hit_y))
        tex = (cos_angle > 0) ? &cub->texture->we_img : &cub->texture->ea_img;
    else
        tex = (sin_angle > 0) ? &cub->texture->so_img : &cub->texture->no_img;

    int tex_width = 64;
    int tex_height = 64;
    int tex_x = (int)((fmod(ray_x, BLOCK) / BLOCK) * tex_width);
    if (tex_x < 0)
        tex_x = 0;
    if (tex_x >= tex_width)
        tex_x = tex_width - 1;

    for (int y = start_y; y < end_y; y++)
    {
        int d = y * 256 - HEIGHT * 128 + wall_height * 128;
        int tex_y = ((d * tex_height) / (int)wall_height) / 256;
        int pixel = *(unsigned int *)(tex->addr + tex_y * tex->line_length + tex_x * (tex->bits_per_pixel / 8));
        my_pixel_put(column, y, &cub->data.img, pixel);
    }
}

void draw_background(t_cub *cub)
{
    int y = 0;
    int screen_middle = HEIGHT / 2;

    while (y < HEIGHT)
    {
        int x = 0;
        while (x < WIDTH)
        {
            if (y < screen_middle)
                my_pixel_put(x, y, &cub->data.img, FLOOR_TOP);
            else
                my_pixel_put(x, y, &cub->data.img, FLOOR_BOTTOM);
            x++;
        }
        y++;
    }
}

int game_loop(t_cub *cub)
{
    handle_movement(cub);
    clear_image(cub);
    draw_background(cub);

    float fraction = PI / 3 / WIDTH;
    float start_x = cub->player.angle - PI / 6;
    for (int i = 0; i < WIDTH; i++)
    {
        cast_ray(cub, start_x, i);
        start_x += fraction;
    }

    render_draw_minimap(cub);
    mlx_put_image_to_window(cub->data.mlx, cub->data.win, cub->data.img.img, 0, 0);
    return (0);
}