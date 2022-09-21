// SVGMSection.cpp: implementation of the CSVGMSection class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SaveGameEditor.h"
#include "SVGMSection.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_SERIAL(CSVGMSection, CObject, 1)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSVGMSection::CSVGMSection() : m_DataSize(-1), m_Buffer(0)
{
	m_Header[0] = 'M';
	m_Header[1] = 'G';
	m_Header[2] = 'V';
	m_Header[3] = 'S';
}

CSVGMSection::~CSVGMSection()
{
	if (m_Buffer)
	{
		free(m_Buffer);
	}
}

void CSVGMSection::Serialize(CArchive& archive)
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
