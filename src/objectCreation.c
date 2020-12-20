#include "objectCreation.h"

struct Pedina{
    //enum colore colore;
    int team;
    char p;
    int grado;
};
//typedef struct Pedina* pedina_p;
struct Cella{
    int height;
    struct Pedina* pedina;
};

//typedef struct Square*cella_c;

struct Board{
    struct Cella **mat;
};

typedef struct Board* BoardPointer;
//int partita=0;
//int turno=1;
//typedef struct Board board_b;

struct Posizione{
    int riga;
    int colonna;
};
//typedef struct Posizione *posizione_p;

struct mossa{
    struct Posizione posizioneattuale;
    struct Posizione posizionearrivo;
};
//typedef struct mossa* mossa_m;
