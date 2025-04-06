/*
* Author: Ol' Jim
* Date: 06/13/2012
* ByteForge Systems
* MIPS-Translatron 3000
*/

#include "Instruction.h"

void slt_reg_assm(void) {
	// Checking that the op code matches
	if (strcmp(OP_CODE, "SLT") != 0) {
		state = WRONG_COMMAND;
		return;
	}

	/*
		Checking the type of parameters 
	*/

	if (PARAM1.type != REGISTER || PARAM2.type != REGISTER || PARAM3.type != REGISTER) {
		state = INVALID_PARAM;
		return;
	}

	/*
		Checking the value of parameters
	*/

	// All registers should be between 0 and 31
	if (PARAM1.value > 31 || PARAM2.value > 31 || PARAM3.value > 31) {
		state = INVALID_REG;
		return;
	}

	/*
		Putting the binary together
	*/

	// Set the opcode (R-type, so all zeroes)
	setBits_str(31, "000000");

	// Set source and destination registers
	setBits_num(25, PARAM2.value, 5); // Rs
	setBits_num(20, PARAM1.value, 5); // Rd
	setBits_num(15, PARAM3.value, 5); // Rt

	// Set shift amount to zero
	setBits_str(10, "00000");

	// Set the function code for SLT
	setBits_str(5, "101010");

	// Let 'em know we’re done
	state = COMPLETE_ENCODE;
}

void slt_reg_bin(void) {
	// Confirm opcode and funct match SLT
	if (checkBits(31, "000000") != 0 || checkBits(5, "101010") != 0) {
		state = WRONG_COMMAND;
		return;
	}

	/*
		Get values from instruction binary
	*/

	uint32_t Rs = getBits(25, 5);  // First operand
	uint32_t Rt = getBits(20, 5);  // Second operand
	uint32_t Rd = getBits(15, 5);  // Destination

	/*
		Fill in the instruction structure
	*/

	setOp("SLT");
	setParam(1, REGISTER, Rd); // Destination
	setParam(2, REGISTER, Rs); // Source 1
	setParam(3, REGISTER, Rt); // Source 2

	state = COMPLETE_DECODE;
}
