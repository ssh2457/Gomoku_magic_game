#ifndef GOMOKU_H
#define GOMOKU_H

#include "color.h"
#include "cost.h"

#include <stdio.h>
#include <Windows.h>

#define MIN_SIZE (10)
#define MAX_SIZE (20)
#define INITIAL_SIZE (15)

#define EMPTY ('\0')

void init_game(void);

unsigned int get_row_count(void);

unsigned int get_column_count(void);

int get_score(const color_t color);

int get_color(const unsigned int row, const unsigned int col);

int is_placeable(const unsigned int row, const unsigned int col);

int place_stone(const color_t color, const unsigned int row, const unsigned int col);

void increase_row(void);

void decrease_row(void);

void increase_column(void);

void decrease_column(void);

void update_score(const color_t color, const unsigned int row, const unsigned int col);

void count_horizontal_stone(const color_t color, const unsigned int row, const unsigned int col, unsigned int* count);

void count_left_stone_recursive(const color_t color, const unsigned int row, const unsigned int col, unsigned int* count);

void count_right_stone_recursive(const color_t color, const unsigned int row, const unsigned int col, unsigned int* count);

void count_vertical_stone(const color_t color, const unsigned int row, const unsigned int col, unsigned int* count);

void count_up_stone_recursive(const color_t color, const unsigned int row, const unsigned int col, unsigned int* count);

void count_bottom_stone_recursive(const color_t color, const unsigned int row, const unsigned int col, unsigned int* count);

void count_left_diagonal_stone(const color_t color, const unsigned int row, const unsigned int col, unsigned int* count);

void count_left_up_stone_recursive(const color_t color, const unsigned int row, const unsigned int col, unsigned int* count);

void count_right_bottom_stone_recursive(const color_t color, const unsigned int row, const unsigned int col, unsigned int* count);

void count_right_diagonal_stone(const color_t color, const unsigned int row, const unsigned int col, unsigned int* count);

void count_rihgt_up_stone_recursive(const color_t color, const unsigned int row, const unsigned int col, unsigned int* count);

void count_left_bottom_stone_recursive(const color_t color, const unsigned int row, const unsigned int col, unsigned int* count);

int consume_score(const color_t color, const cost_t cost);

void display_board(void);

/* SPECIAL MOVES */
int insert_row(const color_t color, const unsigned int row);

int insert_column(const color_t color, const unsigned int col);

int remove_row(const color_t color, const unsigned int row);

int remove_column(const color_t color, const unsigned int col);

int swap_rows(const color_t color, const unsigned int row0, const unsigned int row1);

int swap_columns(const color_t color, const unsigned int col0, const unsigned int col1);

int copy_row(const color_t color, const unsigned int src, const unsigned int dst);

int copy_column(const color_t color, const unsigned int src, const unsigned int dst);

#endif /* GOMOKU_H */
