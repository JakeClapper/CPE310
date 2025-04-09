/*
 * Author: Ol' Jim
 * Date: 06/13/2012
 * ByteForge Systems
 * MIPS-Translatron 3000
 */

 #include "Instruction.h"

 // Function to encode the "SW" (Store Word) instruction into binary
 void sw_immd_assm(void) {
	 // Check if the operation code is "SW"
	 if (strcmp(OP_CODE, "SW") != 0) {
		 state = WRONG_COMMAND;  // If not, set state to WRONG_COMMAND
		 return;
	 }
 
	 /*
	  * Checking parameter types
	  */
 
	 // First parameter should be a register (Rt)
	 if (PARAM1.type != REGISTER) {
		 state = MISSING_REG;  // If Rt is not a register, set state to MISSING_REG
		 return;
	 }
 
	 // Second parameter should be a register (Rs)
	 if (PARAM2.type != REGISTER) {
		 state = MISSING_REG;  // If Rs is not a register, set state to MISSING_REG
		 return;
	 }
 
	 // Third parameter should be an immediate (offset)
	 if (PARAM3.type != IMMEDIATE) {
		 state = INVALID_PARAM;  // If offset is not immediate, set state to INVALID_PARAM
		 return;
	 }
 
	 /*
	  * Checking parameter values
	  */
 
	 // Rt and Rs must be valid register numbers (between 0 and 31)
	 if (PARAM1.value > 31 || PARAM2.value > 31) {
		 state = INVALID_REG;  // If the register values are out of range, set state to INVALID_REG
		 return;
	 }
 
	 // The offset must fit in 16 bits (range: 0x0000 to 0xFFFF)
	 if (PARAM3.value > 0xFFFF) {
		 state = INVALID_IMMED;  // If the offset exceeds 16 bits, set state to INVALID_IMMED
		 return;
	 }
 
	 /*
	  * Putting the binary together
	  */
 
	 // Set the opcode for SW (store word) instruction
	 setBits_str(31, "101011");
 
	 // Set Rt as the register containing the data to store
	 setBits_num(20, PARAM1.value, 5);  // Rt register
 
	 // Set Rs as the base address register
	 setBits_num(25, PARAM2.value, 5);  // Rs register
 
	 // Set the immediate value (offset)
	 setBits_num(15, PARAM3.value, 16);  // Immediate (offset)
 
	 // Let the system know the encoding is complete
	 state = COMPLETE_ENCODE;
 }
 
 // Function to decode the "SW" instruction from binary to assembly
 void sw_immd_bin(void) {
	 // Confirm that the opcode matches the "SW" (store word) instruction
	 if (checkBits(31, "101011") != 0) {
		 state = WRONG_COMMAND;  // If the opcode is incorrect, set state to WRONG_COMMAND
		 return;
	 }
 
	 /*
	  * Extracting values from the binary instruction
	  */
 
	 uint32_t Rs = getBits(25, 5);      // Extract the base register (Rs)
	 uint32_t Rt = getBits(20, 5);      // Extract the register to store (Rt)
	 uint32_t offset = getBits(15, 16); // Extract the offset value (immediate)
 
	 /*
	  * Setting the decoded instruction values
	  */
 
	 setOp("SW");                      // Set the operation to "SW"
	 setParam(1, REGISTER, Rt);        // Set the destination register (Rt)
	 setParam(2, REGISTER, Rs);        // Set the base register (Rs)
	 setParam(3, IMMEDIATE, offset);   // Set the offset value
 
	 // Let the system know the decoding is complete
	 state = COMPLETE_DECODE;
 }
 