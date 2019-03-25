# HARDWARE
There are 2 keyboards (labeled as 1 and 2), as well as 2 Terminals on the Main screen. Rather than opting for a memory-mapped design, we created two new opcodes, one to read a character from a terminal and another to write a character to a display. For the putchar operation, our opcode is represented by bits 10-15 as 001010; for getchar, these bits are 001011. Bits 4-7 determine which register to read to decide which keyboard / display to use and bits 0-3 determine which register to read a character from / write a character to.

The keyboards are Enabled via a subcircuit that determines whether the opcode matches a getchar operation (bits 10-15); another ‘Which Terminal/Board?’ subcircuit determines which keyboard the processor should pull character data from, as well as which terminal the characters/string should be printed out to (bits 0-3). 

The getchar input then travels into the ALSU subcircuit, which essentially computes various operations (arithmetic / bit / shift, etc) and selects the Final Result (and Final Flags), based on the Operation Select. If a getchar operation is detected, the bit-extended ASCII character code is the Final Result computed by the ALSU subcircuit. We chose to have the getchar data be routed to the ALSU simply for ease of use with the existing microprocessor (see below for more info). 

This output becomes Write Data #1 into the Register File. Write Address #1 was already wired to always read bits 0-3, which represents the register where the character will be stored. If we are using Keyboard 2 (store entire newline-terminated string in memory), we perform an extra step: after storing the char in the specified register, we store that character in RAM (starting at memory address 0xd000). We chose this location because we felt that it was far enough after location 0xc000, which is HERA’s default LPSTRING and ldata starts being written. 

For putchar, the Register File’s Read Address #2 is wired to always pull from the register specified by opcode bits 0-3. As a reminder, this register holds the character data. Meanwhile, Read Address #1 is always bits 4-7, which specifies the register that contains the Terminal Number to which we want to print that character out to. Finally, Read Data #2 outputs the bit-extended ASCII character code, which is linked to both Terminals. The correct terminal is Enabled by the same subcircuit that enables the keyboards. How this behavior works for printing chars immediately, versus printing the entire string after a newline is entered, is specified in the Software section below. 


# SOFTWARE
For Keyboard 1, we get the characters inputted using the function getchar_ord and we output it directly to Terminal 1 using putchar_ord. As for Keyboard 2, we get the whole string until we hit a newline and we output it to Terminal 2. For the second case, we used a location in memory where we store the length of the string and each character in the string to output it at once into the terminal using putchar_ord.

To print to the terminal, we use a function that we defined as print. This function takes a length prefixed string stored in register 2 and prints it to the terminal indicated by register 1. We first check that the string’s length L is greater than 0. Then, we use a loop that loops L times to load in each character into register 2 and use putchar_ord to output it.

Both putchar_ord and getchar_ord are using an opcode that we used to implement the hardware part (Please refer to Hardware for more details).

To simulate the polling technique, we used a loop that checks if Keyboard1 has a character and outputs it, then checks Keyboard2. To simulate the operating system, we have a loop that does nothing twenty or so times, but we have commented it out of the program since the program already seems slow enough.
