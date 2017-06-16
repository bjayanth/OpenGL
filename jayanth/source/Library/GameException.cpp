#include "pch.h"

using namespace std;

namespace Library
{
	GameException::GameException(const char* const& message, HRESULT hr) :
		exception(message), mHR(hr)
	{
	}

	HRESULT GameException::HR() const
	{
		return mHR;
	}

	wstring GameException::whatw() const
	{
		string whatString(what());
		wstring whatw;
		whatw.assign(whatString.begin(), whatString.end());

		return whatw;
	}
}