#include "pomoku.h"

int g_player_black_score = 0; /* BLACK */
int g_player_white_score = 0; /* WHITE */

char g_board[MAXIMUM_SIZE][MAXIMUM_SIZE];

unsigned int g_board_row = INITIAL_SIZE;
unsigned int g_board_column = INITIAL_SIZE;

void init_game(void)
{
    unsigned int i;
    unsigned int j;

    g_board_row = INITIAL_SIZE;
    g_board_column = INITIAL_SIZE;

    for (i = 0; i < MAXIMUM_SIZE; ++i) {
        for (j = 0; j < MAXIMUM_SIZE; ++j) {
            g_board[i][j] = '\0';
        }
    }

    g_player_black_score = 0; /* BLACK */
    g_player_white_score = 0; /* WHITE */

}

unsigned int get_row_count(void)
{
    return g_board_row;
}

unsigned int get_column_count(void)
{
    return g_board_column;
}

void increase_row_count(void)
{
    ++g_board_row;
}

void increase_column_count(void)
{
    ++g_board_column;
}

void decrease_row_count(void)
{
    --g_board_row;
}

void decrease_column_count(void)
{
    --g_board_column;
}

void decrease_score(const color_t color, const unsigned int cost)
{
    if (color == COLOR_WHITE) {
        g_player_white_score -= cost;
    }

    if (color == COLOR_BLACK) {
        g_player_black_score -= cost;
    }
}

int get_score(const color_t color)
{
    if (color == COLOR_BLACK) {
        return g_player_black_score;
    }

    if (color == COLOR_WHITE) {
        return g_player_white_score;
    }

    return -1;
}

int get_color(const unsigned int row, const unsigned int col)
{
    if (row < get_row_count() && col < get_column_count()) {
        if (g_board[row][col] == 'O') {
            return COLOR_WHITE;
        }

        if (g_board[row][col] == 'X') {
            return COLOR_BLACK;
        }
    }
    return -1;
}

int is_placeable(const unsigned int row, const unsigned int col)
{
    if (row < get_row_count() && col < get_column_count()) {
        if (g_board[row][col] != '\0') {
            return FALSE;
        }
        return TRUE;
    }
    return FALSE;

}

int place_stone(const color_t color, const unsigned int row, const unsigned int col)
{
    if (is_placeable(row, col) == TRUE) {
        if (color == COLOR_WHITE) {
            g_board[row][col] = 'O';
        }

        if (color == COLOR_BLACK) {
            g_board[row][col] = 'X';
        }
        calculate_score(color, row, col);
        return TRUE;
    }
    return FALSE;
}

void calculate_score(color_t color, const unsigned int row, const unsigned int col)
{
    switch (color) {
    case COLOR_WHITE:
        g_player_white_score += calculate_horizontal_chain(color, row, col);
        g_player_white_score += calculate_vertical_chain(color, row, col);
        g_player_white_score += calculate_left_diagonal_chain(color, row, col);
        g_player_white_score += calculate_right_diagonal_chain(color, row, col);
        break;
    case COLOR_BLACK:
        g_player_black_score += calculate_horizontal_chain(color, row, col);
        g_player_black_score += calculate_vertical_chain(color, row, col);
        g_player_black_score += calculate_left_diagonal_chain(color, row, col);
        g_player_black_score += calculate_right_diagonal_chain(color, row, col);
        break;
    default:
        break;
    }
}

int calculate_horizontal_chain(const color_t color, const unsigned int row, const unsigned int col)
{
    int score = 0;
    int count = 1;

    count_horizontal_stone_recursive(color, DIRECTION_LEFT, &count, row, col);
    count_horizontal_stone_recursive(color, DIRECTION_RIGHT, &count, row, col);

    if (count >= 5) {
        score = count - 4;
    }

    return score;
}

void count_horizontal_stone_recursive(const color_t color, const direction_t direction, int* count, const unsigned int row, const unsigned int col)
{
    if (get_color(row, col) != color) {
        return;
    }

    if (direction == DIRECTION_LEFT && color == get_color(row, col - 1)) {
        (*count)++;
        count_horizontal_stone_recursive(color, direction, count, row, col - 1);
    }

    if (direction == DIRECTION_RIGHT && color == get_color(row, col + 1)) {
        (*count)++;
        count_horizontal_stone_recursive(color, direction, count, row, col + 1);
    }
}

