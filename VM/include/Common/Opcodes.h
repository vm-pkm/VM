#ifndef OPCODES_H
#define OPCODES_H

enum class Opcode
{
	NOP            = 0x00,
	LDC            = 0x01,
	ILOAD          = 0x02,
	LLOAD          = 0x03,
	FLOAD          = 0x04,
	DLOAD          = 0x05,
	ALOAD          = 0x06,
	IALOAD         = 0x07,
	LALOAD         = 0x08,
	FALOAD         = 0x09,
	DALOAD         = 0x0A,
	AALOAD         = 0x0B,
	BALOAD         = 0x0C,
	CALOAD         = 0x0D,
	SALOAD         = 0x0E,
	ISTORE         = 0x0F,
	LSTORE         = 0x10,
	FSTORE         = 0x11,
	DSTORE         = 0x12,
	ASTORE         = 0x13,
	IASTORE        = 0x14,
	LASTORE        = 0x15,
	FASTORE        = 0x16,
	DASTORE        = 0x17,
	AASTORE        = 0x18,
	BASTORE        = 0x19,
	CASTORE        = 0x1A,
	SASTORE        = 0x1B,
	POP            = 0x1C,
	POP2           = 0x1D,
	DUP            = 0x1E,
	DUP2           = 0x1F,
	IADD           = 0x20,
	ISUB           = 0x21,
	IMUL           = 0x22,
	IDIV           = 0x23,
	LADD           = 0x24,
	LSUB           = 0x25,
	LMUL           = 0x26,
	LDIV           = 0x27,
	FADD           = 0x28,
	FSUB           = 0x29,
	FMUL           = 0x2A,
	FDIV           = 0x2B,
	DADD           = 0x2C,
	DSUB           = 0x2D,
	DMUL           = 0x2E,
	DDIV           = 0x2F,
	IREM           = 0x30,
	LREM           = 0x31,
	FREM           = 0x32,
	DREM           = 0x33,
	INEG           = 0x34,
	LNEG           = 0x35,
	FNEG           = 0x36,
	DNEG           = 0x37,
	ISHL           = 0x38,
	LSHL           = 0x39,
	ISHR           = 0x3A,
	LSHR           = 0x3B,
	IAND           = 0x3C,
	LAND           = 0x3D,
	IOR            = 0x3E,
	LOR            = 0x3F,
	IXOR           = 0x40,
	LXOR           = 0x41,
	IINC           = 0x42,
	I2L            = 0x43,
	I2F            = 0x44,
	I2D            = 0x45,
	L2I            = 0x46,
	L2F            = 0x47,
	L2D            = 0x48,
	F2I            = 0x49,
	F2L            = 0x4A,
	F2D            = 0x4B,
	D2I            = 0x4C,
	D2L            = 0x4D,
	D2F            = 0x4E,
	I2B            = 0x4F,
	I2C            = 0x50,
	I2S            = 0x51,
	ICMP           = 0x52,
	LCMP           = 0x53,
	FCMPL          = 0x54,
	FCMPG          = 0x55,
	DCMPL          = 0x56,
	DCMPG          = 0x57,
	IFEQ           = 0x58,
	IFNE           = 0x59,
	IFLT           = 0x5A,
	IFGE           = 0x5B,
	IFGT           = 0x5C,
	IFLE           = 0x5D,
	GOTO           = 0x5E,
	TABLESWITCH    = 0x5F,
	LOOKUPSWITCH   = 0x60,
	IRETURN        = 0x61,
	LRETURN        = 0x62,
	FRETURN        = 0x63,
	DRETURN        = 0x64,
	ARETURN        = 0x65,
	RETURN         = 0x66,
	GETSTATIC      = 0x67,
	PUTSTATIC      = 0x68,
	GETFIELD       = 0x69,
	PUTFIELD       = 0x6A,
	INVOKEINSTANCE = 0x6B,
	INVOKESTATIC   = 0x6C,
	INVOKENATIVE   = 0x6D,
	NEW            = 0x6E,
	NEWARRAY       = 0x6F,
	MULTINEWARRAY  = 0x70,
	ANEWARRAY      = 0x71,
	AMULTINEWARRAY = 0x72,
	ARRAYLENGTH    = 0x73,
};

#endif // OPCODES_H