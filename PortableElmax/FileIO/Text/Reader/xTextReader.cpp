#include "xTextReader.h"

#include "UTF8Reader.h"
#include "UnicodeReader.h"
#include "BEUnicodeReader.h"
#include "AsciiReader.h"
#include "../../Common/Enumeration.h"

using namespace Elmax;

xTextReader::xTextReader(void)
	:	pReader(NULL)
{
}

xTextReader::~xTextReader(void)
{
	Close();
}

bool xTextReader::Open(const std::wstring& file)
{
	Close();
	if(UTF8Reader::IsValid(file))
	{
		pReader = new UTF8Reader();
		return pReader->Open(file);
	}
	if(UnicodeReader::IsValid(file))
	{
		pReader = new UnicodeReader();
		return pReader->Open(file);
	}
	if(BEUnicodeReader::IsValid(file))
	{
		pReader = new BEUnicodeReader();
		return pReader->Open(file);
	}
	if(AsciiReader::IsValid(file))
	{
		pReader = new AsciiReader();
		return pReader->Open(file);
	}

	return false;
}

bool xTextReader::Open(const std::wstring& file, FILE_TYPE ftype)
{
	Close();
	if(UTF8Reader::IsValid(file))
	{
		pReader = new UTF8Reader();
		return pReader->Open(file);
	}
	if(UnicodeReader::IsValid(file))
	{
		pReader = new UnicodeReader();
		return pReader->Open(file);
	}
	if(BEUnicodeReader::IsValid(file))
	{
		pReader = new BEUnicodeReader();
		return pReader->Open(file);
	}
	else
	{
		switch(ftype)
		{
		case FT_UTF8:
			pReader = new UTF8Reader();
			return pReader->Open(file);
			break;
		case FT_UNICODE:
			pReader = new UnicodeReader();
			return pReader->Open(file);
			break;
		case FT_BEUNICODE:
			pReader = new BEUnicodeReader();
			return pReader->Open(file);
			break;
		case FT_ASCII:
			pReader = new AsciiReader();
			return pReader->Open(file);
			break;
		default:
			pReader = new AsciiReader();
			return pReader->Open(file);
			break;
		}
	}

	return false;
}

void xTextReader::Close()
{
	if(pReader != NULL)
	{
		pReader->Close();
		delete pReader;
		pReader = NULL;
	}

	return;
}

bool xTextReader::IsEOF()
{
	if(pReader!=NULL)
	{
		return pReader->IsEOF();
	}

	return true;
}

bool xTextReader::ReadAll( std::wstring& text )
{
	if(pReader!=NULL)
	{
		return pReader->ReadAll(text);
	}

	return false;
}

int xTextReader::GetLastError(std::wstring& msg)
{
	if(pReader!=NULL)
	{
		return pReader->GetLastError(msg);
	}

	msg = GetErrorMsg(ELMAX_NULL_POINTER);
	return ELMAX_NULL_POINTER;
}


void xTextReader::ClearLastError()
{
	if(pReader!=NULL)
	{
		pReader->ClearLastError();
	}
}

bool xTextReader::EnableException(bool enable)
{
	bool prev = enableException;

	enableException = enable;

	return prev;
}
