// LPROSection.cpp: implementation of the CLPROSection class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SaveGameEditor.h"
#include "LPROSection.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_SERIAL(CLPROSection, CObject, 1)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLPROSection::CLPROSection() : m_DataSize(-1), m_Buffer(0)
{
	m_Header[0] = 'O';
	m_Header[1] = 'R';
	m_Header[2] = 'P';
	m_Header[3] = 'L';
}

CLPROSection::~CLPROSection()
{
	if (m_Buffer)
	{
		free(m_Buffer);
	}
}

void CLPROSection::Serialize(CArchive& archive)
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

		archive.Write((void *)m_Buffer, m_DataSize);
	}
	else
	{
		LONG val0;

		archive >> val0;
		ASSERT(val0 == 0);

		archive >> m_DataSize;

		m_Buffer = (char *)malloc(m_DataSize);
		archive.Read((void *)m_Buffer, m_DataSize);
	}
}
