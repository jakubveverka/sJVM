
#include <iostream>
#include <cstring>

#include "../include/debugMsg.hpp"
#include "../include/executionUnit.hpp"
#include "../include/definitions.hpp"
#include "../include/operands/intOperand.hpp"
#include "../include/operands/refOperand.hpp"
#include "../include/objectHeap.hpp"

	 ExecutionUnit::ExecutionUnit(std::stack<Frame*> p_frameStack, ObjectHeap * p_objectHeap)
{
	frameStack = p_frameStack;
	objectHeap = p_objectHeap;
}

void ExecutionUnit::execute( Frame * frame)
{

	u1 *p = frame -> getMethod() . code_attr -> code;

	Operand * firstOperand;
	Operand * secondOperand;

	u1 firstBranchByte;
	u1 secondBranchByte;
	u1 thirdBranchByte;
	u1 fourthBranchByte;

	while(1)
	{
		switch(p[frame -> getPc()])
		{
			case 0x0:
				DEBUG_MSG("executing: nop");
				frame -> movePc(1);
				break;
			case 0x1:
				DEBUG_MSG("executing: aconst_null");
				break;
			case 0x2: //iconst_m1 - fallback to iconst_5
			case 0x3: //iconst_0 - fallback to iconst_5
			case 0x4: //iconst_1 - fallback to iconst_5
			case 0x5: //iconst_2 - fallback to iconst_5
			case 0x6: //iconst_3 - fallback to iconst_5
			case 0x7: //iconst_4 - fallback to iconst_5
			case 0x8: //iconst_5
			{
				DEBUG_MSG("executing: iconst_<i>");
				DEBUG_MSG("iconst_<i> operand: " + std::to_string((u1)(p[frame -> getPc()] - 0x03)));
				frame -> pushOperand(new IntOperand((u1)(p[frame -> getPc()] - 0x03)));
				frame -> movePc(1);
				break;
			}
			case 0x9:
				DEBUG_MSG("executing: lconst_0");
				break;
			case 0x0a:
				DEBUG_MSG("executing: lconst_1");
				break;
			case 0x0b:
				DEBUG_MSG("executing: fconst_0");
				break;
			case 0x0c:
				DEBUG_MSG("executing: fconst_1");
				break;
			case 0x0d:
				DEBUG_MSG("executing: fconst_2");
				break;
			//case 0x0e:
				//TODO dconst_0
			//case 0x0f:
				//TODO dconst_1
			case 0x10:
			{
				DEBUG_MSG("executing: bipush");
				DEBUG_MSG("bipush operand: " + std::to_string((int)((u1)(p[frame->getPc()+1]))));
				IntOperand * pushOperand = new IntOperand((int)((u1)(p[frame->getPc()+1])));
				frame -> pushOperand(pushOperand);
				frame -> movePc(2);
				break;
			}
			case 0x11:
			{
				DEBUG_MSG("executing: sipush");
				u2 operand = getu2(p + frame->getPc() + 1);
				DEBUG_MSG("sipush operand: " + std::to_string(operand));
				IntOperand * pushOperand = new IntOperand(operand);
				frame -> pushOperand(pushOperand);
				frame -> movePc(3);
				break;
			}
			case 0x12:
				DEBUG_MSG("executing: LDC");
				break;
			//case 0x13:
				//TODO ldc_w
			case 0x14:
				DEBUG_MSG("executing: ldc2_w");
				break;

			// LOADS ///////////////////////////////////////////////////////////////
			case 0x15:
				DEBUG_MSG("executing: iload");
				DEBUG_MSG("iload index: " + std::to_string(p[frame -> getPc()+1]));
				DEBUG_MSG("iload operand: " + std::to_string(frame->loadOperand(p[frame -> getPc()+1])->getValue()));
				frame -> pushOperand(frame -> loadOperand(p[frame -> getPc()+1]));
				frame -> movePc(2);
				break;
			case 0x16:
				DEBUG_MSG("executing: lload");
				break;
			//case 0x17:
				//TODO fload
			//case 0x18:
				//TODO dload
			case 0x19:
				DEBUG_MSG("executing: aload");
				DEBUG_MSG("aload index: " + std::to_string(p[frame -> getPc()+1]));
				DEBUG_MSG("aload operand: " + std::to_string(frame->loadOperand(p[frame -> getPc()+1])->getValue()));
				frame -> pushOperand(frame -> loadOperand(p[frame -> getPc()+1]));
				frame -> movePc(2);
				break;
			case 0x1a: // iload_0 - fallback to iload_3
			case 0x1b: // iload_1 - fallback to iload_3
			case 0x1c: // iload_2 - fallback to iload_3
			case 0x1d: // iload_3
				DEBUG_MSG("executing: iload_<i>");
				DEBUG_MSG("iload_<i> index: " + std::to_string(p[frame -> getPc()] - 0x1a));
				DEBUG_MSG("iload_<i> operand: " + std::to_string(frame->loadOperand(p[frame -> getPc()] - 0x1a)->getValue()));
				frame -> pushOperand(frame -> loadOperand(p[frame -> getPc()] - 0x1a));
				frame -> movePc(1);
				break;
			case 0x1e:
				DEBUG_MSG("executing: lload_0");
				break;
			case 0x1f:
				DEBUG_MSG("executing: lload_1");
				break;
			case 0x20:
				DEBUG_MSG("executing: lload_2");
				break;
			case 0x21:
				DEBUG_MSG("executing: lload_3");
				break;
			case 0x22:
				DEBUG_MSG("executing: fload_0");
				break;
			case 0x23:
				DEBUG_MSG("executing: fload_1");
				break;
			case 0x24:
				DEBUG_MSG("executing: fload_2");
				break;
			case 0x25:
				DEBUG_MSG("executing: fload_3");
				break;
			//case 0x26:
				//TODO dload_0
			//case 0x27:
				//TODO dload_1
			//case 0x28:
				//TODO dload_2
			//case 0x29:
				//TODO dload_3
			case 0x2a: // aload_0
			case 0x2b: // aload_1
			case 0x2c: // aload_2
			case 0x2d: // aload_3
				DEBUG_MSG("executing: aload_<i>");
				DEBUG_MSG("aload_<i> index: " + std::to_string(p[frame -> getPc()] - 0x2a));
				DEBUG_MSG("aload_<i> operand: " + std::to_string(frame->loadOperand(p[frame -> getPc()] - 0x2a)->getValue()));
				frame -> pushOperand(frame -> loadOperand(p[frame -> getPc()] - 0x2a));
				frame -> movePc(1);
				break;
			case 0x2e:
				{
					Operand * indexOp = frame -> topPopOperand();
					Operand * refOp = frame -> topPopOperand();
					Operand * valueOp = objectHeap -> loadArrayOp(refOp, indexOp);	
					DEBUG_MSG("executing: iaload. Loaded value: " + std::to_string(valueOp -> getValue()) + 
							  " from ref: " + std::to_string(refOp -> getValue()) +
							  " on index: " + std::to_string(indexOp -> getValue()));
					frame -> pushOperand(valueOp);
					frame -> movePc(1);				
					break;
				}
			case 0x2f:
				DEBUG_MSG("executing: laload");
				break;
			case 0x30:
				DEBUG_MSG("executing: faload");
				break;
			//case 0x31:
				//TODO daload
			case 0x32:
				DEBUG_MSG("executing: aaload");
				break;
			case 0x33:
				DEBUG_MSG("executing: baload");
				break;
			case 0x34:
				DEBUG_MSG("executing: caload");
				break;
			case 0x35:
				DEBUG_MSG("executing: saload");
				break;

			// STORES //////////////////////////////////////////////////////////////
			case 0x36:
			{
				DEBUG_MSG("executing: istore");
				DEBUG_MSG("istore index: " + std::to_string((u1)p[frame -> getPc() + 1]));
				Operand * op = frame->topPopOperand();
				DEBUG_MSG("istore operand: " + std::to_string(op->getValue()));
				frame -> storeOperand((u1)p[frame -> getPc() + 1], op);
				frame -> movePc(2);
				break;
			}
			case 0x37:
				DEBUG_MSG("executing: lstore");
				break;
			case 0x38:
				DEBUG_MSG("executing: fstore");
				break;
			//case 0x39:
				//TODO dstore
			case 0x3a:
			{
				DEBUG_MSG("executing: astore");
				DEBUG_MSG("astore index: " + std::to_string((u1)p[frame -> getPc() + 1]));
				Operand * op = frame->topPopOperand();
				DEBUG_MSG("astore operand: " + std::to_string(op->getValue()));
				frame -> storeOperand((u1)p[frame -> getPc() + 1], op);
				frame -> movePc(2);
				break;
			}
			case 0x3b: // istore_0 - fallback to istore_3
			case 0x3c: // istore_1 - fallback to istore_3
			case 0x3d: // istore_2 - fallback to istore_3
			case 0x3e: // istore_3
			{
				DEBUG_MSG("executing: istore_<i>");
				DEBUG_MSG("istore_<i> index: " + std::to_string((u1)(p[frame -> getPc()] - 0x3b)));
				Operand * op = frame->topPopOperand();
				DEBUG_MSG("istore_<i> operand: " + std::to_string(op->getValue()));
				frame -> storeOperand((u1)(p[frame -> getPc()] - 0x3b), op);
				frame -> movePc(1);
				break;
			}
			case 0x3f:
				DEBUG_MSG("executing: lstore_0");
				break;
			case 0x40:
				DEBUG_MSG("executing: lstore_1");
				break;
			case 0x41:
				DEBUG_MSG("executing: lstore_2");
				break;
			case 0x42:
				DEBUG_MSG("executing: lstore_3");
				break;
			case 0x43:
				DEBUG_MSG("executing: fstore_0");
				break;
			case 0x44:
				DEBUG_MSG("executing: fstore_1");
				break;
			case 0x45:
				DEBUG_MSG("executing: fstore_2");
				break;
			case 0x46:
				DEBUG_MSG("executing: fstore_3");
				break;
			//case 0x47:
				//TODO dstore_0
			//case 0x48:
				//TODO dstore_1
			//case 0x49:
				//TODO dstore_2
			//case 0x4a:
				//TODO dstore_3
			case 0x4b:
			case 0x4c:
			case 0x4d:
			case 0x4e:
			{
				DEBUG_MSG("executing: astore_<i>");
				DEBUG_MSG("astore_<i> index: " + std::to_string((u1)(p[frame -> getPc()] - 0x4b)));
				Operand * op = frame->topPopOperand();
				DEBUG_MSG("astore_<i> operand: " + std::to_string(op->getValue()));
				frame -> storeOperand((u1)(p[frame -> getPc()] - 0x4b), op);
				frame -> movePc(1);
				break;
			}
			case 0x4f:
				{
					Operand * valueOp = frame -> topPopOperand();
					Operand * indexOp = frame -> topPopOperand();
					Operand * refOp = frame -> topPopOperand();
					DEBUG_MSG("executing: iastore. Storing value: " + std::to_string(valueOp -> getValue()) + 
							  " from ref: " + std::to_string(refOp -> getValue()) +
							  " on index: " + std::to_string(indexOp -> getValue()));
					objectHeap -> storeArrayOp(refOp, indexOp, valueOp);
					frame -> movePc(1);					
					break;
				}
			case 0x50:
				DEBUG_MSG("executing: lastore");


				break;
			case 0x51:
				DEBUG_MSG("executing: fastore");
				break;
			//case 0x52:
				//TODO dastore
			case 0x53:
				DEBUG_MSG("executing: aastore");
				break;
			case 0x54:
				DEBUG_MSG("executing: bastore");
				break;
			case 0x55:
				DEBUG_MSG("executing: castore");
				break;
			case 0x56:
				DEBUG_MSG("executing: sastore");
				break;

			// STACK ///////////////////////////////////////////////////////////////
			case 0x57:
				DEBUG_MSG("executing: pop");
				break;
			case 0x58:
				DEBUG_MSG("executing: pop2");
				break;
			case 0x59:
				DEBUG_MSG("executing: dup");
				frame -> opStack.push(frame -> opStack.top());
				frame -> movePc(1);
				break;
			//case 0x5a:
				//TODO dup_x1
			//case 0x5b:
				//TODO dup_x2
			//case 0x5c:
				//TODO dup2
			//case 0x5d:
				//TODO dup2_x1
			//case 0x5e:
				//TODO dup2_x2
			//case 0x5f:
				//TODO swap

			// MATH ////////////////////////////////////////////////////////////////
			case 0x60:
			{
				DEBUG_MSG("executing: iadd");
				getTwoStackOperands("iadd", frame, firstOperand, secondOperand);

				IntOperand * iaddResult = new IntOperand(firstOperand->getValue() + secondOperand->getValue());
				DEBUG_MSG("iadd: result " + std::to_string(iaddResult->getValue()));
				frame -> pushOperand (iaddResult);
				frame -> movePc(1);
				break;
			}
			case 0x61:
				DEBUG_MSG("executing: ladd");
				break;
			case 0x62:
				DEBUG_MSG("executing: fadd");
				break;
			//case 0x63:
				//TODO dadd
			case 0x64:
			{
				DEBUG_MSG("executing: isub");
				getTwoStackOperands("isub", frame, firstOperand, secondOperand);

				IntOperand * isubResult = new IntOperand(secondOperand->getValue() - firstOperand->getValue());
				DEBUG_MSG("isub: result " + std::to_string(isubResult->getValue()));
				frame -> pushOperand (isubResult);
				frame -> movePc(1);
				break;
			}
			case 0x65:
				DEBUG_MSG("executing: lsub");
				break;
			case 0x66:
				DEBUG_MSG("executing: fsub");
				break;
			//case 0x67:
				//TODO dsub
			case 0x68:
			{
				DEBUG_MSG("executing: imul");
				getTwoStackOperands("imul", frame, firstOperand, secondOperand);

				IntOperand * imulResult = new IntOperand(firstOperand->getValue() * secondOperand->getValue());
				DEBUG_MSG("imul: result " + std::to_string(imulResult->getValue()));
				frame -> pushOperand (imulResult);
				frame -> movePc(1);
				break;
			}
			case 0x69:
				DEBUG_MSG("executing: lmul");
				break;
			case 0x6a:
				DEBUG_MSG("executing: fmul");
				break;
			//case 0x6b:
				//TODO dmul
			case 0x6c:
			{
				DEBUG_MSG("executing: idiv");
				getTwoStackOperands("idiv", frame, firstOperand, secondOperand);

				IntOperand * idivResult = new IntOperand(secondOperand->getValue() / firstOperand->getValue());
				DEBUG_MSG("idiv: result " + std::to_string(idivResult->getValue()));
				frame -> pushOperand(idivResult);
				frame -> movePc(1);
				break;
			}
			case 0x6d:
				DEBUG_MSG("executing: ldiv");
				break;
			case 0x6e:
				DEBUG_MSG("executing: fdiv");
				break;
			//case 0x6f:
				//TODO ddiv
			case 0x70:
			{
				DEBUG_MSG("executing: irem");
				getTwoStackOperands("irem", frame, firstOperand, secondOperand);

				IntOperand * iremResult = new IntOperand(secondOperand->getValue() - ((secondOperand->getValue() / firstOperand->getValue()) * firstOperand->getValue()));
				DEBUG_MSG("irem: result " + std::to_string(iremResult->getValue()));
				frame -> pushOperand(iremResult);
				frame -> movePc(1);
				break;
			}
			//case 0x71:
				//TODO lrem
			//case 0x72:
				//TODO frem
			//case 0x73:
				//TODO drem
			case 0x74:
			{
				DEBUG_MSG("executing: ineg"); //TODO test
				firstOperand = frame->topPopOperand();
				DEBUG_MSG("ineg: first operand: " + std::to_string(firstOperand->getValue()));

				IntOperand * result = new IntOperand(~firstOperand->getValue());
				DEBUG_MSG("ishl: result " + std::to_string(result->getValue()));
				frame -> pushOperand(result);
				frame -> movePc(1);
				break;
			}
			//case 0x75:
				//TODO lneg
			//case 0x76:
				//TODO fneg
			//case 0x77:
				//TODO dneg

			case 0x78:
			{
				DEBUG_MSG("executing: ishl");
				getTwoStackOperands("ishl", frame, firstOperand, secondOperand);

				IntOperand * ishlResult = new IntOperand(secondOperand->getValue() << (firstOperand->getValue() & 0x1f));
				DEBUG_MSG("ishl: result " + std::to_string(ishlResult->getValue()));
				frame -> pushOperand(ishlResult);
				frame -> movePc(1);
				break;
			}
			//case 0x79:
				//TODO lshl
			case 0x7a:
			{
				DEBUG_MSG("executing: ishr"); //TODO test and implement for negative int
				getTwoStackOperands("ishr", frame, firstOperand, secondOperand);

				IntOperand * ishrResult = new IntOperand(secondOperand->getValue() >> (firstOperand->getValue() & 0x1f));
				DEBUG_MSG("ishl: result " + std::to_string(ishrResult->getValue()));
				frame -> pushOperand(ishrResult);
				frame -> movePc(1);
				break;
			}
			//case 0x7b:
				//TODO lshr
			case 0x7c:
			{
				DEBUG_MSG("executing: iushr"); //TODO test with negative int
				getTwoStackOperands("iushr", frame, firstOperand, secondOperand);

				IntOperand * result = new IntOperand((int)((unsigned int)secondOperand->getValue() >> (firstOperand->getValue() & 0x1f)));
				DEBUG_MSG("ishl: result " + std::to_string(result->getValue()));
				frame -> pushOperand(result);
				frame -> movePc(1);
				break;
			}
			case 0x7d:
				DEBUG_MSG("executing: lushr");
				break;
			case 0x7e:
			{
				DEBUG_MSG("executing: iand");
				getTwoStackOperands("iand", frame, firstOperand, secondOperand);

				IntOperand * result = new IntOperand(secondOperand->getValue() & firstOperand->getValue());
				DEBUG_MSG("iand: result " + std::to_string(result->getValue()));
				frame -> pushOperand(result);
				frame -> movePc(1);
				break;
			}
			case 0x7f:
				//TODO land
			case 0x80:
			{
				DEBUG_MSG("executing: ior");
				getTwoStackOperands("ior", frame, firstOperand, secondOperand);

				IntOperand * result = new IntOperand(secondOperand->getValue() | firstOperand->getValue());
				DEBUG_MSG("ior: result " + std::to_string(result->getValue()));
				frame -> pushOperand(result);
				frame -> movePc(1);
				break;
			}
			//case 0x81:
				//TODO lor
			case 0x82:
			{
				DEBUG_MSG("executing: ixor");
				getTwoStackOperands("ixor", frame, firstOperand, secondOperand);

				IntOperand * result = new IntOperand(secondOperand->getValue() ^ firstOperand->getValue());
				DEBUG_MSG("ixor: result " + std::to_string(result->getValue()));
				frame -> pushOperand(result);
				frame -> movePc(1);
				break;
			}
			//case 0x83:
				//TODO lxor
			case 0x84:
			{
				DEBUG_MSG("executing: iinc");
				DEBUG_MSG("iinc: index: " + std::to_string(p[frame -> getPc()+1]));
				DEBUG_MSG("iinc: const: " + std::to_string(p[frame -> getPc()+2]));
				Operand * operand = frame -> loadOperand(p[frame -> getPc()+1]);
				DEBUG_MSG("iinc: old operand value: " + std::to_string(operand->getValue()));
				operand->setValue(operand->getValue() + p[frame -> getPc()+2]);
				DEBUG_MSG("iinc: new operand value: " + std::to_string(operand->getValue()));
				frame -> movePc(3);
				break;
			}
			// CONVERSIONS /////////////////////////////////////////////////////////
			case 0x86:
				DEBUG_MSG("executing: i2f");
				break;

			// COMPARSIONS /////////////////////////////////////////////////////////
			case 0x94:
				DEBUG_MSG("executing: lcmp");
				break;
			case 0x95:
				DEBUG_MSG("executing: fcml");
				break;
			case 0x96:
				DEBUG_MSG("executing: fcmpg");
				break;
			//case 0x97:
				//TODO dcmpl
			//case 0x98:
				//TODO dcmpg
			case 0x99:
			case 0x9a:
			case 0x9b:
			case 0x9c:
			case 0x9d:
			case 0x9e:
			{
				DEBUG_MSG("executing: if<cond>");
				int firstOperandValue = (int)frame->topPopOperand()->getValue();
				bool ifResult = false;
				u1 pc = p[frame -> getPc()];
				DEBUG_MSG("if<cond>: pc: " + std::to_string(pc));
				DEBUG_MSG("if<cond>: operand: " + std::to_string(firstOperandValue));
				if (pc == 0x99) ifResult = firstOperandValue == 0;
				else if(pc == 0x9a) ifResult = firstOperandValue != 0;
				else if(pc == 0x9b) ifResult = firstOperandValue < 0;
				else if(pc == 0x9c) ifResult = firstOperandValue >= 0;
				else if(pc == 0x9d) ifResult = firstOperandValue > 0;
				else if(pc == 0x9e) ifResult = firstOperandValue <= 0;
				else DEBUG_MSG("unsuported given <cond> for if<cond>");

				DEBUG_MSG("if<cond>: result: " + std::to_string(ifResult));

				if(ifResult) {
					getTwoBytesFromFrame("if<cond>", frame, p, firstBranchByte, secondBranchByte);
					short offset = (firstBranchByte << 8) | secondBranchByte;
					frame->movePc(offset);
				} else {
					frame->movePc(3);
				}
				break;
			}
			case 0x9f:
			case 0xa0:
			case 0xa1:
			case 0xa2:
			case 0xa3:
			case 0xa4:
			{
				DEBUG_MSG("executing: if_icmp<cond>");
				getTwoStackOperands("if_icmp<cond>", frame, firstOperand, secondOperand);
				int firstOperandValue = (int) firstOperand->getValue();
				int secondOperandValue = (int) secondOperand->getValue();
				bool ifResult = false;
				u1 pc = p[frame -> getPc()];
				DEBUG_MSG("if_icmp<cond>: pc: " + std::to_string(pc));
				if (pc == 0x9f) ifResult = firstOperandValue == secondOperandValue;
				else if(pc == 0xa0) ifResult = firstOperandValue != secondOperandValue;
				else if(pc == 0xa1) ifResult = firstOperandValue > secondOperandValue;
				else if(pc == 0xa2) ifResult = firstOperandValue <= secondOperandValue;
				else if(pc == 0xa3) ifResult = firstOperandValue < secondOperandValue;
				else if(pc == 0xa4) ifResult = firstOperandValue >= secondOperandValue;
				else DEBUG_MSG("unsuported given <cond> for if_icmp<cond>");

				DEBUG_MSG("if_icmp<cond>: result: " + std::to_string(ifResult));

				if(ifResult) {
					getTwoBytesFromFrame("if_icmp<cond>", frame, p, firstBranchByte, secondBranchByte);
					short offset = (firstBranchByte << 8) | secondBranchByte;
					frame->movePc(offset);
				} else {
					frame->movePc(3);
				}
				break;
			}
			case 0xa5:
				DEBUG_MSG("executing: if_acmpeq");
				break;
			case 0xa6:
				DEBUG_MSG("executing: if_acmpne");
				break;

			// CONTROL /////////////////////////////////////////////////////////////
			case 0xa7:
			{
				DEBUG_MSG("executing: goto");
				getTwoBytesFromFrame("goto", frame, p, firstBranchByte, secondBranchByte);
				short offset = (firstBranchByte << 8) | secondBranchByte;
				frame->movePc(offset);
				break;
			}
			case 0xc8:
			{
				DEBUG_MSG("executing: goto_w");
				getFourBytesFromFrame("goto_w", frame, p, firstBranchByte, secondBranchByte, thirdBranchByte, fourthBranchByte);
				int offset = (firstBranchByte << 24) | (secondBranchByte << 16) | (thirdBranchByte << 8) | fourthBranchByte;
				frame->movePc(offset);
				break;
			}
			case 0xac:
				{
					DEBUG_MSG("executing: ireturn");
					Operand * tmp = frame -> topPopOperand();
					frameStack . pop();
					frameStack . top() -> pushOperand(tmp);
					return;
					break;
				}
			case 0xad:
				DEBUG_MSG("executing: lreturn");
				break;
			case 0xb0:
				DEBUG_MSG("executing: areturn");
				break;
			case 0xb1:
				DEBUG_MSG("executing: return");
				frameStack . pop();
				return;
				break;

			// REFERENCIS //////////////////////////////////////////////////////////
			case 0xb2:
				DEBUG_MSG("executing: getstatic");
				break;
			case 0xb3:
				DEBUG_MSG("executing: putstatic");
				break;
			case 0xb4:
				DEBUG_MSG("executing: getfield");
				getField(frame);
				frame -> movePc(3);
				break;
			case 0xb5:
				DEBUG_MSG("executing: putfield");
				putfield(frame);
				frame -> movePc(3);
				break;
			case 0xb6:
				DEBUG_MSG("executing: invokevirtual");
				executeInvoke(frame, 0xb6);
				frame -> movePc(3);
				break;
			case 0xb7:
				DEBUG_MSG("executing: invokespecial");\
				executeInvoke(frame, 0xb7);
				frame -> movePc(3);
				break;
			case 0xb8:
				DEBUG_MSG("executing: invokestatic");
				executeInvoke(frame, 0xb8);
				frame -> movePc(3);
				break;
			case 0xb9:
				DEBUG_MSG("executing: invokeinterface");
				break;
			case 0xba:
				//invokedynamic - java nepouziva
				DEBUG_MSG("invokedynamic is not supported by BVM");
				break;
			case 0xbb:
				DEBUG_MSG("executing: new");
				frame -> pushOperand( new RefOperand(executeNew(frame)));
				frame -> movePc(3);
				break;
			case 0xbc:
				DEBUG_MSG("executing: newarray");
				frame -> pushOperand(new RefOperand(executeNewArray(frame)));
				frame -> movePc(2);
				break;
			case 0xbd:
				DEBUG_MSG("executing: anewarray");
				break;
			case 0xbe:
				DEBUG_MSG("executing: arraylength");
				break;
			case 0xbf:
				DEBUG_MSG("executing: athrow");
				break;
			//case 0xc0:
				//TODO checkcast
			case 0xc1:
				DEBUG_MSG("executing: instanceof");
				break;
			//case 0xc2:
				//TODO monitorenter
			//case 0xc3:
				//TODO monitorexit

			// EXTENDED ////////////////////////////////////////////////////////////
			case 0xc6:
				DEBUG_MSG("executing: ifnull");
				break;
			case 0xc7:
				DEBUG_MSG("executing: ifnonull");
				break;

			////////////////////////////////////////////////////////////////////////
			default:
				break;
		}
	}

	frameStack.pop();
}

