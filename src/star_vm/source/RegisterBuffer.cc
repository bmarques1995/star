#include "RegisterBuffer.hh"

star::RegisterBuffer::RegisterBuffer()
{
	for (size_t i = 0; i < 256; i++)
	{
		m_Registers[i] = 0;
	}
}

size_t* star::RegisterBuffer::GetRegister(RegisterName index)
{
	return &m_Registers[static_cast<size_t>(index)];
}
