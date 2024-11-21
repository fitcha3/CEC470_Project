#define HALT_OPCODE 0x19

void fetchNextInstruction(void);
void executeInstruction(void);

unsigned char memory[65536];
unsigned char ACC=0;
unsigned char IR=0;
unsigned int MAR=0;
unsigned int PC=0;

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
}

void fetchNextInstruction()
{
    IR = memory[PC]; //Fetch at PC
}

void executeInstruciton()
{

}