void ExecutionUnit::executeInvoke(Frame * frame, u1 type)
{

	// get reference of method to class constant pool: invokestatic, indexbyte1, indexbyte2
	u2 classConstRef = getu2(&frame -> getMethod() . code_attr -> code[frame -> getPc() + 1]);

	// get constant_pool entry on this reference. Its CONSTANT_Methodref_info structure
	u1 * p_methodRefInfo = (u1*)frame -> javaClass -> constant_pool[classConstRef];

	// get info from this constant_pool entry about method
	u2 classIndex  	    = getu2(p_methodRefInfo + 1);
	u2 nameAndTypeIndex = getu2(p_methodRefInfo + 3);

	// get class info on this classIndex
	u1 * p_classInfo = (u1*)frame -> javaClass -> constant_pool[classIndex];

	// get name_index of this class (ref to constant_pool with class name)
	u2 nameIndexClass = getu2(p_classInfo + 1);

	// get string name of this class from constant pool
	std::string className;
	frame -> javaClass -> getAttrName(nameIndexClass, className);

	// load class with that className
	//ClassFile * javaClass = frame -> classHeap.getClass(className);

	// get NameAndType_Info structure from constant pool
	u1 *p_nameAndTypeInfo = (u1*)frame -> javaClass -> constant_pool[nameAndTypeIndex];

	// get name_index and descriptor_index of this method
	u2 nameIndexMethod = getu2(p_nameAndTypeInfo + 1);
	u2 descriptorIndex = getu2(p_nameAndTypeInfo + 3);

	// get string name and description of method
	std::string methodName, methodDescription;
	frame -> javaClass -> getAttrName(nameIndexMethod, methodName);
	frame -> javaClass -> getAttrName(descriptorIndex, methodDescription);

	Frame * invokedFrame = new Frame(methodName, methodDescription, className, frame -> stackFrame, frame -> classHeap);

	u2 numberOfparams = getNumberOfMethodParams(methodDescription);

	if( type == 0xb8)
		numberOfparams--;

	for (int i = numberOfparams; i >= 0; i--)
	{
		invokedFrame -> storeOperand( i, frame -> topPopOperand());
	}

	frameStack.push(invokedFrame);

	execute(invokedFrame);
}

