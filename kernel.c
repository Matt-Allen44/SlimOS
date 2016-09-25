/* kernel.c */

/* Function Declerations */
char* interruptsEnabled();
int clearScreen();
int print();
int println();
int wait();
char* getKeyCharFromScanCode(unsigned int scancode);
static __inline unsigned char inb(unsigned short int port);
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
  print("SlimOS > ", MAGENTA);
  println("Cleared Screen", BLACK);

  print("SlimOS > ", MAGENTA);
  print(inb(0x04), BLACK);
  print(inb(0x02), BLACK);
  print(inb(0x00), BLACK);

  print("SlimOS > ", MAGENTA);
  print("IRQ Supported: ", BLACK);
  println(interruptsEnabled(), BLACK);

  print("SlimOS > WAITING ", MAGENTA);

  unsigned char lastChar;
  unsigned char currChar;
  while(1==1){
    currChar = inb(0x60);
    if(currChar != lastChar){
      lastChar = currChar;
      print(getKeyCharFromScanCode(currChar), BLACK);
      print(" ", BLACK);

      if(currChar == 0x3B){
        clearScreen();
        print("SlimOS > ", MAGENTA);
      }
    }
  }

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

char *getKeyCharFromScanCode(unsigned int scancode){
  if(scancode == 0x02){
    return "1";
  } else if (scancode == 0x03){
    return "2";
  } else if (scancode == 0x04){
    return "3";
  } else if (scancode == 0x05){
    return "4";
  } else if (scancode == 0x06){
    return "5";
  } else if (scancode == 0x07){
    return "6";
  } else if (scancode == 0x08){
    return "7";
  } else if (scancode == 0x09){
    return "8";
  } else if (scancode == 0x0A){
    return "9";
  } else if (scancode == 0x0B){
    return "0";
  } else if (scancode == 0x0C){
    return "-";
  } else if (scancode == 0x0D){
    return "=";
  } else if (scancode == 0x0E){
    return "BACKSPACE";
  } else if (scancode == 0x0F){
    return "TAB";
  } else if(scancode == 0x10){
    return "Q";
  } else if(scancode == 0x11){
    return "W";
  } else if(scancode == 0x12){
    return "E";
  } else if (scancode == 0x13){
    return "R";
  } else if (scancode == 0x14){
    return "T";
  } else if (scancode == 0x15){
    return "Y";
  } else if (scancode == 0x16){
    return "U";
  } else if (scancode == 0x17){
    return "I";
  } else if (scancode == 0x18){
    return "O";
  } else if (scancode == 0x19){
    return "P";
  } else if (scancode == 0x1A){
    return "[";
  } else if (scancode == 0x1B){
    return "]";
  } else if (scancode == 0x1C){
    return "ENTER";
  } else if (scancode == 0x1D){
    return "LCTRL";
  } else if (scancode == 0x1E){
    return "A";
  } else if (scancode == 0x1F){
    return "S";
  } else if(scancode == 0x20){
    return "D";
  } else if(scancode == 0x21){
    return "F";
  } else if(scancode == 0x22){
    return "G";
  } else if (scancode == 0x23){
    return "H";
  } else if (scancode == 0x24){
    return "J";
  } else if (scancode == 0x25){
    return "K";
  } else if (scancode == 0x26){
    return "L";
  } else if (scancode == 0x27){
    return ";";
  } else if (scancode == 0x28){
    return "'";
  } else if (scancode == 0x29){
    return "`";
  } else if (scancode == 0x2A){
    return "LSHIFT";
  } else if (scancode == 0x2B){
    return "\\";
  } else if (scancode == 0x2C){
    return "Z";
  } else if (scancode == 0x2D){
    return "X";
  } else if (scancode == 0x2E){
    return "C";
  } else if (scancode == 0x2F){
    return "V";
  } else if(scancode == 0x30){
    return "B";
  } else if(scancode == 0x31){
    return "N";
  } else if(scancode == 0x32){
    return "M";
  } else if (scancode == 0x33){
    return ",";
  } else if (scancode == 0x34){
    return ".";
  } else if (scancode == 0x35){
    return "/";
  } else if (scancode == 0x36){
    return "RSHIFT";
  } else if (scancode == 0x37){
    return "*";
  } else if (scancode == 0x38){
    return "LALT";
  } else if (scancode == 0x39){
    return "SPACE";
  } else if (scancode == 0x3A){
    return "CAPS";
  } else if (scancode == 0x3B){
    return "F1";
  } else if (scancode == 0x3C){
    return "F2";
  } else if (scancode == 0x3D){
    return "F3";
  } else if (scancode == 0x3E){
    return "F4";
  } else if (scancode == 0x3F){
    return "F5";
  } else if(scancode == 0x40){
    return "F6";
  } else if(scancode == 0x41){
    return "F7";
  } else if(scancode == 0x42){
    return "F8";
  } else if (scancode == 0x43){
    return "F9";
  } else if (scancode == 0x44){
    return "F10";
  } else if (scancode == 0x45){
    return "NUMLOCK";
  } else if (scancode == 0x46){
    return "SCROLLLOCK";
  }
  return "";
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

static __inline unsigned char inb (unsigned short int port)
{
  unsigned char _v;

  __asm__ __volatile__ ("inb %w1,%0":"=a" (_v):"Nd" (port));
  return _v;
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

int wait(){
}
