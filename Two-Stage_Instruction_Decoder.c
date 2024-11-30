/*
 * CEC 470: 
 * Computer Architecture
 * 
 * Author: 
 * Adam P. Fitch
 * Michael Harrison
 * Jonathan Legro
 *
 * Date: 
 * November 30, 2024
 * 
 * CEC 470 Project: 
 * Two-Stage Instruction Decoder
 * 
 * Description: 
 * This project involves designing a simple processor simulator with 
 * two key functions in C: fetchNextInstruction() and executeInstruction().
 * 
 * References: 
 * https://stackoverflow.com/questions/4494170/grouping-switch-statement-cases-together
 * 
 */

#define HALT_OPCODE 0x19

void fetchNextInstruction(void);
void executeInstruction(void);

unsigned char memory[65536];
unsigned char ACC = 0;
unsigned char IR = 0;
unsigned int MAR = 0;
unsigned int PC = 0;
unsigned int Last_PC;

int _tmain(int argc, char *argv[])
{ 
	// Sample Data (program in memory)
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
	memory[15] = HALT_OPCODE;

	// Execution loop.
	// Continue fetching and executing until 
	// PC points to a HALT instruction.

	while (memory[PC] != HALT_OPCODE)
	{
		fetchNextInstruction();
        executeInstruction();
	}

	printf("Program Halted\n");
	return 0;
}

void fetchNextInstruction()
{
	IR = memory[PC]; // Fetch at PC
	Last_PC = PC;
	PC += 1;

	// Check if the instruction is a branch instruction
	if (IR & 0x80)
	{
		switch (IR & 0x0C)
		{
		case 0x00:
			PC += (IR & 0x03);
			break;

		case 0x04:
			switch (IR & 0x03)
			{
			case 0:
			case 1:
				break;
			case 2:
			case 3:
				PC += 2;
				break;
			default:
            printf("Unhandled instruction: 0x%02X\n", IR);
				break;
			}
			break;

		case 0x08:
			switch (IR & 0x03)
			{
			case 0:
            case 1:
				break;

			case 2:
				PC += 1;
				break;

			case 3:
				PC += 2;
				break;

			default:
            printf("Unhandled instruction: 0x%02X\n", IR);
				break;
			}
			break;

		case 0x0C:
            switch (IR & 0x03)
            {
            case 0:
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
                printf("Unhandled instruction: 0x%02X\n", IR);
                break;
			}
			break;

		default:
            printf("Unhandled instruction: 0x%02X\n", IR);
			break;
		}
		//Determine size of instruction
		if ((IR & 0xF0) == 0) //Memory operation
		{
            switch (IR & 0x0F)
            {
            case 0:
            case 1:
            case 4:
            case 5:
            case 8:
            case 9:
            case 12:
            case 13:
                PC += 2;
                break;

            case 2:
            case 6:
            case 10:
            case 14:
                PC += 3;
                break;

            case 3:
            case 7:
            case 11:
            case 15:
                PC += 4;
                break;

            default:
                printf("Unhandled instruction: 0x%02X\n", IR);
                break;
            }
		}
		else //Register operation
		{
            switch (IR & 0x7)
            {
            case 0:
            case 4:
            case 5:
                PC += 2;
                break;

            case 1:
                PC += 1;
                break;

            case 2:
            case 6:
                break;

            default:
                printf("Unhandled instruction: 0x%02X\n", IR);
                break;
            }
			}
		}
	}

void executeInstruction()
{
    unsigned char opcode = IR & 0xF0;
    unsigned char operand = IR & 0x0F;

    switch (opcode)
    {
    case 0x00: // Memory operations
        switch (operand)
        {
        case 0x00: // Load ACC from memory
            ACC = memory[MAR];
            break;
        case 0x01: // Store ACC to memory
            memory[MAR] = ACC;
            break;
        case 0x02: // Load ACC from immediate value
            ACC = memory[PC];
            PC += 1;
            break;
        case 0x03: // Store ACC to immediate address
            memory[memory[PC]] = ACC;
            PC += 1;
            break;
        default:
            printf("Unhandled memory operation: 0x%02X\n", operand);
            break;
        }
        break;

    case 0x10: // Register operations
        switch (operand)
        {
        case 0x00: // Clear ACC
            ACC = 0;
            break;
        case 0x01: // Increment ACC
            ACC += 1;
            break;
        case 0x02: // Decrement ACC
            ACC -= 1;
            break;
        case 0x03: // Add immediate to ACC
            ACC += memory[PC];
            PC += 1;
            break;
        default:
            printf("Unhandled register operation: 0x%02X\n", operand);
            break;
        }
        break;

    default:
        printf("Unhandled opcode: 0x%02X\n", opcode);
        break;
    }
}
