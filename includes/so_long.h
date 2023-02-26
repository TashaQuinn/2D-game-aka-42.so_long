#ifndef SO_LONG_H
# define SO_LONG_H

# include "../libs/MLX/include/MLX42/MLX42.h"
# include "../libs/libft/srcs/libft.h"

# include <sys/types.h> //
# include <stdlib.h>
# include <stdio.h> // strerror()
# include <unistd.h>
# include <fcntl.h>
# include <sys/errno.h>
# include <string.h> // strerror()
# include <time.h> // rand()

# ifndef _WIN32
	# include <sys/wait.h>
	# define WIN 0
# else 
	# include <windows.h>
	# include <mmsystem.h>
	# define WIN 1
# endif

# define BLOCK			48 // 48x28
# define HALF_BLOCK		24
# define CHAR_SPEED		5 // speed up or slow down char's movements
# define MOB_SPEED		1 // speed up or slow down mobs' movements
# define STAR_COUNT 	7 // needed for loading images
# define WITCH_COUNT	1 // needed for loading images
# define BATS_COUNT 	2 // needed for loading images
# define TILE_COUNT 	50 // needed for loading images
# define ACCEL 			1
# define ACCEL_MOD		1.3
# define JUMP_HEIGHT	100

typedef enum s_img
{
	BG,
	WALL,
	TILE1,
	TILE2,
	CHAR, // changes its image according to the char's mov dir
	CHAR_L_FLY1,
	CHAR_R_FLY1,
	CHAR_L_FLY2,
	CHAR_R_FLY2,
	DOOR,
	STAR_MARK1,
	STAR_MARK2,
	STAR1,
	STAR2,
	WITCH_L_DOWN,
	WITCH_R_DOWN,
	WITCH_L_UP,
	WITCH_R_UP,
	BAT_L_FLY1,
	BAT_R_FLY1,
	BAT_L_FLY2,
	BAT_R_FLY2,
	IMG_COUNT,

} t_img;

typedef struct s_door
{
	size_t	x_door_start;
	size_t	y_door_end;

} t_door;

typedef struct s_tile
{
	mlx_image_t	 	*tile_img[TILE_COUNT];
	mlx_image_t	 	**type[1];
	size_t			x_tile[TILE_COUNT];
	size_t			y_tile[TILE_COUNT];
	size_t			x_tile_start[TILE_COUNT];
	size_t			y_tile_start[TILE_COUNT];
	size_t			x_tile_end[TILE_COUNT];
	size_t			y_tile_end[TILE_COUNT];

} t_tile;

typedef struct s_mob
{
	mlx_image_t	 	*witch_img[WITCH_COUNT];
	mlx_image_t	 	*bat_img[BATS_COUNT];
	mlx_image_t	 	**type[2];
	int				x_witch[WITCH_COUNT];
	int				y_witch[WITCH_COUNT];
	int				x_bat[BATS_COUNT];
	int				y_bat[BATS_COUNT];

} t_mob;

typedef struct s_star
{
	mlx_image_t	 	*star_img[STAR_COUNT];
	mlx_image_t	 	**type[1];	
	size_t			x_star[STAR_COUNT];
	size_t			y_star[STAR_COUNT];
	size_t			x_star_start[STAR_COUNT];
	size_t			y_star_start[STAR_COUNT];
	size_t			x_star_end[STAR_COUNT];
	size_t			y_star_end[STAR_COUNT];

} t_star;

typedef struct s_map
{
	void			*mlx;
	char			**map;
	int				width;
	int				height;
	//int			steps;
	xpm_t			*xpm[IMG_COUNT];
	mlx_image_t		*img[IMG_COUNT];
	// door
	t_door			door; // struct for storing door's coords (it is the Moon actually)
	// tiles (aka clouds)
	t_tile			tile; // struct for storing clouds' images
	int 			tiles; // nbr of tiles
	bool			tile_hidden[TILE_COUNT];
	size_t			tile_mov[TILE_COUNT]; // movement for every cloudiiieee
	// char
	size_t			char_dir;
	int				lives;
	// jump
	float			accel;
	bool			jump_lock;
	// mobs
	int 			mobs; // nbr of mobs
	t_mob			mob; // struct for storing moves' images and mobs' coords
	bool			witch_move_left[WITCH_COUNT];
	bool			bat_move_left[BATS_COUNT];
	size_t			witch_dir[WITCH_COUNT]; // movement dir for every witch
	size_t			bat_dir[BATS_COUNT]; // movement dir for every bat
	// stars
	int				stars; // nbr of stars
	t_star			star; // struct for storing moves' images and stars' coords
	size_t			star_mov[STAR_COUNT]; // movement for every star
	int				lit_up_stars_count;
	bool			star_lit_up[STAR_COUNT]; // has the star been lit up or not

} t_map;


t_map 	*map_parsing(int argc, char **argv);
char	*get_line(char **av);
t_map	*init_map(char *line);
bool 	load_textures(xpm_t **xpm);
bool 	convert_to_image(t_map *map, xpm_t **xpm, mlx_image_t **img);
bool	display_sprites_and_steps(t_map *map);

// hook? HOOK!
void 	hook(void *map); // loop hook for everything what is moving;)
void 	end_game();

// tile animation and interactions
void 	mob_animation(t_map *map, size_t x_char, size_t y_char); /* iterating 
		through all mobs, changing their movements' dirs and making them fly 
		from the left to the right and vice versa ;) */

// tile animation and interactions
void 	tile_animation(t_map *map); // make clouds move up and down to simulate hovering
void 	hide_tile(t_map *map, size_t x_char, size_t y_char);

// char animation and interactions
void 	jump(t_map *map, size_t x_char, size_t y_char);
void 	char_animation(t_map *map, size_t x_char, size_t y_char); // key hook for a char
void 	char_delete_and_put_images(t_map *map, xpm_t **xpm, size_t x_char, 
		size_t y_char, t_img new_image);
void 	lit_up_stars(t_map *map, size_t x_char, size_t y_char);

// star animation and interactions
void 	star_animation(t_map *map); /* iterating through all stars, making them 
		appear and then shiiine */
void 	star_move(t_map *map, int star_num); // changing movement type (aka mov_dir)
void 	stars_delete_and_put_images(t_map *map, xpm_t **xpm, int star_num, 
		size_t x_star, size_t y_star, t_img new_image);
		// deleting old images and replacing with new ones

void 	close_window(t_map *map, char *str);
void 	terminate(t_map *map);
//void	free_arr_map(t_map *map);

#endif
