#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>

#define MEMORY_SIZE 65536
#define HALT 0x19
#define NOP 0x18

void fetchNextInstruction();
void executeInstruction();

unsigned int PC = 0;   // Program Counter
unsigned int MAR = 0;  // Memory Address Register
unsigned int operand = 0;
unsigned int oldPC;    // Old Program Counter 
unsigned int IR = 0;    // Instruction Register
unsigned int ACC = 0;   // Accumulator



uint8_t memory[MEMORY_SIZE] = {0};

int main(){
  char hex_line[256];
  int i = 0;

  FILE *memory_read = fopen("memory_in.txt", "r");
  if(memory_read == NULL){
    perror("Faild to open memory_in.txt");
    return EXIT_FAILURE;
  }

  while(fgets(hex_line, sizeof(hex_line), memory_read) != NULL){
    char *token = strtok(hex_line, " ");
    while(token != NULL){
      unsigned int hex_value;
      sscanf(token, "%x", &hex_value);
      if(i < MEMORY_SIZE){
        memory[i++] = (uint8_t)hex_value;
      }
      
      token = strtok(NULL, " ");
    }
  }
  fclose(memory_read);

  while(PC < MEMORY_SIZE && memory[PC] != HALT){
    fetchNextInstruction();
    executeInstruction();
  }

  FILE *file_output = fopen("memory_out.txt", "w");
  if(file_output == NULL){
    perror("failed to open memory_out.txt");
    return EXIT_FAILURE;
  }
  
  for(unsigned int i = 0; i < MEMORY_SIZE;){
    for(int j = 0; j < 16 && i < MEMORY_SIZE; j++){
      fprintf(file_output, "%02x ", memory[i++]);
    }
    fprintf(file_output, "\n");
  }
  
  return 0;
}

void fetchNextInstruction(){
  IR = memory[PC];
  oldPC = PC;
  PC++;
  
  if(IR & 0x80){
    switch(IR & 0x0c){
      case 0x00:
        switch(IR & 0x03){
          case 0:
            break;
          case 1:
            break;
          case 2:
            PC++;
            break;
          case 3:
            PC += 2;
            break;
          default:
            break;
        }
        break;
      case 0x04:
        switch(IR & 0x03){
          case 0:
            break;
          case 1:
            break;
          case 2:
            PC++;
            break;
          case 3:
            PC += 2;
            break;
          default:
            break;
        }
        break;
      case 0x08:
        switch(IR & 0x03){
          case 0:
            break;
          case 1:
            break;
          case 2:
            PC += 2;
            break;
          case 3:
          PC += 2;
            break;
          default:
            break;
        }
        break;
      case 0x0c:
        switch(IR & 0x03){
          case 0:
            PC += 2;
            break;
          case 1:
            PC += 2;
            break;
          case 2:
            PC += 3;
            break;
          case 3:
            PC += 4;
            break;
          default:
            break;
        }
        break;
      default:
        break;
    }
  }else if((IR & 0xf0)== 0){
    switch(IR & 0x7){
      case 0:
        PC += 2;
        break;
      case 1:
        PC++;
        break;
      case 2:
        break;
      case 3:
        PC += 2;
        break;
      case 4:
        PC += 2;
        break;
      default:
        break;
    }
  }else if((IR & 0xf8) == 0x10){
    PC += 2;
  }

  operand = PC - oldPC- 1;
  PC &= 0xffff;
}

