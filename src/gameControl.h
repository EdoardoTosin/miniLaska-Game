void promozione(struct Pedina *pedina,int i);

int get_altezza(BoardPointer board,int i, int j);

int get_team(BoardPointer board,int i,int j);

int get_grado(BoardPointer board,int i,int j);

bool cella_vuota(BoardPointer board,int i, int j);

void print_mosse(struct mossa *mosse, int dim);

int avanzamento(BoardPointer board,struct mossa *mosse,int turno);

void svuota_cella(BoardPointer board, int i, int j);

void spostamento_soldato(BoardPointer board,struct mossa mosse);

void spostamento_mangiata(BoardPointer board,struct mossa mosse);

/*
void vincente(BoardPointer board);
*/
