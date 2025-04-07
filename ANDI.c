#include "Instruction.h"

void andi_immd_assm(void) {

	// Checking that the op code matches
	// strcmp(string1, string2) return 0 if they match
	if (strcmp(OP_CODE, "ANDI") != 0) {
		// If the op code doesnt match, this isnt the correct command
		state = WRONG_COMMAND;
		return;
	}

	// check params
	//first parameter needs to be a regester
	if (PARAM1.type != REGISTER) {
		state = MISSING_REG;
		return;
	}
	//first parameter needs to be a regester
	if (PARAM2.type != REGISTER) {
		state = MISSING_REG;
		return;
	}
	//first parameter needs to be a integer value
	if (PARAM3.type != IMMEDIATE) {
		state = INVALID_PARAM;
		return;
	}

	// checking the values of the parameters

	//parameter needs to be <= 31 
	if (PARAM1.value > 31) {
		state = INVALID_REG;
		return;
	}
	//parameter needs to be <= 31 
	if (PARAM2.value > 31) {
		state = INVALID_REG;
		return;
	}
	// The immediate value is limited to 16 bits, 
	if (PARAM3.value > 0xFFFF) {
		state = INVALID_IMMED;
		return;
	}

	// combine binary

	//set the op code
	setBits_str(31, "001100");
	
	// set Rts
	setBits_num(20, PARAM1.value, 5);
	//set Rs
	setBits_num(25, PARAM2.value, 5);
	//set immidiate
	setBits_num(15, PARAM3.value, 16);

	state = COMPLETE_ENCODE;
}

void andi_immd_bin(void) {
	if (checkBits(31, "001100") != 0 ) {
		state = WRONG_COMMAND;
		return;
	}

	// get binary values
	uint32_t Rs = getBits(25, 5);
	uint32_t Rt = getBits(20, 5);
	uint32_t imm16 = getBits(15, 16);

	// set op
	setOp("ANDI");
	setParam(1, REGISTER, Rt); 
	setParam(2, REGISTER, Rs); 
	setParam(3, IMMEDIATE, imm16);
	
	state = COMPLETE_DECODE;
}



