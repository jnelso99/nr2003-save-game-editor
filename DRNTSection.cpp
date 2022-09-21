// DRNTSection.cpp: implementation of the CDRNTSection class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SaveGameEditor.h"
#include "DRNTSection.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_SERIAL(CDRNTSection, CObject, 1)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDRNTSection::CDRNTSection() : m_DataSize(-1), m_RealDataSize(-1)
{
	m_Header[0] = 'T';
	m_Header[1] = 'N';
	m_Header[2] = 'R';
	m_Header[3] = 'D';
}

CDRNTSection::~CDRNTSection()
{
}

void CDRNTSection::Serialize(CArchive& archive)
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
		archive.Write(m_FirstName, 16);
		archive.Write(m_LastName, 16);

		for (i = 0; i < 20; i++)
		{
			archive << val0;
		}

		archive.Write(m_CarFile, 32);
		archive << m_CarMake;
		archive << m_Unknown1;
		archive << m_Unknown2;
		archive << m_CarNumber;
		archive << m_Unknown3;
		archive << m_Index1;
		archive << m_Index0;
		archive.Write(m_Unknown4, 4);
	}
	else
	{
		LONG val0;

		archive >> val0;

		ASSERT(val0 == 0);

		archive >> m_DataSize;
		archive.Read(m_FirstName, 16);
		archive.Read(m_LastName, 16);

		m_RealDataSize = m_DataSize;

		if (m_DataSize % 4 != 0)
		{
			m_RealDataSize = ((m_DataSize + 4) / 4) * 4;
		}

		for (int i = 0; i < 20; i++)
		{
			archive >> val0;
			ASSERT(val0 == 0);
		}

		archive.Read(m_CarFile, 32);

		archive >> m_CarMake;
		archive >> m_Unknown1;
		archive >> m_Unknown2;
		archive >> m_CarNumber;
		archive >> m_Unknown3;
		archive >> m_Index1;
		archive >> m_Index0;
		archive.Read(m_Unknown4, 4);

		//TRACE("\tRead car %d for %s %s (%s)\n", m_CarNumber, m_FirstName, m_LastName, m_CarFile);
		//TRACE("\tUnknowns: { %d, %d, %d, [ %d %d %d ] }\n", m_Unknown1, m_Unknown2, m_Unknown3, m_Unknown4[0], m_Unknown4[1], m_Unknown4[2]);
	}
}

LONG CDRNTSection::GetRealDataSize()
{
	return m_RealDataSize;
}
