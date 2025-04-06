#include "Instruction.h"
// Author: Kayden Yost

/**
 * Function: lw_immd_assm
 * ----------------------
 * Encodes the "LW" (Load Word) instruction into binary format based on the provided parameters.
 * 
 * Preconditions:
 * - OP_CODE must be "LW".
 * - PARAM1 must be a REGISTER (destination register).
 * - PARAM2 must be an IMMEDIATE (offset value).
 * - PARAM3 must be a REGISTER (base register).
 * 
 * Postconditions:
 * - Sets the binary representation of the instruction using `setBits_str` and `setBits_num`.
 * - Updates the `state` to COMPLETE_ENCODE if successful, or an error state otherwise.
 */
void lw_immd_assm(void) {

	// Check if the operation code matches "LW".
	if (strcmp(OP_CODE, "LW") != 0) {

		state = WRONG_COMMAND;
		return;
	}
	
	// Validate the types of the parameters.
	if (PARAM1.type != REGISTER || PARAM2.type != REGISTER || PARAM3.type != IMMEDIATE) 
	{
		state = INVALID_PARAM;
		return;
	}

	// Set the opcode bits for "LW" (Load Word).
	setBits_str(31, "100011");

	// Set the destination registers and immediate values.
	setBits_num(20, PARAM1.value, 5);
	setBits_num(25, PARAM3.value, 5);
	setBits_num(15, PARAM2.value, 16);

	// Update the state to indicate successful encoding.
	state = COMPLETE_ENCODE;
}

/**
 * Function: lw_immd_bin
 * ---------------------
 * Decodes a binary representation of the "LW" (Load Word) instruction into its components.
 * 
 * Preconditions:
 * - The binary instruction must have the opcode "100011" at bits 31-26.
 * 
 * Postconditions:
 * - Extracts the base register (Rs), destination register (Rt), and offset (immediate value).
 * - Sets the operation and parameters using `setOp` and `setParam`.
 * - Updates the `state` to COMPLETE_DECODE if successful, or an error state otherwise.
 */
void lw_immd_bin(void) {

	// Check if the opcode in the binary instruction matches "100011".
	if (checkBits(31, "100011") != 0) 
	{
		state = WRONG_COMMAND;
		return;
	}

	// Extract the base registers and immediate values from the binary instruction.
	uint32_t Rs = getBits(25, 5);
	uint32_t Rt = getBits(20, 5);
	uint32_t offset = getBits(15, 16);

	// Set the operation name to "LW".
	setOp("LW");

	// Set the destination registers and immediate offset.
	setParam(1, REGISTER, Rt);
	setParam(3, REGISTER, Rs);
	setParam(2, IMMEDIATE, offset);

	// Update the state to indicate successful decoding.
	state = COMPLETE_DECODE;
}
