void clear_console(){
  system(“clear”);
}

void table_out(int* board){ /*Creazione output grafico nel terminale*/
  int i, j;
	for (i = 0; i < 7; i++){
		for (j = 0; j < 7; j++){
			if (i%2==0 && j%2==0)
				printf("%c",board(i * dim + j));
			else if (i%2!=0 && j%2!=0)
				printf("%c",board(i * dim + j));
      else
        printf(" ");
		}
	}
	return;
}
