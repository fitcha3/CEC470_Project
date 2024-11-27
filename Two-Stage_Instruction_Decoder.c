#define HALT_OPCODE 0x19

void fetchNextInstruction(void);
void executeInstruction(void);

unsigned char memory[65536];
unsigned char ACC=0;
unsigned char IR=0;
unsigned int MAR=0;
unsigned int PC=0;
unsigned int Last_PC;

int _tmain(int argc, char* argv[])
{

//Sample data
    memory[0] = 0x08;
    memory[1] = 0x10;
    memory[2] = 0x00;
    memory[3] = 0xb7;
    memory[4] = 0x10;
    memory[5] = 0x01;
    memory[6] = 0xb7;
    memory[7] = 0x10;
    memory[8] = 0x02;
    memory[9] = 0xa6;
    memory[10] = 0xff;
    memory[11] = 0xd4;
    memory[12] = 0x00;
    memory[13] = 0x10;
    memory[14] = 0x03;
    memory[15] = 0x19;

// Execution loop. Continue fetching and executing
// unitl PC points to a HALT instruction

    while(memory[PC] != HALT_OPCODE)
    {
        fetchNextInstruction();
        executeInstruciton();
    }
    return 0;
}

void fetchNextInstruction()
{
    IR = memory[PC]; //Fetch at PC
    Last_PC = PC;
    PC = PC+1;
    if (IR && memory[0]){
switch(IR && 0x0C){
    case 0x00:
        shitch(IR && ){
            case 0:
            break;
                
            case 2:
            PC=PC+1;
            break;
                
            case3 :
            PC = PC + 2;
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
			PC = PC + 2;
			break;
			case 3: 
			PC= PC + 2;
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
	PC = PC + 1;
	break;
	    
	case 3:
	PC = PC + 2;
	break;
	    
	default:
	break;
				}
    break;
    
    case 0x0C:
switch(IR & 0x03){ 
			case 0:
	    	PC = PC + 2;
			break;
	
			case 1:
			PC = PC + 2;
			break;
	
			case 2:
			PC = PC + 3;
			break;
	
			case 3:
			PC = PC + 4;
			break;
	
	 default:
         break;
			}
    break;

    default:.
    break;
    }
    else if((IR & 0xf0) == 0){ 
	switch(IR & 0x7){
	case 0: 
	PC = PC + 2;
	break;
		
	case 1:
	PC = PC + 1;
	break;
		
	case 2:
	break;
		
	case 4:
	PC = PC + 2;
	break;
		
	case 5:
	PC = PC + 2;
	break;
		
	case 6:
	break;
		
	default:
	break;
		}
	}
}

void executeInstruciton()
{
int location;
int destination;
int source;

	
}
