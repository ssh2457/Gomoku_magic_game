#ifndef POMOKU_H
#define POMOKU_H

#include <Windows.h>

#include "color.h"
#include "direction.h"

#define MAXIMUM_SIZE (20)
#define MINIMUM_SIZE (10)
#define INITIAL_SIZE (15)
#define MINIMUM_STONE_COUNT (5)

/* #define TRUE (1) */
/* #define FALSE (0) */


extern int g_player_black_score; /* BLACK */
extern int g_player_white_score; /* WHITE */

extern char g_board[MAXIMUM_SIZE][MAXIMUM_SIZE];

extern unsigned int g_board_row;
extern unsigned int g_board_column;

void init_game(void);

unsigned int get_row_count(void);

unsigned int get_column_count(void);

void increase_row_count(void);

void increase_column_count(void);

void decrease_row_count(void);

void decrease_column_count(void);

void decrease_score(const color_t color, const unsigned int cost);

int get_score(const color_t color);

int get_color(const unsigned int row, const unsigned int col);

int is_placeable(const unsigned int row, const unsigned int col);

int place_stone(const color_t color, const unsigned int row, const unsigned int col);

void calculate_score(color_t color, const unsigned int row, const unsigned int col);

int calculate_horizontal_chain(const color_t color, const unsigned int row, const unsigned int col);

void count_horizontal_stone_recursive(const color_t color, const direction_t direction, int* count, const unsigned int row, const unsigned int col);

int calculate_vertical_chain(const color_t color, const unsigned int row, const unsigned int col);

void count_vertical_stone_recursive(const color_t color, const direction_t direction, int* count, const unsigned int row, const unsigned int col);

int calculate_left_diagonal_chain(const color_t color, const unsigned int row, const unsigned int col);

void count_left_diagonal_stone_recursive(const color_t color, const direction_t vertical_direction, const direction_t horizontal_direction, int* count, const unsigned int row, const unsigned int col);

int calculate_right_diagonal_chain(const color_t color, const unsigned int row, const unsigned int col);

void count_right_diagonal_stone_recursive(const color_t color, const direction_t vertical_direction, const direction_t horizontal_direction, int* count, const unsigned int row, const unsigned int col);

/* special moves */
int insert_row(const color_t color, const unsigned int row);

int insert_column(const color_t color, const unsigned int col);

int remove_row(const color_t color, const unsigned int row);

int remove_column(const color_t color, const unsigned int col);

int swap_rows(const color_t color, const unsigned int row0, const unsigned int row1);

int swap_columns(const color_t color, const unsigned int col0, const unsigned int col1);

int copy_row(const color_t color, const unsigned int src, const unsigned int dst);

int copy_column(const color_t color, const unsigned int src, const unsigned int dst);

#endif /* POMOKU_H */#pragma once