void executeInstruction(){
  int addr;

  if ((IR & 0x80) == 0x80){
    int dest, src;

    switch(IR & 0x0c){
      case 0x00:
        dest = memory[MAR];
        break;
      case 0x04:
        dest = ACC;
        break;
      case 0x08:
        dest = MAR;
        break;
      case 0x0c:
        dest = memory[((memory[oldPC + 1] << 8) + memory[oldPC + 2])];
        break;
      default:
        break;
    }

    switch(IR & 0x03){
      case 0x00:
        src = memory[MAR];
        break;
      case 0x01:
        src = ACC;
        break;
      case 0x02:
        if((IR & 0x0c) == 0x08){
          src = memory[((memory[oldPC - 2] << 8) + memory[oldPC - 1])];
        }else{
          src = memory[PC - 1];
        }
        break;
      case 0x03:
        if((IR & 0x0c) == 0x08){
          addr = ((memory[oldPC + 1] << 8) + memory[oldPC +2]);
          src =  ((memory[oldPC + 1] << 8) + memory[oldPC + 2]);
        }else{
          src = memory[((memory[oldPC + 1] << 8) + memory[oldPC + 2])];
        }
        break;
      default:
        break;
    }

    switch(IR & 0x70){
      case 0x00:
        dest &= src;
        break;
      case 0x10:
        dest |= src;
        break;
      case 0x20:
        dest ^= src;
        break;
      case 0x30:
        dest += src;
        break;
      case 0x40:
        dest -= src;
        break;
      case 0x50:
        dest++;
        break;
      case 0x60:
        dest--;
        break;
      case 0x70:
        dest = !dest;
        break;
      deafult:
        break;
    }

    switch(IR & 0x0c){
      case 0x00:
        memory[MAR] = dest & 0xff;
        break;
      case 0x04:
        ACC = dest & 0xff;
        break;
      case 0x08:
        MAR = dest & 0xffff;
        break;
      case 0x0c:
        memory[((memory[oldPC + 1] << 8) + memory[oldPC + 2])] = dest & 0xff;
        break;
      default:
        break;
    }
  }else if((IR & 0xf0)== 0){
    if((IR &0x08) == 0){
      if((IR & 0x04) == 0){
        switch(IR & 0x03){
          case 0:
            memory[((memory[oldPC + 1] << 8) + memory[oldPC +2])] = ACC;
            break;
          case 1:
            break;
          case 2:
            memory[MAR] = ACC;
            break;
          default:
            break;
        }
      }else{
        switch(IR & 0x03){
          case 0:
            memory[((memory[oldPC + 1] << 8) + memory[oldPC + 2])] = (MAR >> 8) & 0xff;
            memory[((memory[oldPC + 1] << 8) + memory[oldPC + 2]) + 1] = MAR & 0xff;
            break;
          case 1:
            break;
          case 2:
            memory[MAR] = (MAR >> 8) & 0xff;
            memory[MAR + 1] = MAR & 0xff;
            break;
          default:
            break;
        }
      } 
    }else{
      if((IR & 0x04) == 0){
        switch(IR & 0x03){
          case 0:
            ACC = memory[((memory[oldPC + 1] << 8) + memory[oldPC + 2])];
            break;
          case 1:
            ACC = memory[oldPC + 1];
            break;
          case 2:
            ACC = memory[MAR];
            break;
          default:
            break;
        }
      }else{
        int temp;
        temp = MAR;

        switch(IR & 0x03){
          case 0:
            MAR = memory[((memory[oldPC + 1] << 8) + memory[oldPC + 2])];
						MAR <<= 8;
						MAR += memory[((memory[oldPC + 1] << 8) + memory[oldPC + 2]) + 1];
            break;
          case 1:
						MAR = memory[oldPC + 1];
						MAR <<= 8;
						MAR += memory[oldPC + 2];
            break;
          case 2:
            MAR = memory[temp];
						MAR <<= 8;
						MAR += memory[temp + 1];
            break;
          default:
            break;
        }
      }
    }
  }else if((IR & 0xF8) == 0x10){
    addr = (memory[oldPC + 1] << 8) + memory[oldPC + 2];

    switch(IR & 0x07){
      case 0:
        PC = addr;
        break;
      case 1:
        if(ACC == 0){
          PC = addr;
        }
        break;
      case 2:
        if(ACC != 0){
          PC = addr;
        }
        break;
      case 3:
        if((ACC & 0x80) != 0){
          PC = addr;
        }
        break;
      case 4:
        if(((ACC & 0x80) != 0) || (ACC == 0)){
          PC = addr;
        }
        break;
      case 5:
        if(((ACC &0x80) == 0) || (ACC == 0)){
          PC = addr;
        }
        break;
      case 6:
        if((ACC & 0x80) == 0){
          PC = addr;
        }
        break;
      default:
        break;
    }
  }else{
    if(IR == NOP){
     //do nothing
    }else if(IR == HALT){
      return;
    }
  }
}
