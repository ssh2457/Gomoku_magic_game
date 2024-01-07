#include "gomoku.h"

static unsigned int s_row_size = INITIAL_SIZE;
static unsigned int s_col_size = INITIAL_SIZE;

static int s_white_score = 0;
static int s_black_score = 0;

static char s_board[MAX_SIZE][MAX_SIZE] = { { EMPTY, }, };

void init_game(void)
{
    unsigned int i;
    unsigned int j;

    s_row_size = INITIAL_SIZE;
    s_col_size = INITIAL_SIZE;

    s_white_score = 0;
    s_black_score = 0;

    for (i = 0; i < s_row_size; ++i) {
        for (j = 0; j < s_row_size; ++j) {
            s_board[i][j] = EMPTY;
        }
    }
}

unsigned int get_row_count(void)
{
    return s_row_size;
}

unsigned int get_column_count(void)
{
    return s_col_size;
}

int get_score(const color_t color)
{
    if (color == COLOR_WHITE) {
        return s_white_score;
    }
    else if (color == COLOR_BLACK) {
        return s_black_score;
    }
    return -1;
}

int get_color(const unsigned int row, const unsigned int col)
{
    if (s_board[row][col] == 'O') {
        return COLOR_BLACK;
    }
    else if (s_board[row][col] == 'X') {
        return COLOR_WHITE;
    }
    return -1;
}

int is_placeable(const unsigned int row, const unsigned int col)
{
    if (row < get_row_count() && col < get_column_count() && s_board[row][col] == EMPTY) {
        return TRUE;
    }
    return FALSE;
}

int place_stone(const color_t color, const unsigned int row, const unsigned int col)
{
    if ((color == COLOR_BLACK || color == COLOR_WHITE) && is_placeable(row, col)) {
        if (color == COLOR_BLACK) {
            s_board[row][col] = 'O'; /* BLACK */
        }
        else {
            s_board[row][col] = 'X'; /* WHITE */
        }
        update_score(color, row, col);
        return TRUE;
    }
    return FALSE;
}

void increase_row(void)
{
    ++s_row_size;
}

void decrease_row(void)
{
    --s_row_size;
}

void increase_column(void)
{
    ++s_col_size;
}

void decrease_column(void)
{
    --s_col_size;
}

void update_score(const color_t color, const unsigned int row, const unsigned int col)
{
    int score = 0;
    unsigned int horizontal_count = 0;
    unsigned int vertical_count = 0;
    unsigned int left_diagonal_count = 0;
    unsigned int right_diagonal_count = 0;

    count_horizontal_stone(color, row, col, &horizontal_count);
    count_vertical_stone(color, row, col, &vertical_count);
    count_left_diagonal_stone(color, row, col, &left_diagonal_count);
    count_right_diagonal_stone(color, row, col, &right_diagonal_count);


    if (horizontal_count >= 5) {
        score += horizontal_count - 4;
    }

    if (vertical_count >= 5) {
        score += vertical_count - 4;
    }

    if (left_diagonal_count >= 5) {
        score += left_diagonal_count - 4;
    }

    if (right_diagonal_count >= 5) {
        score += right_diagonal_count - 4;
    }

    if (color == COLOR_BLACK) {
        s_black_score += score;
    }
    else if (color == COLOR_WHITE) {
        s_white_score += score;
    }
}

void count_horizontal_stone(const color_t color, const unsigned int row, const unsigned int col, unsigned int* count)
{
    if (row > get_row_count()) {
        return;
    }

    if (color == get_color(row, col)) {
        (*count)++;
        count_left_stone_recursive(color, row - 1, col, count);
        count_right_stone_recursive(color, row + 1, col, count);
    }
}

void count_left_stone_recursive(const color_t color, const unsigned int row, const unsigned int col, unsigned int* count)
{
    if (row > get_row_count()) {
        return;
    }

    if (color == get_color(row, col)) {
        (*count)++;
        count_left_stone_recursive(color, row - 1, col, count);
    }
}

void count_right_stone_recursive(const color_t color, const unsigned int row, const unsigned int col, unsigned int* count)
{
    if (row > get_row_count()) {
        return;
    }

    if (color == get_color(row, col)) {
        (*count)++;
        count_right_stone_recursive(color, row + 1, col, count);
    }
}

