
#include "../include/objectTable.hpp"
#include "../include/objectHeap.hpp"
#include "../include/frame.hpp"
#include "../include/operands/RefOperand.hpp"
#include "../include/ref.hpp"
#include "../include/garbageCollector.hpp"
#include "../include/debugMsg.hpp"
#include "../include/objectRef.hpp"
#include "../include/arrayRef.hpp"
#include "../include/operands/IntOperand.hpp"

      GarbageCollector::GarbageCollector(ObjectHeap* p_objectHeap, ObjectTable* p_objectTable, std::stack<Frame*>* p_stackFrame)
{
   objectHeap = p_objectHeap;
   objectTable = p_objectTable;
   stackFrame = p_stackFrame;
   numberOfRuns = 0;
}

void GarbageCollector::execute()
{
   objectTable->print();
   objectHeap->print();
   DEBUG_MSG("garbage collector executed");
   numberOfRuns++;
   markLiveObjects();
   cleanHeap();
   DEBUG_MSG("garbage collector finished");
   objectTable->print();
   objectHeap->print();
}

void GarbageCollector::markLiveObjects()
{
   for(std::stack<Frame*> tmpStackFrame = *stackFrame; !tmpStackFrame.empty(); tmpStackFrame.pop()) {
      DEBUG_MSG("markliveobjects first");
      Frame* tmpFrame = tmpStackFrame.top();
      std::stack<Operand*>* frameOpStack = tmpFrame->getOpStack();

      for(std::stack<Operand*> tmpFrameOpStack = *frameOpStack; !tmpFrameOpStack.empty(); tmpFrameOpStack.pop()) {
         DEBUG_MSG("popuju stack");
         Operand* operand = tmpFrameOpStack.top();
         if(RefOperand* o = dynamic_cast<RefOperand*>(operand)) {
            Ref* ref = objectTable->getRef(o->getValue());
            if(ref != nullptr && ref->getGcNumber() != numberOfRuns) {
               ref->setGcNumber(numberOfRuns);
               DEBUG_MSG("Finded live object with index " + std::to_string(o->getValue()) + " in object table and heapIndex " + std::to_string(ref->heapIndex));
               findInsideObject(ref, o);
            }
         }
      }

      for(int i = 0; i < tmpFrame->localVariablesSize; i++) {
         Operand* operand = tmpFrame->loadOperand(i);
         if(operand == nullptr) continue;
         DEBUG_MSG("prohledavam promeny");
         if(RefOperand* o = dynamic_cast<RefOperand*>(operand)) {
            Ref* ref = objectTable->getRef(o->getValue());
            if(ref != nullptr && ref->getGcNumber() != numberOfRuns) {
               ref->setGcNumber(numberOfRuns);
               DEBUG_MSG("Finded live object with index " + std::to_string(o->getValue()) + " in object table and heapIndex " + std::to_string(ref->heapIndex));
               findInsideObject(ref, o);
            }
         }
      }
   }
   DEBUG_MSG("ending markliveobjects");
}