int ExecutionUnit::executeNew(Frame * frame)
{
	u2 constPoolClassRef = getu2(&frame -> getMethod() . code_attr -> code[frame -> getPc() + 1]);

	u1 * p_classInfo = (u1*) frame -> javaClass -> constant_pool[constPoolClassRef];

	u2 classNameIndex = getu2(p_classInfo + 1);

	std::string className;
	frame -> javaClass -> getAttrName(classNameIndex, className);

	return objectHeap -> createObject(className);	
}

int ExecutionUnit::executeNewArray(Frame * frame)
{
	char arrayType = getu1(&frame -> getMethod() . code_attr -> code[frame -> getPc() + 1]);
	
	int length = frame -> topPopOperand() -> getValue();

	return objectHeap -> createArray(length, arrayType);	
}

u2 ExecutionUnit::getNumberOfMethodParams(std::string p_description)
{
	u2 	count = 0;
	int length = p_description.size();

	for (int i = 1; i < length; i++)
	{
		if(p_description[i] == 'L')
		{
			while(p_description[i] != ';')
			{
				i++;
			}
		}
		if(p_description[i] == ')')
		{
			break;
		}
		count++;
	}
	return count;
}

void ExecutionUnit::putfield(Frame * frame)
{
	u2 fieldref = getu2(&frame -> getMethod() . code_attr -> code[frame -> getPc() + 1]);

	// get constant_pool entry on this reference. Its CONSTANT_Fieldref_info structure
	u1 * p_fieldRefInfo = (u1*)frame -> javaClass -> constant_pool[fieldref];

	// get info from this constant_pool entry about method
	u2 nameAndTypeIndex = getu2(p_fieldRefInfo + 3);

	// get class info on this classIndex
	u1 * p_fieldInfo = (u1*)frame -> javaClass -> constant_pool[nameAndTypeIndex];

	// get name_index of this class (ref to constant_pool with class name)
	u2 fieldNameIndex = getu2(p_fieldInfo + 1);

	// get string name of this class from constant pool
	std::string fieldName;
	frame -> javaClass -> getAttrName(fieldNameIndex, fieldName);

	
	Operand * valueOp = frame -> topPopOperand();

	Operand * refOp = frame -> topPopOperand();

	DEBUG_MSG("Setting value of " + fieldName + " to: " + std::to_string(valueOp -> getValue()));

	objectHeap -> setObjectValue(refOp, fieldName, valueOp);
}

void ExecutionUnit::getField(Frame * frame)
{
	u2 fieldref = getu2(&frame -> getMethod() . code_attr -> code[frame -> getPc() + 1]);

	// get constant_pool entry on this reference. Its CONSTANT_Fieldref_info structure
	u1 * p_fieldRefInfo = (u1*)frame -> javaClass -> constant_pool[fieldref];

	// get info from this constant_pool entry about method
	u2 nameAndTypeIndex = getu2(p_fieldRefInfo + 3);

	// get class info on this classIndex
	u1 * p_fieldInfo = (u1*)frame -> javaClass -> constant_pool[nameAndTypeIndex];

	// get name_index of this class (ref to constant_pool with class name)
	u2 fieldNameIndex = getu2(p_fieldInfo + 1);

	// get string name of this class from constant pool
	std::string fieldName;
	frame -> javaClass -> getAttrName(fieldNameIndex, fieldName);

	Operand * refOp = frame -> topPopOperand();

	Operand * valueOp = objectHeap -> getObjectValue(refOp, fieldName);

	DEBUG_MSG("Getting value of " + fieldName + ". Value: " + std::to_string(valueOp -> getValue()));
	
	frame -> pushOperand(valueOp);
}
