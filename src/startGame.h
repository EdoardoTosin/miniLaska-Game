void createTable(square* board){
  const int dim = 7;
  int i, j;
	board = (square*) malloc (dim * dim * sizeof(square));
	for (i = 0; i < dim, i++){
		for (j = 0; j < dim, j++){
			if ((i%2==0 && j%2==0) || (i%2!=0 && j%2!=0)){
				if (i < 3)
					board(i * dim + j) = 1;
				else if (i == 3)
					board(i * dim + j) = NULL;
				else if (i > 3)
					board(i * dim + j) = 2;
			}
		}
	}
}
