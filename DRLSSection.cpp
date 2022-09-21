// DRLSSection.cpp: implementation of the CDRLSSection class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SaveGameEditor.h"
#include "DRLSSection.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_SERIAL(CDRLSSection, CObject, 1)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDRLSSection::CDRLSSection() : m_DataSize(-1)
{
	m_Header[0] = 'S';
	m_Header[1] = 'L';
	m_Header[2] = 'R';
	m_Header[3] = 'D';
}

CDRLSSection::~CDRLSSection()
{
	int i = 0;

	while (i < m_DRNTSections.GetSize())
	{
		delete m_DRNTSections.GetAt(i++);
	}

	m_DRNTSections.RemoveAll();
}

void CDRLSSection::Serialize(CArchive& archive)
{
	// call base class function first

	CObject::Serialize(archive);

	// now do the stuff for our specific class

	if (archive.IsStoring())
	{
		int i = 0;

		for (i = 0; i < 4; i++)
		{
			archive << m_Header[i];
		}

		LONG val0 = 0L;

		archive << val0;
		archive << m_DataSize;

		for (i = 0; i < m_DRNTSections.GetSize(); i++)
		{
			CDRNTSection* sec = m_DRNTSections.GetAt(i);
			sec->Serialize(archive);
		}
	}
	else
	{
		LONG val0;

		archive >> val0;

		ASSERT(val0 == 0);

		archive >> m_DataSize;

		TRACE("Data size = %d\n", m_DataSize);

		LONG bytesLeft = m_DataSize;

		while (bytesLeft > 0)
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

			ASSERT(!strcmp("TNRD", header));

			CDRNTSection *sec = new CDRNTSection();
			sec->Serialize(archive);
			m_DRNTSections.Add(sec);

			bytesLeft -= (sec->GetRealDataSize() + 12);
		}

		ASSERT(bytesLeft == 0);
	}
}