void count_vertical_stone(const color_t color, const unsigned int row, const unsigned int col, unsigned int* count)
{
    if (col > get_column_count()) {
        return;
    }

    if (color == get_color(row, col)) {
        (*count)++;
        count_up_stone_recursive(color, row, col - 1, count);
        count_bottom_stone_recursive(color, row, col + 1, count);
    }
}

void count_up_stone_recursive(const color_t color, const unsigned int row, const unsigned int col, unsigned int* count)
{
    if (col > get_column_count()) {
        return;
    }

    if (color == get_color(row, col)) {
        (*count)++;
        count_up_stone_recursive(color, row, col - 1, count);
    }
}

void count_bottom_stone_recursive(const color_t color, const unsigned int row, const unsigned int col, unsigned int* count)
{
    if (col > get_column_count()) {
        return;
    }

    if (color == get_color(row, col)) {
        (*count)++;
        count_bottom_stone_recursive(color, row, col + 1, count);
    }
}

void count_left_diagonal_stone(const color_t color, const unsigned int row, const unsigned int col, unsigned int* count)
{
    if (row > get_row_count() || col > get_column_count()) {
        return;
    }

    if (color == get_color(row, col)) {
        (*count)++;
        count_left_up_stone_recursive(color, row - 1, col - 1, count);
        count_right_bottom_stone_recursive(color, row + 1, col + 1, count);
    }
}

void count_left_up_stone_recursive(const color_t color, const unsigned int row, const unsigned int col, unsigned int* count)
{
    if (row > get_row_count() || col > get_column_count()) {
        return;
    }

    if (color == get_color(row, col)) {
        (*count)++;
        count_left_up_stone_recursive(color, row - 1, col - 1, count);
    }
}

void count_right_bottom_stone_recursive(const color_t color, const unsigned int row, const unsigned int col, unsigned int* count)
{
    if (row > get_row_count() || col > get_column_count()) {
        return;
    }

    if (color == get_color(row, col)) {
        (*count)++;
        count_right_bottom_stone_recursive(color, row + 1, col + 1, count);
    }
}

void count_right_diagonal_stone(const color_t color, const unsigned int row, const unsigned int col, unsigned int* count)
{
    if (row > get_row_count() || col > get_column_count()) {
        return;
    }

    if (color == get_color(row, col)) {
        (*count)++;
        count_rihgt_up_stone_recursive(color, row + 1, col - 1, count);
        count_left_bottom_stone_recursive(color, row - 1, col + 1, count);
    }
}

void count_rihgt_up_stone_recursive(const color_t color, const unsigned int row, const unsigned int col, unsigned int* count)
{
    if (row > get_row_count() || col > get_column_count()) {
        return;
    }

    if (color == get_color(row, col)) {
        (*count)++;
        count_rihgt_up_stone_recursive(color, row + 1, col - 1, count);
    }
}

void count_left_bottom_stone_recursive(const color_t color, const unsigned int row, const unsigned int col, unsigned int* count)
{
    if (row > get_row_count() || col > get_column_count()) {
        return;
    }

    if (color == get_color(row, col)) {
        (*count)++;
        count_left_bottom_stone_recursive(color, row - 1, col + 1, count);
    }
}

int consume_score(const color_t color, const cost_t cost)
{
    if (get_score(color) >= cost) {
        if (color == COLOR_BLACK) {
            s_black_score -= cost;
        }
        else if (color == COLOR_WHITE) {
            s_white_score -= cost;
        }
        return TRUE;
    }
    return FALSE;
}

void display_board(void)
{
    unsigned int i;
    unsigned int j;
    printf("board size: %dx%d\n", get_row_count(), get_column_count());
    for (i = 0; i < get_row_count(); ++i) {
        for (j = 0; j < get_column_count(); ++j) {
            if (s_board[i][j] == EMPTY) {
                printf("%c", '-');
            }
            else {
                printf("%c", s_board[i][j]);
            }
        }
        printf("\n");
    }
}

