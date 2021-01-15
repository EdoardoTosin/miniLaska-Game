#ifndef STRUCT_H
#define STRUCT_H

struct Pedina{
    int team;
    char p;
    int rank;
};
typedef struct Pedina* PedinaPointer;

struct Cella{
    int height;
    PedinaPointer piece;
};
typedef struct Cella** BoardPointer;

struct Posizione{
    int row;
    int col;
};
typedef struct Posizione* PosizionePointer;

struct mossa{
    PosizionePointer startPos;
    PosizionePointer endPos;
};
typedef struct mossa* MossaPointer;

#endif
