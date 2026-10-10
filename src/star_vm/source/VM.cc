#include "VM.hh"
#include "Exit.hh"
#include "Push.hh"

star::VM::VM(std::vector<size_t> instructions) :
	m_InstructionBuffer(std::move(instructions)),
	m_Running(false)
{
	m_InstructionSet.emplace(
		static_cast<uint16_t>(Opcode::EXIT),
		std::make_unique<Exit>(&m_Running)
	);

	m_InstructionSet.emplace(
		static_cast<uint16_t>(Opcode::PUSH_LOW),
		std::make_unique<PushLow>()
	);

	m_InstructionSet.emplace(
		static_cast<uint16_t>(Opcode::PUSH_HIGH),
		std::make_unique<PushHigh>()
	);

	m_InstructionSet.emplace(
		static_cast<uint16_t>(Opcode::NOP),
		nullptr
	);
}

star::VM::~VM()
{}

void star::VM::Run()
{
	m_Running = true;
	while (m_Running)
	{
#warning "MSVC bug of clang-cl: not displaying this"
		auto debugInfo = this;
		size_t* instructionIndex = m_RegisterBuffer.GetRegister(RegisterName::PC);
		ExecuteInstruction(m_InstructionBuffer[*instructionIndex]);
		(*instructionIndex)++;
	}
}

void star::VM::ExecuteInstruction(size_t instruction)
{
	uint16_t numOpcode = static_cast<uint16_t>(instruction >> 48);
	uint16_t numberOfOperands = static_cast<uint16_t>(numOpcode >> 14);
	size_t* registerOut = nullptr;
	size_t* registerIn1 = nullptr;
	size_t* registerIn2 = nullptr;

	switch (numberOfOperands)
	{
		case 3:
		{
			uint16_t registerIn2Index = static_cast<uint16_t>(instruction);
			registerIn2 = m_RegisterBuffer.GetRegister(static_cast<RegisterName>(registerIn2Index));
			[[fallthrough]];
		}
		case 2:
		{
			uint16_t registerIn1Index = static_cast<uint16_t>(instruction >> 16);
			registerIn1 = m_RegisterBuffer.GetRegister(static_cast<RegisterName>(registerIn1Index));
			[[fallthrough]];
		}
		case 1:
		{
			uint16_t registerOutIndex = static_cast<uint16_t>(instruction >> 32);
			registerOut = m_RegisterBuffer.GetRegister(static_cast<RegisterName>(registerOutIndex));
			[[fallthrough]];
		}
		default:
			break;
	}
	
	m_InstructionSet[numOpcode]->ExecuteTAC(registerOut, registerIn1, registerIn2, instruction);
}
