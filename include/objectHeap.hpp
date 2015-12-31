#ifndef OBJECTHEAP_HPP_
#define OBJECTHEAP_HPP_

#include <string>
#include <cstdlib>

class ClassHeap;
class Operand;
class ObjectTable;
class GarbageCollector;

class ObjectHeap{
	private:

	public:
		Operand	   ** data;
		int    	      heapSize = 1000;
		ClassHeap   * classHeap;
		ObjectTable * objectTable;
		GarbageCollector * garbageCollector = NULL;

	public:
			 	  ObjectHeap(ClassHeap * pClassHeap, ObjectTable * objectTable);
		int  	  createObject(std::string className);
		int		  createArray(int length, char arrayType);
		int 	  createObjectArray(int length,std::string className);
		int	 	  createString(std::string stringValue);
		int  	  getFreeSpace(int objectSize);
		Operand * getArrayLength(Operand * refOp);
		void 	  setObjectValue(Operand * refOp, std::string fieldName, Operand * valueOp);
		Operand * getObjectValue(Operand * refOp, std::string fieldName);
		Operand * loadArrayOp(Operand * refOp, Operand * indexOp);
		void	  storeArrayOp(Operand * refOp, Operand * indexOp, Operand * valueOp);
		void    setGarbageCollector(GarbageCollector* pGarbageCollector);
		void 	  print();
		int	  getFieldHeapIndex(Operand * refOp, std::string fieldName);
		int 	  getArrayOpIndex(Operand * refOp, Operand * indexOp);
		Operand* getOperandOnHeap(Operand * refOp);

};

#endif /* OBJECTHEAP_HPP_ */
