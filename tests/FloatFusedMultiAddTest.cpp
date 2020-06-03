#include "FloatFusedMultiAddTest.h"
#include "MemStream.h"

CFloatFusedMultiAddTest::CFloatFusedMultiAddTest()
{
}

CFloatFusedMultiAddTest::~CFloatFusedMultiAddTest()
{
}

void CFloatFusedMultiAddTest::Compile(Jitter::CJitter& jitter)
{
	Framework::CMemStream codeStream;
	jitter.SetStream(&codeStream);

	jitter.Begin();
	{
		jitter.FP_PushSingle(offsetof(CONTEXT, number3));
		jitter.FP_PushSingle(offsetof(CONTEXT, number2));
		jitter.FP_PushSingle(offsetof(CONTEXT, number1));
		jitter.FP_MulAdd();
		jitter.FP_PullSingle(offsetof(CONTEXT, res1));

		jitter.FP_PushSingle(offsetof(CONTEXT, number4));
		jitter.FP_PushSingle(offsetof(CONTEXT, number2));
		jitter.FP_PushSingle(offsetof(CONTEXT, number2));
		jitter.FP_MulAdd();
		jitter.FP_PullSingle(offsetof(CONTEXT, res2));

		jitter.FP_PushSingle(offsetof(CONTEXT, number3));
		jitter.FP_PushSingle(offsetof(CONTEXT, number4));
		jitter.FP_PushSingle(offsetof(CONTEXT, number2));
		jitter.FP_MulAdd();
		jitter.FP_PullSingle(offsetof(CONTEXT, res3));

		jitter.FP_PushSingle(offsetof(CONTEXT, number3));
		jitter.FP_PushSingle(offsetof(CONTEXT, number2));
		jitter.FP_PushSingle(offsetof(CONTEXT, number1));
		jitter.FP_MulSub();
		jitter.FP_PullSingle(offsetof(CONTEXT, res4));

		jitter.FP_PushSingle(offsetof(CONTEXT, number4));
		jitter.FP_PushSingle(offsetof(CONTEXT, number2));
		jitter.FP_PushSingle(offsetof(CONTEXT, number2));
		jitter.FP_MulSub();
		jitter.FP_PullSingle(offsetof(CONTEXT, res5));

		jitter.FP_PushSingle(offsetof(CONTEXT, number3));
		jitter.FP_PushSingle(offsetof(CONTEXT, number4));
		jitter.FP_PushSingle(offsetof(CONTEXT, number2));
		jitter.FP_MulSub();
		jitter.FP_PullSingle(offsetof(CONTEXT, res6));
	}
	jitter.End();

	m_function = CMemoryFunction(codeStream.GetBuffer(), codeStream.GetSize());
}

void CFloatFusedMultiAddTest::Run()
{
	memset(&m_context, 0, sizeof(CONTEXT));
	m_context.number1 = 1.0f;
	m_context.number2 = 2.0f;
	m_context.number3 = -4.0f;
	m_context.number4 = 16.0f;
	m_function(&m_context);
	TEST_VERIFY(m_context.res1 == -2.0f);
	TEST_VERIFY(m_context.res2 == 20.0f);
	TEST_VERIFY(m_context.res3 == 28.0f);

	TEST_VERIFY(m_context.res4 == 6.0f);
	TEST_VERIFY(m_context.res5 == -12.0f);
	TEST_VERIFY(m_context.res6 == 36.0f);
}