int insert_row(const color_t color, const unsigned int row)
{
    if (get_row_count() >= MAX_SIZE) {
        return FALSE;
    }

    if (row <= get_row_count() && consume_score(color, COST_INSERT_ROW)) {
        unsigned int i;
        if (row == get_row_count()) {
            for (i = 0; i < get_column_count(); ++i) {
                s_board[row][i] = EMPTY;
            }

        }
        else {
            unsigned int j;
            i = get_row_count() - 1;
            while (row <= i && i < get_row_count()) {
                for (j = 0; j < get_column_count(); ++j) {
                    s_board[i + 1][j] = s_board[i][j];
                }
                --i;
            }

            for (i = 0; i < get_column_count(); ++i) {
                s_board[row][i] = EMPTY;
            }
        }

        increase_row();
        return TRUE;
    }
    return FALSE;
}

int insert_column(const color_t color, const unsigned int col)
{
    if (get_column_count() >= MAX_SIZE) {
        return FALSE;
    }

    if (col <= get_column_count() && consume_score(color, COST_INSERT_COLUMN)) {
        unsigned int i;
        if (col == get_column_count()) {
            for (i = 0; i < get_row_count(); ++i) {
                s_board[i][col] = EMPTY;
            }

        }
        else {
            unsigned int j;
            i = get_column_count() - 1;
            while (col <= i && i < get_column_count()) {
                for (j = 0; j < get_row_count(); ++j) {
                    s_board[j][i + 1] = s_board[j][i];
                }
                --i;
            }

            for (i = 0; i < get_row_count(); ++i) {
                s_board[i][col] = EMPTY;
            }
        }

        increase_column();
        return TRUE;
    }
    return FALSE;
}

int remove_row(const color_t color, const unsigned int row)
{
    if (get_row_count() <= MIN_SIZE) {
        return FALSE;
    }

    if (row < get_row_count() && consume_score(color, COST_REMOVE_ROW)) {
        unsigned int i;
        unsigned int j;

        for (i = row; i < get_row_count() - 1; ++i) {
            for (j = 0; j < get_column_count(); ++j) {
                s_board[i][j] = s_board[i + 1][j];
            }
        }

        decrease_row();
        return TRUE;
    }
    return FALSE;
}

int remove_column(const color_t color, const unsigned int col)
{
    if (get_column_count() <= MIN_SIZE) {
        return FALSE;
    }

    if (col < get_column_count() && consume_score(color, COST_REMOVE_COLUMN)) {
        unsigned int i;
        unsigned int j;

        for (i = col; i < get_column_count() - 1; ++i) {
            for (j = 0; j < get_row_count(); ++j) {
                s_board[j][i] = s_board[j][i + 1];
            }
        }

        decrease_column();
        return TRUE;
    }
    return FALSE;
}

int swap_rows(const color_t color, const unsigned int row0, const unsigned int row1)
{
    if (row0 < get_row_count() && row1 < get_row_count() && consume_score(color, COST_SWAP_ROW)) {
        unsigned int i;

        for (i = 0; i < get_column_count(); ++i) {
            int val = s_board[row0][i];
            s_board[row0][i] = s_board[row1][i];
            s_board[row1][i] = val;
        }
        return TRUE;
    }
    return FALSE;
}

int swap_columns(const color_t color, const unsigned int col0, const unsigned int col1)
{
    if (col0 < get_column_count() && col1 < get_column_count() && consume_score(color, COST_SWAP_COLUMN)) {
        unsigned int i;

        for (i = 0; i < get_row_count(); ++i) {
            int val = s_board[i][col0];
            s_board[i][col0] = s_board[i][col1];
            s_board[i][col1] = val;
        }
        return TRUE;
    }
    return FALSE;
}

int copy_row(const color_t color, const unsigned int src, const unsigned int dst)
{
    if (src < get_row_count() && dst < get_row_count() && consume_score(color, COST_COPY_ROW)) {
        unsigned int i;

        for (i = 0; i < get_column_count(); ++i) {
            s_board[dst][i] = s_board[src][i];
        }
        return TRUE;
    }
    return FALSE;
}

int copy_column(const color_t color, const unsigned int src, const unsigned int dst)
{
    if (src < get_column_count() && dst < get_column_count() && consume_score(color, COST_COPY_COLUMN)) {
        unsigned int i;

        for (i = 0; i < get_row_count(); ++i) {
            s_board[i][dst] = s_board[i][src];
        }
        return TRUE;
    }
    return FALSE;
}