int calculate_vertical_chain(const color_t color, const unsigned int row, const unsigned int col)
{
    int score = 0;
    int count = 1;

    count_vertical_stone_recursive(color, DIRECTION_UP, &count, row, col);
    count_vertical_stone_recursive(color, DIRECTION_DOWN, &count, row, col);

    if (count >= 5) {
        score = count - 4;
    }

    return score;
}

void count_vertical_stone_recursive(const color_t color, const direction_t direction, int* count, const unsigned int row, const unsigned int col)
{
    if (get_color(row, col) != color) {
        return;
    }

    if (direction == DIRECTION_UP && color == get_color(row - 1, col)) {
        (*count)++;
        count_vertical_stone_recursive(color, direction, count, row - 1, col);
    }

    if (direction == DIRECTION_DOWN && color == get_color(row + 1, col)) {
        (*count)++;
        count_vertical_stone_recursive(color, direction, count, row + 1, col);
    }
}

int calculate_left_diagonal_chain(const color_t color, const unsigned int row, const unsigned int col)
{
    int score = 0;
    int count = 1;

    count_left_diagonal_stone_recursive(color, DIRECTION_UP, DIRECTION_LEFT, &count, row, col);
    count_left_diagonal_stone_recursive(color, DIRECTION_DOWN, DIRECTION_RIGHT, &count, row, col);

    if (count >= 5) {
        score = count - 4;
    }

    return score;
}

void count_left_diagonal_stone_recursive(const color_t color, const direction_t vertical_direction, const direction_t horizontal_direction, int* count, const unsigned int row, const unsigned int col)
{
    if (get_color(row, col) != color) {
        return;
    }

    if (vertical_direction == DIRECTION_UP && horizontal_direction == DIRECTION_LEFT && color == get_color(row - 1, col - 1)) {
        (*count)++;
        count_left_diagonal_stone_recursive(color, vertical_direction, horizontal_direction, count, row - 1, col - 1);
    }

    if (vertical_direction == DIRECTION_DOWN && horizontal_direction == DIRECTION_RIGHT && color == get_color(row + 1, col + 1)) {
        (*count)++;
        count_left_diagonal_stone_recursive(color, vertical_direction, horizontal_direction, count, row + 1, col + 1);
    }
}

int calculate_right_diagonal_chain(const color_t color, const unsigned int row, const unsigned int col)
{
    int score = 0;
    int count = 1;

    count_right_diagonal_stone_recursive(color, DIRECTION_UP, DIRECTION_RIGHT, &count, row, col);
    count_right_diagonal_stone_recursive(color, DIRECTION_DOWN, DIRECTION_LEFT, &count, row, col);

    if (count >= 5) {
        score = count - 4;
    }

    return score;
}

void count_right_diagonal_stone_recursive(const color_t color, const direction_t vertical_direction, const direction_t horizontal_direction, int* count, const unsigned int row, const unsigned int col)
{
    if (get_color(row, col) != color) {
        return;
    }

    if (vertical_direction == DIRECTION_UP && horizontal_direction == DIRECTION_RIGHT && color == get_color(row - 1, col + 1)) {
        (*count)++;
        count_right_diagonal_stone_recursive(color, vertical_direction, horizontal_direction, count, row - 1, col + 1);
    }

    if (vertical_direction == DIRECTION_DOWN && horizontal_direction == DIRECTION_LEFT && color == get_color(row + 1, col - 1)) {
        (*count)++;
        count_right_diagonal_stone_recursive(color, vertical_direction, horizontal_direction, count, row + 1, col - 1);
    }
}

int insert_row(const color_t color, const unsigned int row)
{
    const unsigned int COST = 3;
    if (get_row_count() < MAXIMUM_SIZE) {
        if ((color == COLOR_WHITE || color == COLOR_BLACK) && get_score(color) >= COST && row <= get_row_count()) {
            int i;
            int j;
            decrease_score(color, COST);
            increase_row_count();

            if (row == get_row_count() - 1) {
                for (j = 0; j < get_column_count(); ++j) {
                    g_board[row][j] = '\0';
                    return TRUE;
                }
            }

            for (i = get_row_count() - 2; i >= (int)row; --i) {
                for (j = 0; j < get_column_count(); ++j) {
                    g_board[i + 1][j] = g_board[i][j];
                    g_board[i][j] = '\0';
                }
            }
            return TRUE;
        }
        return FALSE;
    }
    return FALSE;
}

