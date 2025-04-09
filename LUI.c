/*
 * Author: Ol' Jim
 * Date: 06/13/2012
 * ByteForge Systems
 * MIPS-Translatron 3000
 */

 #include "Instruction.h"

 /**
  * Function: lui_immd_assm
  * ------------------------
  * Assembles the "LUI" (Load Upper Immediate) instruction into its binary representation.
  * 
  * Preconditions:
  * - OP_CODE must be "LUI".
  * - PARAM1 must be a REGISTER (destination register).
  * - PARAM2 must be an IMMEDIATE value (16-bit).
  * 
  * Postconditions:
  * - Encodes the instruction as binary.
  * - Sets `state` to COMPLETE_ENCODE if successful, or an error state if validation fails.
  */
 void lui_immd_assm(void) {
	 // Check if the opcode matches "LUI".
	 if (strcmp(OP_CODE, "LUI") != 0) {
		 state = WRONG_COMMAND; // Set state to WRONG_COMMAND if the opcode doesn't match.
		 return;
	 }
 
	 // Validate first parameter: must be a REGISTER.
	 if (PARAM1.type != REGISTER) {
		 state = MISSING_REG; // Set state to MISSING_REG if PARAM1 is not a REGISTER.
		 return;
	 }
 
	 // Validate second parameter: must be an IMMEDIATE value.
	 if (PARAM2.type != IMMEDIATE) {
		 state = INVALID_PARAM; // Set state to INVALID_PARAM if PARAM2 is not an IMMEDIATE value.
		 return;
	 }
 
	 // Validate register and immediate value ranges.
	 if (PARAM1.value > 31) {
		 state = INVALID_REG; // Set state to INVALID_REG if PARAM1 is out of range.
		 return;
	 }
	 if (PARAM2.value > 0xFFFF) {
		 state = INVALID_IMMED; // Set state to INVALID_IMMED if PARAM2 is out of range (16-bit).
		 return;
	 }
 
	 // Begin encoding: LUI is an I-type instruction.
	 setBits_str(31, "001111");               // Opcode for LUI (bits 31–26)
	 setBits_num(20, PARAM1.value, 5);        // Rt (destination register) — bits 20–16
	 setBits_num(15, PARAM2.value, 16);       // Immediate value (upper 16 bits) — bits 15–0
 
	 // Mark encoding as complete
	 state = COMPLETE_ENCODE;
 }
 
 /**
  * Function: lui_immd_bin
  * -----------------------
  * Decodes the binary form of the "LUI" (Load Upper Immediate) instruction into readable components.
  * 
  * Preconditions:
  * - Must match the opcode "001111" at bits 31–26.
  * 
  * Postconditions:
  * - Sets OP_CODE and the parameters based on the decoded binary.
  * - Updates `state` to COMPLETE_DECODE or an error state if the instruction doesn't match.
  */
 void lui_immd_bin(void) {
	 // Check if the opcode matches "LUI".
	 if (checkBits(31, "001111") != 0) {
		 state = WRONG_COMMAND; // Set state to WRONG_COMMAND if the opcode doesn't match.
		 return;
	 }
 
	 // Extract the destination register (Rt) and the immediate value.
	 uint32_t Rt = getBits(20, 5);     // Rt (destination register) — bits 20–16
	 uint32_t imm16 = getBits(15, 16);  // Immediate value — bits 15–0
 
	 // Set the operation to "LUI" and its parameters.
	 setOp("LUI");
	 setParam(1, REGISTER, Rt);         // Destination register
	 setParam(3, IMMEDIATE, imm16);     // Immediate value
 
	 // Mark decoding as complete
	 state = COMPLETE_DECODE;
 }
 