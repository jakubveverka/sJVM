#ifndef NATIVEMETHODS_HPP_
#define NATIVEMETHODS_HPP_

class Frame;
class ObjectHeap;

void void_PrintStream_Print_String(Frame * frame, ObjectHeap * objectHeap);
void string_StdInputReader_ReadString_Void(Frame* frame, ObjectHeap* objectHeap);
void int_FileParserReader_readElementsCount_String(Frame* frame, ObjectHeap* objectHeap);
void twoDimenIntArray_FileParserReader_readAndParseFormula_String(Frame* frame, ObjectHeap* objectHeap);
void int_FileWriter_writeString_String_String(Frame* frame, ObjectHeap* objectHeap);
void int_FileWriter_writeInt_String_Int(Frame* frame, ObjectHeap* objectHeap);
void void_PrintStream_Print_Int(Frame * frame, ObjectHeap * objectHeap);

#endif /* NATIVEMETHODS_HPP_ */
