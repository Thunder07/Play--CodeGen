#ifndef _MULTTEST_H_
#define _MULTTEST_H_

#include "Test.h"
#include "MemoryFunction.h"

class CMultTest : public CTest
{
public:
						CMultTest(bool);
	virtual				~CMultTest();
			
	void				Run();
	void				Compile(Jitter::CJitter&);

private:
	struct CONTEXT
	{
		uint32			cstResultLo;
		uint32			cstResultHi;

		uint32			relArg0;
		uint32			relArg1;

		uint32			relResultLo;
		uint32			relResultHi;

		uint32			multHalfLoResult;
		uint32			multHalfHiResult;
	};

	bool				m_isSigned;
	CONTEXT				m_context;
	CMemoryFunction*	m_function;
};

#endif
