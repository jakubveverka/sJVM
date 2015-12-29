#ifndef OBJECTHEAP_HPP_
#define OBJECTHEAP_HPP_

#include <string>

class ClassHeap;
class Operand;
class ObjectTable;

class ObjectHeap{
	private:

	public:
		Operand	   ** data;
		int    	      heapSize = 1000;
		ClassHeap   * classHeap;
		ObjectTable * objectTable;

	public:
			 	  ObjectHeap(ClassHeap * pClassHeap, ObjectTable * objectTable);
		int  	  createObject(std::string className);
		int		  createArray(int length, char arrayType);
		int	 	  createString(std::string stringValue);
		int  	  getFreeSpace(int objectSize);
		void 	  setObjectValue(Operand * refOp, std::string fieldName, Operand * valueOp);
		Operand * getObjectValue(Operand * refOp, std::string fieldName);
		Operand * loadArrayOp(Operand * refOp, Operand * indexOp);					
		void	  storeArrayOp(Operand * refOp, Operand * indexOp, Operand * valueOp);					

};

#endif /* OBJECTHEAP_HPP_ */