void GarbageCollector::findInsideObject(Ref* ref, RefOperand* refOperand)
{
   DEBUG_MSG("findInsideObject start");
   if(ObjectRef* oref = dynamic_cast<ObjectRef*>(ref)) {
      DEBUG_MSG("findInsideObject object ref");
      for(int i = 0; i < oref->classFile->fields_count; i++) {
         DEBUG_MSG("findInsideObject fieeelds");
         std::string fieldName;
         oref->classFile->getAttrName(oref->classFile->fields[i].name_index, fieldName);
         DEBUG_MSG("findInsideObject fieeelds name " + fieldName);
         Operand* heapOperand = objectHeap->getObjectValue(refOperand, fieldName);
         DEBUG_MSG("ahoj");
         if(RefOperand* o = dynamic_cast<RefOperand*>(heapOperand)) {
            DEBUG_MSG("findInsideObject object refoperand");
            Ref* objectRef = objectTable->getRef(o->getValue()); //or array ref
            if(objectRef != nullptr && objectRef->getGcNumber() != numberOfRuns) {
               objectRef->setGcNumber(numberOfRuns);
               DEBUG_MSG("Finded live object with index " + std::to_string(o->getValue()) + " in object table and heapIndex " + std::to_string(objectRef->heapIndex));
               findInsideObject(objectRef, o);
            }
         }
      }
   } else if(dynamic_cast<ArrayRef*>(ref)) {
      DEBUG_MSG("findInsideObject arrayref");
      int arrayLength = objectHeap->getArrayLength(refOperand)->getValue();
      for(int i = 0; i < arrayLength; i++) {
         DEBUG_MSG("findInsideObject array fields");
         IntOperand* indexOperand = new IntOperand(i);
         Operand* arrayOperand = objectHeap->loadArrayOp(refOperand, indexOperand);
         delete indexOperand;
         if(RefOperand* o = dynamic_cast<RefOperand*>(arrayOperand)) {
            DEBUG_MSG("findInsideObject array refoperand");
            Ref* objectRef = objectTable->getRef(o->getValue()); //or array ref
            if(objectRef != nullptr && objectRef->getGcNumber() != numberOfRuns) {
               objectRef->setGcNumber(numberOfRuns);
               DEBUG_MSG("Finded live object with index " + std::to_string(o->getValue()) + " in object table and heapIndex " + std::to_string(objectRef->heapIndex));
               findInsideObject(objectRef, o);
            }
         }
      }
   } else {
      DEBUG_MSG("ERROR: Unknown ref type to object table");
   }
   DEBUG_MSG("endfind inside object");
}

void GarbageCollector::cleanHeap()
{
   DEBUG_MSG("starting cleanheap");
   for(int i = 0; i < objectTable->tableSize; i++) {
      Ref* ref = objectTable->objectTable[i];
      if(ref != nullptr && ref->getGcNumber() != numberOfRuns) {
         DEBUG_MSG("cleanheap gc is not equal");
         IntOperand* refOperand = new IntOperand(i);
         if(ObjectRef* oref = dynamic_cast<ObjectRef*>(ref)) {
            DEBUG_MSG("Removing object with index " + std::to_string(i) + " in object table and with heapIndex " + std::to_string(oref->heapIndex) + " with fieldsCount " + std::to_string(oref->classFile->fields_count));
            for(int j = 0; j < oref->classFile->fields_count; j++) {
               std::string fieldName;
               oref->classFile->getAttrName(oref->classFile->fields[j].name_index, fieldName);
               Operand* heapOperand = objectHeap->getObjectValue(refOperand, fieldName);
               int heapIndex = objectHeap->getFieldHeapIndex(refOperand, fieldName);
               delete heapOperand;
               objectHeap->data[heapIndex] = nullptr;
            }
         } else if(ArrayRef* aref = dynamic_cast<ArrayRef*>(ref)) {
            int arrayLength = objectHeap->getArrayLength(refOperand)->getValue();
            DEBUG_MSG("Removing array with index " + std::to_string(i) + " in object table and with heapIndex " + std::to_string(aref->heapIndex) + " with lenght " + std::to_string(arrayLength));
            for(int j = 0; j < arrayLength; j++) {
               IntOperand* indexOperand = new IntOperand(j);
               Operand* arrayOperand = objectHeap->loadArrayOp(refOperand, indexOperand);
               int heapIndex = objectHeap->getArrayOpIndex(refOperand, indexOperand);
               delete indexOperand;
               delete arrayOperand;
               objectHeap->data[heapIndex] = nullptr;
            }
            //removing array length operand on the heap
            Operand* lengthOperand = objectHeap->data[aref->heapIndex];
            delete lengthOperand;
            objectHeap->data[ref->heapIndex] = nullptr;
         } else {
            DEBUG_MSG("ERROR: Unknown ref type to object table");
         }
         delete ref;
         objectTable->objectTable[i] = nullptr;
         delete refOperand;
      }
   }
   DEBUG_MSG("ending cleanup");
}
