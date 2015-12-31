
#include "../include/objectTable.hpp"
#include "../include/objectHeap.hpp"
#include "../include/frame.hpp"
#include "../include/operands/refOperand.hpp"
#include "../include/ref.hpp"
#include "../include/garbageCollector.hpp"
#include "../include/debugMsg.hpp"
#include "../include/objectRef.hpp"
#include "../include/arrayRef.hpp"
#include "../include/objectArrayRef.hpp"
#include "../include/operands/intOperand.hpp"

      GarbageCollector::GarbageCollector(ObjectHeap* p_objectHeap, ObjectTable* p_objectTable, std::stack<Frame*>* p_stackFrame)
{
   objectHeap = p_objectHeap;
   objectTable = p_objectTable;
   stackFrame = p_stackFrame;
   numberOfRuns = 0;
}

void GarbageCollector::execute()
{
   //objectTable->print();
   //objectHeap->print();
   DEBUG_MSG("garbage collector executed");
   numberOfRuns++;
   markLiveObjects();
   cleanHeap();
   DEBUG_MSG("garbage collector finished");
   //objectTable->print();
   //objectHeap->print();
}

void GarbageCollector::markLiveObjects()
{
   for(std::stack<Frame*> tmpStackFrame = *stackFrame; !tmpStackFrame.empty(); tmpStackFrame.pop()) {
      Frame* tmpFrame = tmpStackFrame.top();
      std::stack<Operand*>* frameOpStack = tmpFrame->getOpStack();

      for(std::stack<Operand*> tmpFrameOpStack = *frameOpStack; !tmpFrameOpStack.empty(); tmpFrameOpStack.pop()) {
         Operand* operand = tmpFrameOpStack.top();
         if(RefOperand* o = dynamic_cast<RefOperand*>(operand)) {
            if(o->getValue() != -1) {
               Ref* ref = objectTable->getRef(o->getValue());
               if(ref != nullptr && ref->getGcNumber() != numberOfRuns) {
                  ref->setGcNumber(numberOfRuns);
                  DEBUG_MSG("Finded live object with index " + std::to_string(o->getValue()) + " in object table and heapIndex " + std::to_string(ref->heapIndex));
                  findInsideObject(ref, o);
               }
            }
         }
      }

      for(int i = 0; i < tmpFrame->localVariablesSize; i++) {
         Operand* operand = tmpFrame->loadOperand(i);
         if(operand == nullptr) continue;
         if(RefOperand* o = dynamic_cast<RefOperand*>(operand)) {
            if(o->getValue() != -1) {
               Ref* ref = objectTable->getRef(o->getValue());
               if(ref != nullptr && ref->getGcNumber() != numberOfRuns) {
                  ref->setGcNumber(numberOfRuns);
                  DEBUG_MSG("Finded live object with index " + std::to_string(o->getValue()) + " in object table and heapIndex " + std::to_string(ref->heapIndex));
                  findInsideObject(ref, o);
               }
            }
         }
      }
   }
}

void GarbageCollector::findInsideObject(Ref* ref, RefOperand* refOperand)
{
   if(ObjectRef* oref = dynamic_cast<ObjectRef*>(ref)) {
      for(int i = 0; i < oref->classFile->fields_count; i++) {
         std::string fieldName;
         oref->classFile->getAttrName(oref->classFile->fields[i].name_index, fieldName);
         Operand* heapOperand = objectHeap->getObjectValue(refOperand, fieldName);
         if(RefOperand* o = dynamic_cast<RefOperand*>(heapOperand)) {
            if(o->getValue() != -1) {
               Ref* objectRef = objectTable->getRef(o->getValue()); //or array ref
               if(objectRef != nullptr && objectRef->getGcNumber() != numberOfRuns) {
                  objectRef->setGcNumber(numberOfRuns);
                  DEBUG_MSG("Finded live object with index " + std::to_string(o->getValue()) + " in object table and heapIndex " + std::to_string(objectRef->heapIndex));
                  findInsideObject(objectRef, o);
               }
            }
         }
      }
   } else if(dynamic_cast<ObjectArrayRef*>(ref)) {
      int arrayLength = objectHeap->getArrayLength(refOperand)->getValue();
      for(int i = 0; i < arrayLength; i++) {
         IntOperand* indexOperand = new IntOperand(i);
         Operand* arrayOperand = objectHeap->loadArrayOp(refOperand, indexOperand);
         delete indexOperand;
         if(RefOperand* o = dynamic_cast<RefOperand*>(arrayOperand)) {
            if(o->getValue() != -1) {
               Ref* objectRef = objectTable->getRef(o->getValue()); //or array ref
               if(objectRef != nullptr && objectRef->getGcNumber() != numberOfRuns) {
                  objectRef->setGcNumber(numberOfRuns);
                  DEBUG_MSG("Finded live object with index " + std::to_string(o->getValue()) + " in object table and heapIndex " + std::to_string(objectRef->heapIndex));
                  findInsideObject(objectRef, o);
               }
            }
         }
      }
   }
}

void GarbageCollector::cleanHeap()
{
   DEBUG_MSG("starting cleanheap");
   for(int i = 0; i < objectTable->tableSize; i++) {
      Ref* ref = objectTable->objectTable[i];
      if(ref != nullptr && ref->getGcNumber() != numberOfRuns) {
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
         } else if((dynamic_cast<ObjectArrayRef*>(ref)) || (dynamic_cast<ArrayRef*>(ref))) {
            int arrayLength = objectHeap->getArrayLength(refOperand)->getValue();
            DEBUG_MSG("Removing array with index " + std::to_string(i) + " in object table and with heapIndex " + std::to_string(ref->heapIndex) + " with lenght " + std::to_string(arrayLength));
            for(int j = 0; j < arrayLength; j++) {
               IntOperand* indexOperand = new IntOperand(j);
               Operand* arrayOperand = objectHeap->loadArrayOp(refOperand, indexOperand);
               int heapIndex = objectHeap->getArrayOpIndex(refOperand, indexOperand);
               delete indexOperand;
               delete arrayOperand;
               objectHeap->data[heapIndex] = nullptr;
            }
            //removing array length operand on the heap
            Operand* lengthOperand = objectHeap->data[ref->heapIndex];
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
   DEBUG_MSG("cleanup finished");
}
