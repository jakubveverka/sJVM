
#include <iostream>

#include "../include/debugMsg.hpp"
#include "../include/executionUnit.hpp"
#include "../include/definitions.hpp"
#include "../include/operands/intOperand.hpp"

	 ExecutionUnit::ExecutionUnit(std::stack<Frame*> p_frameStack)
{
	frameStack = p_frameStack;
}

void ExecutionUnit::execute()
{
	DEBUG_MSG("Executing" << std::endl);

	Frame * frame = frameStack.top();

	u1 *p = frame -> getMethod() . code_attr -> code;

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
				DEBUG_MSG("bipush operand: " + std::to_string((u1)(p[frame->getPc()+1])));
				IntOperand * pushOperand = new IntOperand((u1)(p[frame->getPc()+1]));
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
			case 0x2a:
				DEBUG_MSG("executing: aload_0");
				break;
			case 0x2b:
				DEBUG_MSG("executing: aload_1");
				break;
			case 0x2c:
				DEBUG_MSG("executing: aload_2");
				break;
			case 0x2d:
				DEBUG_MSG("executing: aload_3");
				break;
			case 0x2e:
				DEBUG_MSG("executing: iaload");
				break;
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
				DEBUG_MSG("executing: astore");
				break;
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
				DEBUG_MSG("executing: astore_0");
				break;
			case 0x4c:
				DEBUG_MSG("executing: astore_1");
				break;
			case 0x4d:
				DEBUG_MSG("executing: astore_2");
				break;
			case 0x4e:
				DEBUG_MSG("executing: astore_3");
				break;
			case 0x4f:
				DEBUG_MSG("executing: iastore");
				break;
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
				int firstOperand = frame -> topPopOperand() -> getValue();
				DEBUG_MSG("iadd: first operand: " + std::to_string(firstOperand));
				int secondOperand = frame -> topPopOperand() -> getValue();
				DEBUG_MSG("iadd: second operand: " + std::to_string(secondOperand));

				IntOperand * iaddResult = new IntOperand(firstOperand + secondOperand);
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
				int firstOperand = frame -> topPopOperand() -> getValue();
				DEBUG_MSG("isub: first operand: " + std::to_string(firstOperand));
				int secondOperand = frame -> topPopOperand() -> getValue();
				DEBUG_MSG("isub: second operand: " + std::to_string(secondOperand));

				IntOperand * isubResult = new IntOperand(secondOperand - firstOperand);
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
				int firstOperand = frame -> topPopOperand() -> getValue();
				DEBUG_MSG("imul: first operand: " + std::to_string(firstOperand));
				int secondOperand = frame -> topPopOperand() -> getValue();
				DEBUG_MSG("imul: second operand: " + std::to_string(secondOperand));

				IntOperand * imulResult = new IntOperand(firstOperand * secondOperand);
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
				int firstOperand = frame -> topPopOperand() -> getValue();
				DEBUG_MSG("idiv: first operand: " + std::to_string(firstOperand));
				int secondOperand = frame -> topPopOperand() -> getValue();
				DEBUG_MSG("idiv: second operand: " + std::to_string(secondOperand));

				IntOperand * idivResult = new IntOperand(secondOperand / firstOperand);
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
				DEBUG_MSG("executing: irem");
				break;
			//case 0x71:
				//TODO lrem
			//case 0x72:
				//TODO frem
			//case 0x73:
				//TODO drem
			case 0x74:
				DEBUG_MSG("executing: ineg");
				break;
			//case 0x75:
				//TODO lneg
			//case 0x76:
				//TODO fneg
			//case 0x77:
				//TODO dneg
			//case 0x78:
				//TODO ishl
			//case 0x79:
				//TODO lshl
			//case 0x7a:
				//TODO ishr
			//case 0x7b:
				//TODO lshr
			//case 0x7c:
				//TODO iushr
			//case 0x7d:
				//TODO lushr
			case 0x7e:
				DEBUG_MSG("executing: iand");
				break;
			case 0x7f:
				//TODO land
			case 0x80:
				DEBUG_MSG("executing: ior");
				break;
			//case 0x81:
				//TODO lor
			case 0x82:
				DEBUG_MSG("executing: ixor");
				break;
			//case 0x83:
				//TODO lxor
			case 0x84:
				DEBUG_MSG("executing: iinc");
				break;

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
				DEBUG_MSG("executing: ifeq");
				break;
			case 0x9a:
				DEBUG_MSG("executing: ifne");
				break;
			case 0x9b:
				DEBUG_MSG("executing: iflt");
				break;
			case 0x9c:
				DEBUG_MSG("executing: ifge");
				break;
			case 0x9d:
				DEBUG_MSG("executing: ifgt");
				break;
			case 0x9e:
				DEBUG_MSG("executing: ifle");
				break;
			case 0x9f:
				DEBUG_MSG("executing: if_icmpeq");
				break;
			case 0xa0:
				DEBUG_MSG("executing: if_icmpne");
				break;
			case 0xa1:
				DEBUG_MSG("executing: if_icmplt");
				break;
			case 0xa2:
				DEBUG_MSG("executing: if_icmpge");
				break;
			case 0xa3:
				DEBUG_MSG("executing: if_icmpgt");
				break;
			case 0xa4:
				DEBUG_MSG("executing: if_icmple");
				break;
			case 0xa5:
				DEBUG_MSG("executing: if_acmpeq");
				break;
			case 0xa6:
				DEBUG_MSG("executing: if_acmpne");
				break;

			// CONTROL /////////////////////////////////////////////////////////////
			case 0xa7:
				DEBUG_MSG("executing: goto");
				break;
			case 0xac:
				DEBUG_MSG("executing: ireturn");
				break;
			case 0xad:
				DEBUG_MSG("executing: lreturn");
				break;
			case 0xb0:
				DEBUG_MSG("executing: areturn");
				break;
			case 0xb1:
				DEBUG_MSG("executing: return");
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
				break;
			case 0xb5:
				DEBUG_MSG("executing: putfield");
				break;
			case 0xb6:
				DEBUG_MSG("executing: invokevirtual");
				break;
			case 0xb7:
				DEBUG_MSG("executing: invokespecial");
				break;
			case 0xb8:
				DEBUG_MSG("executing: invokestatic");
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
				break;
			case 0xbc:
				DEBUG_MSG("executing: newarray");
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
}
