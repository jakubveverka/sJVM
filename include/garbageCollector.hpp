#ifndef GC_HPP_
#define GC_HPP_

#include "frame.hpp"
#include "objectTable.hpp"
#include "objectHeap.hpp"

class ObjectTable;
class ObjectHeap;

class GarbageCollector {
	private:

	public:
      ObjectHeap*          objectHeap;
	   ObjectTable*        objectTable;
      std::stack<Frame*>*  stackFrame;
      int                  numberOfRuns;

	public:
			 GarbageCollector(ObjectHeap* p_objectHeap, ObjectTable* p_objectTable, std::stack<Frame*>* p_stackFrame);
     void execute();
     void markLiveObjects();
     void findInsideObject(Ref* ref);
     void cleanHeap();
};

#endif /* GC_HPP_ */
