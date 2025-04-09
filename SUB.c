/*
 * Author: Ol' Jim
 * Date: 06/13/2012
 * ByteForge Systems
 * MIPS-Translatron 3000
 */

 #include "Instruction.h"

 // Function to encode the "SUB" (Subtract) instruction for registers into binary
 void sub_reg_assm(void) {
	 // Check if the operation code is "SUB"
	 // strcmp(string1, string2) returns 0 if the strings match
	 if (strcmp(OP_CODE, "SUB") != 0) {
		 // If the op code doesn't match, this isn't the correct command
		 state = WRONG_COMMAND;
		 return; 
	 }
 
	 /*
	  * Checking the type of parameters
	  */
 
	 // All parameters must be registers for SUB
	 if (PARAM1.type != REGISTER || PARAM2.type != REGISTER || PARAM3.type != REGISTER) {
		 state = INVALID_PARAM;  // Set state to INVALID_PARAM if any parameter is incorrect
		 return;
	 }
 
	 /*
	  * Checking the value of parameters
	  */
 
	 // All register values must be between 0 and 31 (valid register range for MIPS)
	 if (PARAM1.value > 31 || PARAM2.value > 31 || PARAM3.value > 31) {
		 state = INVALID_REG;  // Set state to INVALID_REG if any register value is out of range
		 return;
	 }
 
	 /*
	  * Putting the binary together
	  */
 
	 // Set the opcode for R-type (SUB is an R-type instruction, so the opcode is all zeroes)
	 setBits_str(31, "000000");
 
	 // Set Rs, Rt, and Rd register values
	 setBits_num(25, PARAM2.value, 5);  // Rs register (first source operand)
	 setBits_num(20, PARAM3.value, 5);  // Rt register (second source operand)
	 setBits_num(15, PARAM1.value, 5);  // Rd register (destination for result)
 
	 // Set shift amount (shamt) to 0 since it's not used in the SUB instruction
	 setBits_str(10, "00000");
 
	 // Set funct code for SUB (in binary)
	 setBits_str(5, "100010");
 
	 // Let the system know the encoding is complete
	 state = COMPLETE_ENCODE;
 }
 
 // Function to decode the "SUB" instruction from binary to assembly
 void sub_reg_bin(void) {
	 // Check if the opcode and funct code match the "SUB" instruction
	 if (checkBits(31, "000000") != 0 || checkBits(5, "100010") != 0) {
		 state = WRONG_COMMAND;  // Set state to WRONG_COMMAND if the opcode and funct code do not match
		 return;
	 }
 
	 /*
	  * Finding values in the binary instruction
	  */
 
	 // Extract Rs, Rt, and Rd register values from the binary instruction
	 uint32_t Rs = getBits(25, 5);  // Extract Rs (first source operand)
	 uint32_t Rt = getBits(20, 5);  // Extract Rt (second source operand)
	 uint32_t Rd = getBits(15, 5);  // Extract Rd (destination operand)
 
	 /*
	  * Setting Instruction values for assembly
	  */
 
	 setOp("SUB");  // Set operation to SUB
	 setParam(1, REGISTER, Rd);  // Set the destination register (Rd)
	 setParam(2, REGISTER, Rs);  // Set the first source register (Rs)
	 setParam(3, REGISTER, Rt);  // Set the second source register (Rt)
 
	 // Let the system know the decoding is complete
	 state = COMPLETE_DECODE;
 }
 