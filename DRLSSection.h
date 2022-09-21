// DRLSSection.h: interface for the CDRLSSection class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DRLSSECTION_H__01269906_0C99_432B_B15E_1645A7AE8A46__INCLUDED_)
#define AFX_DRLSSECTION_H__01269906_0C99_432B_B15E_1645A7AE8A46__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxtempl.h>
#include "DRNTSection.h"

class CDRLSSection : public CObject  
{
public:
	DECLARE_SERIAL(CDRLSSection)

	CDRLSSection();
	virtual ~CDRLSSection();

	void Serialize(CArchive& archive);

public:
	char m_Header[4];
	LONG m_DataSize;
	CTypedPtrArray < CObArray, CDRNTSection* > m_DRNTSections;
};

#endif // !defined(AFX_DRLSSECTION_H__01269906_0C99_432B_B15E_1645A7AE8A46__INCLUDED_)
