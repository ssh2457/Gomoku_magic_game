#ifndef COST_H
#define COST_H

typedef enum cost {
    COST_INSERT_ROW = 3,
    COST_INSERT_COLUMN = 3,
    COST_REMOVE_ROW = 3,
    COST_REMOVE_COLUMN = 3,
    COST_SWAP_ROW = 2,
    COST_SWAP_COLUMN = 2,
    COST_COPY_ROW = 4,
    COST_COPY_COLUMN = 4
} cost_t;

#endif /* COST_H */