int insert_column(const color_t color, const unsigned int col)
{
    const unsigned int COST = 3;
    if (get_column_count() < MAXIMUM_SIZE) {
        if ((color == COLOR_WHITE || color == COLOR_BLACK) && get_score(color) >= COST && col <= get_column_count()) {
            int i;
            int j;
            decrease_score(color, COST);
            increase_column_count();

            if (col == get_column_count() - 1) {
                for (i = 0; i < get_row_count(); ++i) {
                    g_board[i][col] = '\0';
                }
                return TRUE;
            }

            for (j = get_column_count() - 2; j >= (int)col; --j) {
                for (i = 0; i < get_row_count(); ++i) {
                    g_board[i][j + 1] = g_board[i][j];
                    g_board[i][j] = '\0';
                }
            }
            return TRUE;
        }
        return FALSE;
    }
    return FALSE;
}

int remove_row(const color_t color, const unsigned int row)
{
    const unsigned int COST = 3;
    if (get_row_count() > MINIMUM_SIZE) {
        if ((color == COLOR_WHITE || color == COLOR_BLACK) && get_score(color) >= COST && row < get_row_count()) {
            unsigned int i;
            unsigned int j;
            for (i = row; i < get_row_count() - 1; ++i) {
                for (j = 0; j < get_column_count(); ++j) {
                    g_board[i][j] = g_board[i + 1][j];
                }
            }
            decrease_score(color, COST);
            decrease_row_count();
            return TRUE;
        }
        return FALSE;
    }
    return FALSE;
}

int remove_column(const color_t color, const unsigned int col)
{
    const unsigned int COST = 3;
    if (get_column_count() > MINIMUM_SIZE) {
        if ((color == COLOR_WHITE || color == COLOR_BLACK) && get_score(color) >= COST && col < get_column_count()) {
            unsigned int i;
            unsigned int j;
            for (j = col; j < get_column_count() - 1; ++j) {
                for (i = 0; i < get_row_count(); ++i) {
                    g_board[i][j] = g_board[i][j + 1];
                }
            }
            decrease_score(color, COST);
            decrease_column_count();
            return TRUE;
        }
        return FALSE;
    }
    return FALSE;
}

int swap_rows(const color_t color, const unsigned int row0, const unsigned int row1)
{
    const unsigned int COST = 2;
    char tmp;
    unsigned int j;
    if ((color == COLOR_WHITE || color == COLOR_BLACK) && get_score(color) >= COST && row0 < get_row_count() && row1 < get_row_count()) {
        for (j = 0; j < get_column_count(); ++j) {
            tmp = g_board[row0][j];
            g_board[row0][j] = g_board[row1][j];
            g_board[row1][j] = tmp;
        }
        decrease_score(color, COST);
        return TRUE;
    }
    return FALSE;
}

int swap_columns(const color_t color, const unsigned int col0, const unsigned int col1)
{
    const unsigned int COST = 2;
    char tmp;
    unsigned int i;
    if ((color == COLOR_WHITE || color == COLOR_BLACK) && get_score(color) >= COST && col0 < get_column_count() && col1 < get_column_count()) {
        for (i = 0; i < get_row_count(); ++i) {
            tmp = g_board[i][col0];
            g_board[i][col0] = g_board[i][col1];
            g_board[i][col1] = tmp;
        }
        decrease_score(color, COST);
        return TRUE;
    }
    return FALSE;
}

int copy_row(const color_t color, const unsigned int src, const unsigned int dst)
{
    const unsigned int COST = 4;
    unsigned int j;
    if ((color == COLOR_WHITE || color == COLOR_BLACK) && get_score(color) >= COST && src < get_row_count() && dst < get_row_count()) {
        for (j = 0; j < get_column_count(); ++j) {
            g_board[dst][j] = g_board[src][j];
        }
        decrease_score(color, COST);
        return TRUE;
    }
    return FALSE;
}

int copy_column(const color_t color, const unsigned int src, const unsigned int dst)
{
    const unsigned int COST = 4;
    unsigned int i;
    if ((color == COLOR_WHITE || color == COLOR_BLACK) && get_score(color) >= COST && src < get_column_count() && dst < get_column_count()) {
        for (i = 0; i < get_column_count(); ++i) {
            g_board[i][dst] = g_board[i][src];
        }
        decrease_score(color, COST);
        return TRUE;
    }
    return FALSE;
}