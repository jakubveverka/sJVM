
#include <iostream>
#include <fstream>
#include <vector>

#include "../include/nativeMethods.hpp"
#include "../include/frame.hpp"
#include "../include/objectHeap.hpp"
#include "../include/objectTable.hpp"
#include "../include/debugMsg.hpp"
#include "../include/operands/operand.hpp"
#include "../include/operands/refOperand.hpp"

void void_PrintStream_Print_String(Frame * frame, ObjectHeap * objectHeap)
{
	DEBUG_MSG("starting native print");
	Operand * refOp = frame -> loadOperand(0);

	Operand * valueOp = objectHeap -> getOperandOnHeap(refOp);

	std::cout << "PROGRAM OUTPUT ---> "<< valueOp -> getStringValue() << std::endl;

	frame->stackFrame->pop();
	DEBUG_MSG("finishing native print");
}

void void_PrintStream_Print_Int(Frame * frame, ObjectHeap * objectHeap)
{
	DEBUG_MSG("starting native print int");
	Operand * valueOp = frame -> loadOperand(0);

	std::cout << "PROGRAM OUTPUT ---> "<< valueOp -> getValue() << std::endl;

	frame->stackFrame->pop();
	DEBUG_MSG("finishing native print int");
}


void string_StdInputReader_ReadString_Void(Frame* frame, ObjectHeap* objectHeap)
{
	DEBUG_MSG("starting native std input reader");
	std::string input;
	std::cout << "PROGRAM INPUT ---> ";
	std::cin >> input;

	RefOperand* refOperand = new RefOperand(objectHeap->createString(input));

	frame->stackFrame->pop();
	frame->stackFrame->top()->pushOperand(refOperand);
	DEBUG_MSG("finishing native std input reader");
}

void int_FileParserReader_readElementsCount_String(Frame* frame, ObjectHeap* objectHeap)
{
	DEBUG_MSG("starting FileParserReader readElementsCount");
	Operand * refOp = frame -> loadOperand(0);
	Operand * fileNameOp = objectHeap -> getOperandOnHeap(refOp);

	std::ifstream inputFile;
	inputFile.open("test/SAT/"+fileNameOp->getStringValue(), std::ios::in);

	if(!inputFile.is_open()) {
		IntOperand* elementsCountOperand = new IntOperand(-1);
		frame->stackFrame->pop();
		frame->stackFrame->top()->pushOperand(elementsCountOperand);
		DEBUG_MSG("error in FileParserReader readElementsCount");
		return;
	}

	int elementsCount;
	inputFile >> elementsCount;

	IntOperand* elementsCountOperand = new IntOperand(elementsCount);
	frame->stackFrame->pop();
	frame->stackFrame->top()->pushOperand(elementsCountOperand);
	inputFile.close();
	DEBUG_MSG("finishing FileParserReader readElementsCount");
}

void twoDimenIntArray_FileParserReader_readAndParseFormula_String(Frame* frame, ObjectHeap* objectHeap)
{
	DEBUG_MSG("starting FileParserReader readAndParseFormula");
	Operand * refOp = frame -> loadOperand(0);
	Operand * fileNameOp = objectHeap -> getOperandOnHeap(refOp);

	std::ifstream inputFile;
	inputFile.open("test/SAT/"+fileNameOp->getStringValue(), std::ios::in);
	if(!inputFile.is_open()) {
		//TODO
		DEBUG_MSG("error in FileParserReader readAndParseFormula");
		return;
	}

	std::string line;
	getline(inputFile, line); //reads number of elements

	getline(inputFile,line); //reads formula!

	DEBUG_MSG("formula = " + line);

	std::vector<std::vector<int>> formula;
	std::vector<int> emptyVector;
	formula.push_back(emptyVector);
	int deep = 0;
	for(int i = 1; i < (line.length()-1); i++) { //cuts off brackets in formula
		if(line[i] == '(') {
			deep = 1;
			continue;
		}
		if(line[i] == ')' && i != (line.length()-2)) {
			formula.push_back(emptyVector);
			deep = 0;
			continue;
		}
		if(line[i] == ' ') continue;

		if(line[i] == '|') formula.back().push_back(-1);
		else if(line[i] == '&') formula.back().push_back(-2);
		else if(line[i] == '!') formula.back().push_back(-3);
		else formula.back().push_back(line[i] - 'a');

		if(deep == 0 && i != (line.length()-2)) formula.push_back(emptyVector);
	}

	RefOperand* objectArrayRef = new RefOperand(objectHeap->createObjectArray(formula.size(), "[I"));
	for(int i = 0; i < formula.size(); i++) {
		RefOperand* arrayRef = new RefOperand(objectHeap->createArray(formula[i].size(), 10));
		IntOperand* indexOp = new IntOperand(i);
		objectHeap->storeArrayOp(objectArrayRef, indexOp, arrayRef);
		for(int j = 0; j < formula[i].size(); j++) {
			IntOperand* indexOp2 = new IntOperand(j);
			IntOperand* intOp = new IntOperand(formula[i][j]);
			objectHeap->storeArrayOp(arrayRef, indexOp2, intOp);
		}
	}

	frame->stackFrame->pop();
	frame->stackFrame->top()->pushOperand(objectArrayRef);

	DEBUG_MSG("finishing FileParserReader readAndParseFormula");
}

void int_FileWriter_writeString_String_String(Frame* frame, ObjectHeap* objectHeap)
{
	DEBUG_MSG("starting FileWriter writeString");
	Operand * refOp = frame -> loadOperand(0);
	Operand * fileNameOp = objectHeap -> getOperandOnHeap(refOp);

	std::ofstream outputFile;
	outputFile.open("test/SAT/"+fileNameOp->getStringValue(), std::ios::out | std::ios::app);
	if(!outputFile.is_open()) {
		IntOperand* returnOperand = new IntOperand(-1);
		frame->stackFrame->pop();
		frame->stackFrame->top()->pushOperand(returnOperand);
		DEBUG_MSG("error in FileWriter writeString");
		return;
	}

	Operand * stringOp = frame -> loadOperand(1);
	Operand * stringToWriteOp = objectHeap -> getOperandOnHeap(stringOp);
	outputFile << stringToWriteOp->getStringValue() << "\n";
	IntOperand* returnOperand = new IntOperand(0);
	frame->stackFrame->pop();
	frame->stackFrame->top()->pushOperand(returnOperand);
	outputFile.close();
	DEBUG_MSG("finishing FileWriter writeString");
}

void int_FileWriter_writeInt_String_Int(Frame* frame, ObjectHeap* objectHeap)
{
	DEBUG_MSG("starting FileWriter writeInt");
	Operand * refOp = frame -> loadOperand(0);
	Operand * fileNameOp = objectHeap -> getOperandOnHeap(refOp);

	std::ofstream outputFile;
	outputFile.open("test/SAT/"+fileNameOp->getStringValue(), std::ios::out | std::ios::app);
	if(!outputFile.is_open()) {
		IntOperand* returnOperand = new IntOperand(-1);
		frame->stackFrame->pop();
		frame->stackFrame->top()->pushOperand(returnOperand);
		DEBUG_MSG("error FileWriter writeInt");
		return;
	}

	Operand * intOp = frame -> loadOperand(1);
	outputFile << intOp->getValue() << "\n";
	IntOperand* returnOperand = new IntOperand(0);
	frame->stackFrame->pop();
	frame->stackFrame->top()->pushOperand(returnOperand);
	outputFile.close();
	DEBUG_MSG("finishing FileWriter writeInt");
}
