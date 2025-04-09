/*
 * Author: Ol' Jim
 * Date: 06/13/2012
 * ByteForge Systems
 * MIPS-Translatron 3000
 */

 #include "Instruction.h"

 // Function to encode the "SLT" (Set on Less Than) instruction for registers into binary
 void slt_reg_assm(void) {
	 // Checking that the operation code is "SLT"
	 if (strcmp(OP_CODE, "SLT") != 0) {
		 state = WRONG_COMMAND;  // Set state to WRONG_COMMAND if the opcode does not match
		 return;
	 }
 
	 /*
		 Checking the type of parameters: 
		 Ensure all parameters are registers
	 */
	 if (PARAM1.type != REGISTER || PARAM2.type != REGISTER || PARAM3.type != REGISTER) {
		 state = INVALID_PARAM;  // Set state to INVALID_PARAM if any parameter is not a REGISTER
		 return;
	 }
 
	 /*
		 Checking the value of parameters:
		 Ensure all registers are between 0 and 31
	 */
	 if (PARAM1.value > 31 || PARAM2.value > 31 || PARAM3.value > 31) {
		 state = INVALID_REG;  // Set state to INVALID_REG if any register value is out of range
		 return;
	 }
 
	 /*
		 Putting the binary together:
		 Setting the opcode, registers, shift amount, and function code for the SLT instruction
	 */
 
	 // Set the opcode for R-type instruction (all zeroes)
	 setBits_str(31, "000000");
 
	 // Set the source register (Rs), destination register (Rd), and second operand register (Rt)
	 setBits_num(25, PARAM2.value, 5); // Rs (source register 1)
	 setBits_num(20, PARAM1.value, 5); // Rd (destination register)
	 setBits_num(15, PARAM3.value, 5); // Rt (source register 2)
 
	 // Set the shift amount (shamt) to 0 for SLT (not used in this case)
	 setBits_str(10, "00000");
 
	 // Set the function code for SLT (101010)
	 setBits_str(5, "101010");
 
	 // Mark encoding as complete
	 state = COMPLETE_ENCODE;
 }
 
 // Function to decode the "SLT" instruction from binary to assembly
 void slt_reg_bin(void) {
	 // Confirm opcode (000000) and function code (101010) match "SLT"
	 if (checkBits(31, "000000") != 0 || checkBits(5, "101010") != 0) {
		 state = WRONG_COMMAND;  // Set state to WRONG_COMMAND if opcode or function code does not match
		 return;
	 }
 
	 /*
		 Get values from instruction binary:
		 Extract the source and destination registers (Rs, Rt, Rd)
	 */
	 uint32_t Rs = getBits(25, 5);  // Extract Rs (first source operand)
	 uint32_t Rt = getBits(20, 5);  // Extract Rt (second source operand)
	 uint32_t Rd = getBits(15, 5);  // Extract Rd (destination register)
 
	 /*
		 Fill in the instruction structure:
		 Set operation and parameters for the decoded SLT instruction
	 */
	 setOp("SLT");  // Set operation to SLT
 
	 setParam(1, REGISTER, Rd);  // Set destination register (Rd)
	 setParam(2, REGISTER, Rs);  // Set source register 1 (Rs)
	 setParam(3, REGISTER, Rt);  // Set source register 2 (Rt)
 
	 // Mark decoding as complete
	 state = COMPLETE_DECODE;
 }
 