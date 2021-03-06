#pragma once

#include "Test.h"
#include "MemoryFunction.h"

class CLogic64Test : public CTest
{
public:
	void				Run() override;
	void				Compile(Jitter::CJitter&) override;

private:
	struct CONTEXT
	{
		uint64			op1;
		uint64			op2;

		uint64			resultAnd;
	};

	CONTEXT				m_context;
	CMemoryFunction		m_function;
};
