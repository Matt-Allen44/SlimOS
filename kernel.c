/* kernel.c */

/* Function Declerations */
char* interruptsEnabled();
int clearScreen();
int print();
int println();
/* End of Declerations *

/* Start Of Colors */
const int BLACK = 0x70;
const int BLUE = 0x71;
const int GREEN = 0x72;
const int CYAN = 0x73;
const int RED = 0x74;
const int MAGENTA = 0x75;
const int BROWN = 0x76;
const int GREY = 0x77;
const int GRAY = 0x78;
/* End Of Colors */


char *VideoMemPointer = (char*)0xb8000; //Pointer for the beggining of the video memory
unsigned int i = 0;

void smain(void){
  clearScreen();

  int loop = 0;
  print("SlimOS > ", BLUE);
  println("Cleared Screen", BLACK);

  print("SlimOS > ", BLUE);
  print("IRQ Supported: ", BLACK);
  println(interruptsEnabled(), BLACK);

  return;
}

char* interruptsEnabled(){
  unsigned long flags;
  asm volatile (  "pushf\n\t"
                  "pop %0"
                  : "=g"(flags));

  if(flags & (1 << 9)){
    return "TRUE";
  } else {
    return "FALSE";
  }
}

int clearScreen(){
  unsigned int j = 0;

  /* loop through all of video memory and clear it */
  while(j < 80*25*2){
    VideoMemPointer[j] = ' ';
    VideoMemPointer[j+1] = 0x72;
    j = j + 2; //increment to next section of screen (as 2 bytes per section)
  }
  j = 0;
  i = 0;
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


/*  COLORS TABLE
    0 - Black, 1 - Blue, 2 - Green, 3 - Cyan, 4 - Red, 5 - Magenta, 6 - Brown
    7 - Light Grey, 8 - Dark Grey, 9 - Light Blue, 10/a - Light Green, 11/b - Light Cyan
    12/c - Light Red, 13/d - Light Magenta, 14/e - Light Brown, 15/f – White.
*/
int println(char *str, unsigned int col){
  print(str, col);

  int bytesInALine = 160;
  i = bytesInALine * (i/bytesInALine) + bytesInALine;
}
