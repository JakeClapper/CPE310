/*
 * Author: Ol' Jim
 * Date: 06/13/2012
 * ByteForge Systems
 * MIPS-Translatron 3000
 */

 #include "Instruction.h"

 /**
  * Function: beq_immd_assm
  * ------------------------
  * Encodes the "BEQ" (Branch on Equal) instruction into binary format using I-type format.
  * 
  * Preconditions:
  * - OP_CODE must be "BEQ".
  * - PARAM1 must be a REGISTER.
  * - PARAM2 must be a REGISTER.
  * - PARAM3 must be an IMMEDIATE value (16-bit signed offset).
  * - All register values must be within the range 0–31.
  * - Immediate must fit in 16 bits.
  * 
  * Postconditions:
  * - Sets the binary representation of the BEQ instruction.
  * - Updates `state` to COMPLETE_ENCODE if successful, or an error state otherwise.
  */
 void beq_immd_assm(void) {
	 // Verify the opcode matches "BEQ".
	 if (strcmp(OP_CODE, "BEQ") != 0) {
		 state = WRONG_COMMAND;
		 return;
	 }
 
	 // PARAM1 must be a REGISTER (Rs).
	 if (PARAM1.type != REGISTER) {
		 state = MISSING_REG;
		 return;
	 }
 
	 // PARAM2 must be a REGISTER (Rt).
	 if (PARAM2.type != REGISTER) {
		 state = MISSING_REG;
		 return;
	 }
 
	 // PARAM3 must be an IMMEDIATE (offset).
	 if (PARAM3.type != IMMEDIATE) {
		 state = INVALID_PARAM;
		 return;
	 }
 
	 // All registers must be in range [0, 31].
	 if (PARAM1.value > 31 || PARAM2.value > 31) {
		 state = INVALID_REG;
		 return;
	 }
 
	 // Immediate value must fit in 16 bits (signed).
	 if (PARAM3.value > 0xFFFF) {
		 state = INVALID_IMMED;
		 return;
	 }
 
	 // Set opcode bits for BEQ.
	 setBits_str(31, "000100");
 
	 // Set Rs (PARAM1).
	 setBits_num(25, PARAM1.value, 5);
 
	 // Set Rt (PARAM2).
	 setBits_num(20, PARAM2.value, 5);
 
	 // Set 16-bit immediate (offset).
	 setBits_num(15, PARAM3.value, 16);
 
	 // Mark encoding as complete.
	 state = COMPLETE_ENCODE;
 }
 
 
 /**
  * Function: beq_immd_bin
  * -----------------------
  * Decodes a binary representation of the "BEQ" (Branch on Equal) instruction into human-readable components.
  * 
  * Preconditions:
  * - The opcode field (bits 31–26) must match "000100".
  * 
  * Postconditions:
  * - Extracts the register values and immediate offset.
  * - Sets operation and parameters with `setOp` and `setParam`.
  * - Updates `state` to COMPLETE_DECODE if successful, or an error state otherwise.
  */
 void beq_immd_bin(void) {
	 // Validate opcode matches BEQ ("000100").
	 if (checkBits(31, "000100") != 0) {
		 state = WRONG_COMMAND;
		 return;
	 }
 
	 // Extract Rs, Rt, and immediate from binary instruction.
	 uint32_t Rs = getBits(25, 5);     // Source register
	 uint32_t Rt = getBits(20, 5);     // Destination register
	 uint32_t imm16 = getBits(15, 16); // 16-bit offset
 
	 // Set decoded operation and parameters.
	 setOp("BEQ");
	 setParam(1, REGISTER, Rs);
	 setParam(2, REGISTER, Rt);
	 setParam(3, IMMEDIATE, imm16);
 
	 // Mark decoding as complete.
	 state = COMPLETE_DECODE;
 }
 