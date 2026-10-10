#pragma once

#include "StarVMMacro.hh"
#include "RegisterBuffer.hh"
#include <vector>
#include <unordered_map>
#include <memory>
#include "Execute.hh"
#include "Opcodes.hh"

namespace star
{
	class STAR_VM_API VM
	{
	public:
		VM(std::vector<size_t> instructions);
		~VM();

		VM(const VM&) = delete;
		VM& operator=(const VM&) = delete;

		VM(VM&&) = default;
		VM& operator=(VM&&) = default;

		void Run();
		void ExecuteInstruction(size_t instruction);
	private:
		std::vector<size_t> m_InstructionBuffer;
		RegisterBuffer m_RegisterBuffer;
		bool m_Running;
		std::unordered_map<uint16_t, std::unique_ptr<Execute>> m_InstructionSet;
	};
}