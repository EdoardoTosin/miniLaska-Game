# :red_circle: miniLaska Game :white_circle:

#### Clone our repository, compile and run

`$ git clone https://github.com/EdoardoTosin/miniLaska-Game`
`$ cd /miniLaska-Game/src/`
`$ make`
`$ ./miniLaska`

#### Main Function
```c
int main() {
  char start='0';
  do{
    system("clear");
    printf("\nminiLaska GAME\n\nPress F to start the game\n\n");
    scanf(" %c", &start);
  } while(start!='f' && start!='F');
  do{
    match();
    printf("Do you want to play again? (y for yes)\n\n");
    scanf(" %c", &start);
  } while(start=='y' && start=='Y');
  return 0;
}
```
