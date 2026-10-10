#pragma once

#include "StarVMMacro.hh"
#include "Execute.hh"

namespace star
{
	class STAR_VM_API Exit final : public Execute
	{
	public:
		Exit(bool *running);
		~Exit() = default;

		void ExecuteTAC(size_t* registerOut, size_t* registerIn1, size_t* registerIn2, size_t instruction) const override;

	private:
		bool* m_Running;
	};
}