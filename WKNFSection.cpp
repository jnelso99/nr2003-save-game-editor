// WKNFSection.cpp: implementation of the CWKNFSection class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SaveGameEditor.h"
#include "WKNFSection.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_SERIAL(CWKNFSection, CObject, 1)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWKNFSection::CWKNFSection() : m_DataSize(-1), m_Buffer(0)
{
	m_Header[0] = 'F';
	m_Header[1] = 'N';
	m_Header[2] = 'K';
	m_Header[3] = 'W';
}

CWKNFSection::~CWKNFSection()
{
	if (m_Buffer)
	{
		free(m_Buffer);
	}
}

void CWKNFSection::Serialize(CArchive& archive)
{
	// call base class function first

	CObject::Serialize(archive);

	// now do the stuff for our specific class

	if (archive.IsStoring())
	{
		for (int i = 0; i < 4; i++)
		{
			archive << m_Header[i];
		}

		LONG val0 = 0L;

		archive << val0;
		archive << m_DataSize;

		LONG realDataSize = m_DataSize;

		if (m_DataSize % 4 != 0)
		{
			realDataSize = ((m_DataSize + 4) / 4) * 4;
		}

		archive.Write((void *)m_Buffer, realDataSize);
	}
	else
	{
		LONG val0;

		archive >> val0;

		ASSERT(val0 == 0);

		archive >> m_DataSize;

		LONG realDataSize = m_DataSize;

		if (m_DataSize % 4 != 0)
		{
			realDataSize = ((m_DataSize + 4) / 4) * 4;
		}

		m_Buffer = (char *)malloc(realDataSize);
		archive.Read((void *)m_Buffer, realDataSize);
	}
}
