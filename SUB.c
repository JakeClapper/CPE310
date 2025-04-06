/*
* Author: Ol' Jim
* Date: 06/13/2012
* ByteForge Systems
* MIPS-Translatron 3000
*/

#include "Instruction.h"

void sub_reg_assm(void) {
	// Checking that the op code matches
	// strcmp(string1, string2) return 0 if they match
	if (strcmp(OP_CODE, "SUB") != 0) {
		// If the op code doesn't match, this isn't the correct command
		state = WRONG_COMMAND;
		return; 
	}

	/*
		Checking the type of parameters
	*/

	// All parameters must be registers for SUB
	if (PARAM1.type != REGISTER || PARAM2.type != REGISTER || PARAM3.type != REGISTER) {
		state = INVALID_PARAM;
		return;
	}

	/*
		Checking the value of parameters
	*/

	// All register values must be between 0 and 31
	if (PARAM1.value > 31 || PARAM2.value > 31 || PARAM3.value > 31) {
		state = INVALID_REG;
		return;
	}

	/*
		Putting the binary together
	*/

	// Set the opcode for R-type (SUB is an R-type)
	setBits_str(31, "000000");

	// Set Rs, Rt, Rd
	setBits_num(25, PARAM2.value, 5); // Rs
	setBits_num(20, PARAM3.value, 5); // Rt
	setBits_num(15, PARAM1.value, 5); // Rd

	// Set shamt to 0
	setBits_str(10, "00000");

	// Set funct code for SUB
	setBits_str(5, "100010");

	// Tell the system the encoding is done
	state = COMPLETE_ENCODE;
}

void sub_reg_bin(void) {
	// Check if the op code bits match
	// checkBits(start_bit, bit_string) returns 0 if the bit_string matches
	if (checkBits(31, "000000") != 0 || checkBits(5, "100010") != 0) {
		state = WRONG_COMMAND;
		return;
	}

	/*
		Finding values in the binary
	*/
	// getBits(start_bit, width)
	uint32_t Rs = getBits(25, 5);
	uint32_t Rt = getBits(20, 5);
	uint32_t Rd = getBits(15, 5);	

	/*
		Setting Instruction values
	*/

	setOp("SUB");
	setParam(1, REGISTER, Rd); // destination
	setParam(2, REGISTER, Rs); // first source register operand
	setParam(3, REGISTER, Rt); // second source register operand

	// Tell the system the decoding is done
	state = COMPLETE_DECODE;
}
