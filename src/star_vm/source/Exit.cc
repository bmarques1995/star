#include "Exit.hh"

star::Exit::Exit(bool* running) :
	m_Running(running)
{

}

void star::Exit::ExecuteTAC(size_t* registerOut, size_t* registerIn1, size_t* registerIn2, size_t instruction) const
{
	size_t exitCode = static_cast<size_t>(instruction & 0x00000000FFFFFFFF);
	*registerOut = exitCode;
	*m_Running = false;	
}
