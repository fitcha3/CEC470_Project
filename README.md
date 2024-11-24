# CEC470_Project: Two-Stage Instruction Decoder
## This project involves designing a simple processor simulator with two key functions in C: fetchNextInstruction() and executeInstruction().

### Simulate a two-step instruction cycle: 
    Fetch: Retrieve instructions from memory using the program counter (PC).
    Execute: Perform operations based on the current instruction.

### Use global variables for registers:
    PC (Program Counter): Tracks the next instruction.
    IR (Instruction Register): Holds the current instruction.
    MAR (Memory Address Register): Stores memory addresses.
    ACC (Accumulator): Used for operations.

### Simulate memory with an array: memory[65536].

### Support a basic instruction set, including:
    Mathematical operations (e.g., ADD, XOR).
    Memory operations (e.g., LOAD, STOR).
    Branches/Jumps.
    Special instructions:
    NOP (No operation).
    Halt (Stop execution).

### Write C code for the two functions:
    fetchNextInstruction(): Fetch the next instruction and update the program counter.
    executeInstruction(): Decode and execute the current instruction.

### Answer four provided questions about the instruction set and simulator features.

### Deliverables:
    C code for fetchNextInstruction() and executeInstruction().
    Answers to the four questions.
