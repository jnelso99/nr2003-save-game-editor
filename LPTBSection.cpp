// LPTBSection.cpp: implementation of the CLPTBSection class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SaveGameEditor.h"
#include "LPTBSection.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_SERIAL(CLPTBSection, CObject, 1)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLPTBSection::CLPTBSection() : m_DataSize(-1), m_LPROSection(0)
{
	m_Header[0] = 'B';
	m_Header[1] = 'T';
	m_Header[2] = 'P';
	m_Header[3] = 'L';
}

CLPTBSection::~CLPTBSection()
{
	if (m_LPROSection)
	{
		delete m_LPROSection;
	}
}

void CLPTBSection::Serialize(CArchive& archive)
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

		if (m_DataSize > 0)
		{
			ASSERT(m_LPROSection);

			m_LPROSection->Serialize(archive);
		}
	}
	else
	{
		LONG val0;

		archive >> val0;

		ASSERT(val0 == 0);

		archive >> m_DataSize;

		if (m_DataSize > 0)
		{
			char header[5];

			try
			{
				for (int i = 0; i < 4; i++)
				{
					archive >> header[i];
				}
			}
			catch(CArchiveException *e)
			{
				TRACE("CArchiveException caught!");
				e->Delete();
			}

			header[4] = '\0';

			ASSERT(!strcmp("ORPL", header));

			m_LPROSection = new CLPROSection();
			m_LPROSection->Serialize(archive);
		}
	}
}
