/*
* Author: Ol' Jim
* Date: 06/13/2012
* ByteForge Systems
* MIPS-Translatron 3000
*/

#include "Instruction.h"

void sw_immd_assm(void) {
	// Check the operation code
	if (strcmp(OP_CODE, "SW") != 0) {
		state = WRONG_COMMAND;
		return;
	}

	/*
		Checking parameter types
	*/

	// First param should be a register (Rt)
	if (PARAM1.type != REGISTER) {
		state = MISSING_REG;
		return;
	}

	// Second param should be a register (Rs)
	if (PARAM2.type != REGISTER) {
		state = MISSING_REG;
		return;
	}

	// Third param should be an immediate (offset)
	if (PARAM3.type != IMMEDIATE) {
		state = INVALID_PARAM;
		return;
	}

	/*
		Checking parameter values
	*/

	// Rt and Rs must be valid register numbers (0–31)
	if (PARAM1.value > 31 || PARAM2.value > 31) {
		state = INVALID_REG;
		return;
	}

	// Offset must fit in 16 bits
	if (PARAM3.value > 0xFFFF) {
		state = INVALID_IMMED;
		return;
	}

	/*
		Putting the binary together
	*/

	// Set opcode for SW (store word)
	setBits_str(31, "101011");

	// Set Rt (source data register)
	setBits_num(20, PARAM1.value, 5);

	// Set Rs (base address register)
	setBits_num(25, PARAM2.value, 5);

	// Set offset (immediate field)
	setBits_num(15, PARAM3.value, 16);

	// Encoding complete
	state = COMPLETE_ENCODE;
}

void sw_immd_bin(void) {
	// Confirm opcode bits match for SW
	if (checkBits(31, "101011") != 0) {
		state = WRONG_COMMAND;
		return;
	}

	/*
		Extracting values from binary
	*/

	uint32_t Rs = getBits(25, 5);      // Base register
	uint32_t Rt = getBits(20, 5);      // Register to store
	uint32_t offset = getBits(15, 16); // Offset value

	/*
		Setting decoded instruction values
	*/

	setOp("SW");
	setParam(1, REGISTER, Rt);        // Destination register (to store)
	setParam(2, REGISTER, Rs);        // Base register
	setParam(3, IMMEDIATE, offset);   // Offset

	// Decoding complete
	state = COMPLETE_DECODE;
}
