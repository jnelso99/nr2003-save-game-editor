// RESEntry.cpp: implementation of the CRESEntry class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SaveGameEditor.h"
#include "RESEntry.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_SERIAL(CRESEntry, CObject, 1)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRESEntry::CRESEntry()
{

}

CRESEntry::~CRESEntry()
{

}

void CRESEntry::Serialize(CArchive& archive)
{
	// call base class function first

	CObject::Serialize(archive);

	// now do the stuff for our specific class

	if (archive.IsStoring())
	{
		archive << m_LapTime;
		archive << m_Unknown0;
		archive << m_Unknown1;
		archive << m_Unknown2;
		archive << m_Unknown3;
	}
	else
	{
		archive >> m_LapTime;  // Lap time (sec)
		archive >> m_Unknown0; // Laps run?
		archive >> m_Unknown1;
		archive >> m_Unknown2; // 0-based index value in DRNT object
		archive >> m_Unknown3; // 1-based index value in DRNT object

		TRACE("\t%f - %d - %d - %d - %d\n", m_LapTime, m_Unknown0, m_Unknown1, m_Unknown2, m_Unknown3);
	}
}
