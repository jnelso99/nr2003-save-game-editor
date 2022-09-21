// RESSection.h: interface for the CRESSection class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RESSECTION_H__283628BD_7777_46DB_A147_A8A04DB52568__INCLUDED_)
#define AFX_RESSECTION_H__283628BD_7777_46DB_A147_A8A04DB52568__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxtempl.h>
#include "RESEntry.h"

#define SESS_PRACTICE 0
#define SESS_QUALIFY0 1
#define SESS_WARMUP   2
#define SESS_QUALIFY1 8

class CRESSection : public CObject  
{
public:
	DECLARE_SERIAL(CRESSection)

	CRESSection();
	virtual ~CRESSection();

	void Serialize(CArchive& archive);

public:
	char m_Header[4];
	LONG m_DataSize;
	LONG m_NumEntries;
	CTypedPtrArray < CObArray, CRESEntry* > m_Entries;
	LONG m_Unknown;
	LONG m_Type;
	char *m_Buffer;
};

#endif // !defined(AFX_RESSECTION_H__283628BD_7777_46DB_A147_A8A04DB52568__INCLUDED_)
