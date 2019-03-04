#define  WROTE_CS356_IO 1
#include <HERA.h>
void HERA_main()
{

DLABEL(INPUT_STR)
LP_STRING("hello")

CBON()

SET(R2,INPUT_STR)
SET(R1,1)
CALL(FP_alt,print)

SET(R1,0)
SET(R2, 72)
CALL(FP_alt,putchar_ord)
SET(R2, 105)
CALL(FP_alt,putchar_ord)
HALT()


// putchar_ord function
//register 1 which terminal
//register 2 which character
LABEL(putchar_ord)
OPCODE(0b0010100000010010)
RETURN(FP_alt, PC_ret)
HALT()


//register 1 which terminal
//register 2 points to the string
LABEL(print)
MOVE(R9,FP_alt)
MOVE(R10,PC_ret)
MOVE(R3,R2)
LOAD(R4,0,R3) //R4 is the length of the string
BZ(empty_str) //if there is an empty string go to the end of the program
INC(R3,1) // increment pointer
// Now, pull in the next char of the actual string (into R2)
LABEL(Top_of_loop)
        // Load in current char into R2
        LOAD(R2, 0, R3)
        INC(R3,1)
        CALL(FP_alt,putchar_ord)
        DEC(R4, 1) // decrement the length
BNZ(Top_of_loop) // keep looping as long as the length is not zero
LABEL(empty_str)
RETURN(R9, R10)
HALT()


}
