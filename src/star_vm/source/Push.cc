#include "Push.hh"
#include "RegisterBuffer.hh"

star::PushLow::PushLow()
{}

void star::PushLow::ExecuteTAC(size_t* registerOut, size_t* registerIn1, size_t* registerIn2, size_t instruction) const
{
	size_t lowWord = static_cast<size_t>(instruction & 0x00000000FFFFFFFF);
	*registerOut = lowWord;
}

star::PushHigh::PushHigh()
{}

void star::PushHigh::ExecuteTAC(size_t* registerOut, size_t* registerIn1, size_t* registerIn2, size_t instruction) const
{
	size_t highWord = static_cast<size_t>(instruction & 0x00000000FFFFFFFF) << 32;
	size_t lowWord = (*registerOut & 0x00000000FFFFFFFF);
	*registerOut = highWord | lowWord;
}
