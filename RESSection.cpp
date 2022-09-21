// RESSection.cpp: implementation of the CRESSection class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SaveGameEditor.h"
#include "RESSection.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_SERIAL(CRESSection, CObject, 1)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRESSection::CRESSection() : m_DataSize(-1), m_NumEntries(0), m_Unknown(0), m_Type(0), m_Buffer(0)
{
	m_Header[0] = ' ';
	m_Header[1] = 'S';
	m_Header[2] = 'E';
	m_Header[3] = 'R';
}

CRESSection::~CRESSection()
{
	int i = 0;

	while (i < m_Entries.GetSize())
	{
		delete m_Entries.GetAt(i++);
	}

	m_Entries.RemoveAll();

	if (m_Buffer)
	{
		free(m_Buffer);
	}
}

void CRESSection::Serialize(CArchive& archive)
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

		for (i = 0; i < m_NumEntries; i++)
		{
			CRESEntry* entry = m_Entries.GetAt(i);
			entry->Serialize(archive);
		}

		archive << m_Type;

		archive.Write((void *)m_Buffer, 26);
	}
	else
	{
		LONG val0;

		archive >> val0;
		ASSERT(val0 == 0);

		archive >> m_DataSize;

		m_NumEntries = (m_DataSize / 10) - 3;

		for (int i = 0; i < m_NumEntries; i++)
		{
			CRESEntry *entry = new CRESEntry();
			entry->Serialize(archive);

			m_Entries.Add(entry);
		}

		archive >> m_Type;

		TRACE("\tRES Section Type = %d\n", m_Type);

		// snarf the remaining 26 bytes

		m_Buffer = (char *)malloc(26);
		archive.Read((void *)m_Buffer, 26);
	}
}
