/* kernel.c */
int clearScreen();
int print();
int printLn();

char *VideoMemPointer = (char*)0xb8000; //Pointer for the beggining of the video memory
unsigned int i = 0;

void smain(void){
  clearScreen();

  print("SlimOS > ", 0x04);
  printLn("Cleared Screen", 0x03);
  return;
}

int clearScreen(){
  unsigned int j = 0;

  /* loop through all of video memory and clear it */
  while(j < 80*25*2){
    VideoMemPointer[j] = ' ';
    VideoMemPointer[j+1] = 0x07;
    j= j + 2; //increment to next section of screen (as 2 bytes per section)
  }
  j=0;
}

int print(char *str, unsigned int col){
  unsigned int j = 0;

  while(str[j] != '\0'){
    /* get character from string and copy to video memory */
    VideoMemPointer[i] = str[j];
    /* set characters colour to green */
    VideoMemPointer[i+1] = col;
    j = j+1;
    i = i+2;
  }
}

int printLn(char *str, unsigned int col){
  print(str, col);

  int bytesInALine = 160;
  i = bytesInALine * (i/bytesInALine) + bytesInALine;
}
