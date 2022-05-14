#include "VM/PkmVM.h"
#include "Opcodes.h"
#include "VM/Interpreter.h"
#include "VM/ClassLinker.h"

#include <bit>
#include <fstream>
#include <cstddef>
#include <stack>
#include <cstring>

#define ARIFMETIC_OPERATION(type, operation)                              \
{                                                                         \
    type value1 = std::bit_cast<type>(current_frame.operand_stack.top()); \
    current_frame.operand_stack.pop();                                    \
    type value2 = std::bit_cast<type>(current_frame.operand_stack.top()); \
    current_frame.operand_stack.pop();                                    \
                                                                          \
    int32_t result = std::bit_cast<int32_t>(value1 operation value2);     \
    current_frame.operand_stack.push(result);                             \
}

#define BIT_OPERATION(bit_operation)            \
{                                               \
    ARIFMETIC_OPERATION(int32_t, bit_operation) \
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"

void Interpreter::start_interpreting(pclass cls, pmethodID mid)
{
    static void* dispatch_table[] = {
        &&NOP           ,
        &&LDC           ,
        &&ILOAD         ,
        &&LLOAD         ,
        &&FLOAD         ,
        &&DLOAD         ,
        &&ALOAD         ,
        &&IALOAD        ,
        &&LALOAD        ,
        &&FALOAD        ,
        &&DALOAD        ,
        &&AALOAD        ,
        &&BALOAD        ,
        &&CALOAD        ,
        &&SALOAD        ,
        &&ISTORE        ,
        &&LSTORE        ,
        &&FSTORE        ,
        &&DSTORE        ,
        &&ASTORE        ,
        &&IASTORE       ,
        &&LASTORE       ,
        &&FASTORE       ,
        &&DASTORE       ,
        &&AASTORE       ,
        &&BASTORE       ,
        &&CASTORE       ,
        &&SASTORE       ,
        &&POP           ,
        &&POP2          ,
        &&DUP           ,
        &&DUP2          ,
        &&IADD          ,
        &&ISUB          ,
        &&IMUL          ,
        &&IDIV          ,
        &&LADD          ,
        &&LSUB          ,
        &&LMUL          ,
        &&LDIV          ,
        &&FADD          ,
        &&FSUB          ,
        &&FMUL          ,
        &&FDIV          ,
        &&DADD          ,
        &&DSUB          ,
        &&DMUL          ,
        &&DDIV          ,
        &&IREM          ,
        &&LREM          ,
        &&FREM          ,
        &&DREM          ,
        &&INEG          ,
        &&LNEG          ,
        &&FNEG          ,
        &&DNEG          ,
        &&ISHL          ,
        &&LSHL          ,
        &&ISHR          ,
        &&LSHR          ,
        &&IAND          ,
        &&LAND          ,
        &&IOR           ,
        &&LOR           ,
        &&IXOR          ,
        &&LXOR          ,
        &&I2L           ,
        &&I2F           ,
        &&I2D           ,
        &&L2I           ,
        &&L2F           ,
        &&L2D           ,
        &&F2I           ,
        &&F2L           ,
        &&F2D           ,
        &&D2I           ,
        &&D2L           ,
        &&D2F           ,
        &&I2B           ,
        &&I2C           ,
        &&I2S           ,
        &&IEQ           ,
        &&INEQ          ,
        &&ILEQ          ,
        &&IGEQ          ,
        &&ISTL          ,
        &&ISTG          ,
        &&LEQ           ,
        &&LNEQ          ,
        &&LLEQ          ,
        &&LGEQ          ,
        &&LSTL          ,
        &&LSTG          ,
        &&FEQ           ,
        &&FNEQ          ,
        &&FLEQ          ,
        &&FGEQ          ,
        &&FSTL          ,
        &&FSTG          ,
        &&DEQ           ,
        &&DNEQ          ,
        &&DLEQ          ,
        &&DGEQ          ,
        &&DSTL          ,
        &&DSTG          ,
        &&IF            ,
        &&IFN           ,
        &&GOTO          ,
        &&TABLESWITCH   ,
        &&LOOKUPSWITCH  ,
        &&IRETURN       ,
        &&LRETURN       ,
        &&FRETURN       ,
        &&DRETURN       ,
        &&ARETURN       ,
        &&RETURN        ,
        &&GETSTATIC     ,
        &&PUTSTATIC     ,
        &&GETFIELD      ,
        &&PUTFIELD      ,
        &&INVOKEINSTANCE,
        &&INVOKESTATIC  ,
        &&INVOKENATIVE  ,
        &&NEW           ,
        &&NEWARRAY      ,
        &&MULTINEWARRAY ,
        &&ANEWARRAY     ,
        &&AMULTINEWARRAY,
        &&ARRAYLENGTH
    };

    std::size_t  pc       = mid->offset;
    std::string* bytecode = &(cls->bytecode);
    
    pvm_->create_new_frame(mid);
    Frame& current_frame = pvm_->stack_frame.top();

    #define DISPATCH() goto *dispatch_table[static_cast<uint8_t>((*bytecode)[(pc += 4) - 4])]

    DISPATCH();
    while (true)
    {
        NOP:
        {
            DISPATCH();
        }
        LDC:
        {
            auto*   index_ptr = reinterpret_cast<uint16_t*>(&((*bytecode)[pc - 2]));
            auto*   val_ptr   = static_cast<IntegerType*>((current_frame.pmethod->cls->const_pool)[*index_ptr].get());
            int32_t value     = val_ptr->value;

            current_frame.operand_stack.push(value);
            DISPATCH();
        }
        ILOAD:
        {
            auto*   index_ptr = reinterpret_cast<uint16_t*>(&((*bytecode)[pc - 2]));
            int32_t value     = current_frame.local_variables[*index_ptr];
            current_frame.operand_stack.push(value);
            DISPATCH();
        }
        LLOAD:
            DISPATCH();
        FLOAD:
        {
            auto*   index_ptr = reinterpret_cast<uint16_t*>(&((*bytecode)[pc - 2]));
            int32_t value     = current_frame.local_variables[*index_ptr];
            current_frame.operand_stack.push(value);
            DISPATCH();
        }
        DLOAD:
            DISPATCH();
        ALOAD:
            DISPATCH();
        IALOAD:
            DISPATCH();
        LALOAD:
            DISPATCH();
        FALOAD         :
            DISPATCH();
        DALOAD         :
            DISPATCH();
        AALOAD         :
            DISPATCH();
        BALOAD         :
            DISPATCH();
        CALOAD         :
            DISPATCH();
        SALOAD         :
            DISPATCH();
        ISTORE:
        {
            auto* index_ptr = reinterpret_cast<uint16_t*>(&((*bytecode)[pc - 2]));
            int32_t value = current_frame.operand_stack.top();
            current_frame.operand_stack.pop();
            current_frame.local_variables[*index_ptr] = value;
            DISPATCH();
        }
        LSTORE:
            DISPATCH();
        FSTORE:
        {
            auto* index_ptr = reinterpret_cast<uint16_t*>(&((*bytecode)[pc - 2]));
            int32_t value = current_frame.operand_stack.top();
            current_frame.operand_stack.pop();
            current_frame.local_variables[*index_ptr] = value;
            DISPATCH();
        }
        DSTORE         :
            DISPATCH();
        ASTORE         :
            DISPATCH();
        IASTORE        :
            DISPATCH();
        LASTORE        :
            DISPATCH();
        FASTORE        :
            DISPATCH();
        DASTORE        :
            DISPATCH();
        AASTORE        :
            DISPATCH();
        BASTORE        :
            DISPATCH();
        CASTORE        :
            DISPATCH();
        SASTORE        :
            DISPATCH();
        POP:
        {
            current_frame.operand_stack.pop();
            DISPATCH();
        }
        POP2:
        {
            current_frame.operand_stack.pop();
            if (!current_frame.operand_stack.empty())
                current_frame.operand_stack.pop();
            
            DISPATCH();
        }
        DUP:
        {
            int32_t duplicate_value = current_frame.operand_stack.top();
            current_frame.operand_stack.push(duplicate_value);
            DISPATCH();
        }
        DUP2:
        {
            int32_t fir_dup_value = current_frame.operand_stack.top();
            current_frame.operand_stack.pop();
            int32_t sec_dup_value = current_frame.operand_stack.top();
            current_frame.operand_stack.push(fir_dup_value);
            current_frame.operand_stack.push(sec_dup_value);
            current_frame.operand_stack.push(fir_dup_value);
            DISPATCH();
        }
        IADD:
        {
            ARIFMETIC_OPERATION(int32_t, +);
            DISPATCH();
        }
        ISUB:
        {
            ARIFMETIC_OPERATION(int32_t, -);
            DISPATCH();
        }
        IMUL:
        {
            ARIFMETIC_OPERATION(int32_t, *);
            DISPATCH();
        }
        IDIV:
        {
            ARIFMETIC_OPERATION(int32_t, /);
            DISPATCH();
        }
        LADD:
            DISPATCH();
        LSUB:
            DISPATCH();
        LMUL:
            DISPATCH();
        LDIV:
            DISPATCH();
        FADD:
        {
            ARIFMETIC_OPERATION(float, +);
            DISPATCH();
        }
        FSUB:
        {
            ARIFMETIC_OPERATION(float, -);
            DISPATCH();
        }
        FMUL:
        {
            ARIFMETIC_OPERATION(float, *);
            DISPATCH();
        }
        FDIV:
        {
            ARIFMETIC_OPERATION(float, /);
            DISPATCH();
        }
        DADD:
            DISPATCH();
        DSUB:
            DISPATCH();
        DMUL:
            DISPATCH();
        DDIV:
            DISPATCH();
        IREM:
        {
            int32_t value1 = current_frame.operand_stack.top();
            current_frame.operand_stack.pop();
            int32_t value2 = current_frame.operand_stack.top();
            current_frame.operand_stack.pop();

            int32_t result = value1 - (value1 / value2) * value2;
            current_frame.operand_stack.push(result);
            DISPATCH();
        }
        LREM:
            DISPATCH();
        FREM:
        {
            float value1 = std::bit_cast<float>(current_frame.operand_stack.top());
            current_frame.operand_stack.pop();
            float value2 = std::bit_cast<float>(current_frame.operand_stack.top());
            current_frame.operand_stack.pop();

            float result = value1 - (value1 / value2) * value2;
            current_frame.operand_stack.push(std::bit_cast<int32_t>(result));
            DISPATCH();
        }
        DREM:
            DISPATCH();
        INEG:
        {
            int32_t value = current_frame.operand_stack.top();
            current_frame.operand_stack.pop();
            current_frame.operand_stack.push(-value);
            DISPATCH();
        }
        LNEG:
            DISPATCH();
        FNEG:
        {
            float value = std::bit_cast<float>(current_frame.operand_stack.top());
            current_frame.operand_stack.pop();
            current_frame.operand_stack.push(std::bit_cast<int32_t>(-value));
            DISPATCH();
        }
        DNEG:
            DISPATCH();
        ISHL:
        {
            BIT_OPERATION(<<);
            DISPATCH();
        }
        LSHL:
            DISPATCH();
        ISHR:
        {
            BIT_OPERATION(>>);
            DISPATCH();
        }
        LSHR:
            DISPATCH();
        IAND:
        {
            BIT_OPERATION(&);
            DISPATCH();
        }
        LAND:
            DISPATCH();
        IOR:
        {
            BIT_OPERATION(|);
            DISPATCH();
        }
        LOR:
            DISPATCH();
        IXOR:
        {
            BIT_OPERATION(^);
            DISPATCH();
        }
        LXOR:
            DISPATCH();
        I2L:
            DISPATCH();
        I2F:
        {
            int32_t value = current_frame.operand_stack.top();
            current_frame.operand_stack.pop();
            float convert_val = static_cast<float>(value);
            current_frame.operand_stack.push(std::bit_cast<int32_t>(convert_val));
            DISPATCH();
        }
        I2D:
            DISPATCH();
        L2I:
            DISPATCH();
        L2F:
            DISPATCH();
        L2D:
            DISPATCH();
        F2I:
        {
            float value = std::bit_cast<float>(current_frame.operand_stack.top());
            current_frame.operand_stack.pop();
            int32_t convert_val = static_cast<int32_t>(value);
            current_frame.operand_stack.push(convert_val);
            DISPATCH();
        }
        F2L:
            DISPATCH();
        F2D:
            DISPATCH();
        D2I:
            DISPATCH();
        D2L:
            DISPATCH();
        D2F:
            DISPATCH();
        I2B:
            DISPATCH();
        I2C:
            DISPATCH();
        I2S:
            DISPATCH();
        IEQ:
            DISPATCH();
        INEQ:
            DISPATCH();
        ILEQ:
            DISPATCH();
        IGEQ:
            DISPATCH();
        ISTL:
            DISPATCH();
        ISTG:
            DISPATCH();
        LEQ:
            DISPATCH();
        LNEQ:
            DISPATCH();
        LLEQ:
            DISPATCH();
        LGEQ:
            DISPATCH();
        LSTL:
            DISPATCH();
        LSTG:
            DISPATCH();
        FEQ :
            DISPATCH();
        FNEQ:
            DISPATCH();
        FLEQ:
        DISPATCH();
        FGEQ:
        DISPATCH();
        FSTL:
        DISPATCH();
        FSTG:
        DISPATCH();
        DEQ :
        DISPATCH();
        DNEQ:
        DISPATCH();
        DLEQ:
        DISPATCH();
        DGEQ:
        DISPATCH();
        DSTL:
        DISPATCH();
        DSTG:
        DISPATCH();
        IF  :
        DISPATCH();
        IFN :
        DISPATCH();

        GOTO:
            DISPATCH();
        TABLESWITCH:
            DISPATCH();
        LOOKUPSWITCH:
            DISPATCH();
        IRETURN:
        {
            int32_t return_value = current_frame.operand_stack.top();
            current_frame.operand_stack.pop();
            
            pvm_->stack_frame.pop();
            if (pvm_->stack_frame.empty())
                return;

            current_frame = pvm_->stack_frame.top();
            
            current_frame.operand_stack.push(return_value);
            pc = current_frame.pc;
            bytecode = &(current_frame.pmethod->cls->bytecode);

            DISPATCH();
        }
        LRETURN:
            DISPATCH();
        FRETURN:
        {
            DISPATCH();
        }
        DRETURN:
            DISPATCH();
        ARETURN:
            DISPATCH();
        RETURN:
        {
            pvm_->stack_frame.pop();
            if (pvm_->stack_frame.empty())
                return;

            current_frame = pvm_->stack_frame.top();
            pc = current_frame.pc;
            bytecode = &(current_frame.pmethod->cls->bytecode);

            DISPATCH();
        }
        GETSTATIC:
            DISPATCH();
        PUTSTATIC:
            DISPATCH();
        GETFIELD:
            DISPATCH();
        PUTFIELD:
            DISPATCH();
        INVOKEINSTANCE:
            DISPATCH();
        INVOKESTATIC:
        {
            current_frame.pc = pc;

            auto* index_ptr = reinterpret_cast<uint16_t*>(&((*bytecode)[pc - 2]));
            auto* val_ptr   = static_cast<PointerType*>((current_frame.pmethod->cls->const_pool)[*index_ptr].get());
            auto  pmethod   = std::bit_cast<pmethodID>(val_ptr->value);
            
            int nmb_args = pmethod->met_params.size();
            auto* args = new int32_t[nmb_args];

            for (int i = nmb_args - 1; i >= 0; --i)
            {
                args[i] = current_frame.operand_stack.top();
                current_frame.operand_stack.pop();
            }

            pvm_->create_new_frame(pmethod);
            current_frame = pvm_->stack_frame.top();

            memcpy(current_frame.local_variables, args, nmb_args * sizeof(int32_t));

            pc = current_frame.pmethod->offset;
            bytecode = &(current_frame.pmethod->cls->bytecode);
            
            DISPATCH();
        }
        INVOKENATIVE:
            DISPATCH();
        NEW:
            DISPATCH();
        NEWARRAY:
            DISPATCH();
        MULTINEWARRAY:
            DISPATCH();
        ANEWARRAY:
            DISPATCH();
        AMULTINEWARRAY:
            DISPATCH();
        ARRAYLENGTH:
            DISPATCH();
    }
}

#pragma GCC diagnostic pop
