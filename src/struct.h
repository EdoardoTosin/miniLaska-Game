#ifndef STRUCT_H
#define STRUCT_H

struct Pedina{
    int team;
    char p;
    int rank;
};
/*
typedef struct Pedina* pedina_p;*/
struct Cella{
    int height;
    struct Pedina* piece;
};
/*
typedef struct Square*cella_c;*/

struct Board{
    struct Cella **mat;
};
typedef struct Board* BoardPointer;
/*
int partita=0;
int turno=1;
typedef struct Board board_b;*/

struct Posizione{
    int row;
    int col;
};
/*
typedef struct Posizione *posizione_p;*/

struct mossa{
    struct Posizione startPos;
    struct Posizione endPos;
};

/*
typedef struct mossa* mossa_m;*/

#endif
