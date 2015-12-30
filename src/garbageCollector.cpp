
#include "../include/objectTable.hpp"
#include "../include/objectHeap.hpp"
#include "../include/frame.hpp"
#include "../include/operands/RefOperand.hpp"
#include "../include/ref.hpp"
#include "../include/garbageCollector.hpp"
#include "../include/debugMsg.hpp"

      GarbageCollector::GarbageCollector(ObjectHeap* p_objectHeap, ObjectTable* p_objectTable, std::stack<Frame*>* p_stackFrame)
{
   objectHeap = p_objectHeap;
   objectTable = p_objectTable;
   stackFrame = p_stackFrame;
   numberOfRuns = 0;
}

void GarbageCollector::execute()
{
   DEBUG_MSG("garbage collector executed");
   objectTable->print();
   objectHeap->print();
   numberOfRuns++;
   markLiveObjects();
   cleanHeap();
   DEBUG_MSG("garbage collector finished");
}

void GarbageCollector::markLiveObjects()
{
   for(std::stack<Frame*> tmpStackFrame = *stackFrame; !tmpStackFrame.empty(); tmpStackFrame.pop()) {
      Frame* tmpFrame = tmpStackFrame.top();
      std::stack<Operand*>* frameOpStack = tmpFrame->getOpStack();

      for(std::stack<Operand*> tmpFrameOpStack = *frameOpStack; !tmpFrameOpStack.empty(); tmpFrameOpStack.pop()) {
         Operand* operand = tmpFrameOpStack.top();
         if(RefOperand* o = dynamic_cast<RefOperand*>(operand)) {
            Ref* ref = objectTable->getRef(o->getValue());
            if(ref != nullptr && ref->getGcNumber() != numberOfRuns) {
               ref->setGcNumber(numberOfRuns);
               DEBUG_MSG("Finded live object with index " + std::to_string(o->getValue()) + " in object table and heapIndex " + std::to_string(ref->heapIndex));
               findInsideObject(ref);
            }
         }
      }

      for(int i = 0; i < tmpFrame->localVariables.size(); i++) {
         Operand* operand = tmpFrame->loadOperand(i);
         if(RefOperand* o = dynamic_cast<RefOperand*>(operand)) {
            Ref* ref = objectTable->getRef(o->getValue());
            if(ref != nullptr && ref->getGcNumber() != numberOfRuns) {
               ref->setGcNumber(numberOfRuns);
               DEBUG_MSG("Finded live object with index " + std::to_string(o->getValue()) + " in object table and heapIndex " + std::to_string(ref->heapIndex));
               findInsideObject(ref);
            }
         }
      }
   }
}

void GarbageCollector::findInsideObject(Ref* ref)
{

}

void GarbageCollector::cleanHeap()
{

}
