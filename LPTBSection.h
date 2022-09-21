// LPTBSection.h: interface for the CLPTBSection class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LPTBSECTION_H__2BB7B9C7_422A_4FA8_9E32_376898E75824__INCLUDED_)
#define AFX_LPTBSECTION_H__2BB7B9C7_422A_4FA8_9E32_376898E75824__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "LPROSection.h"

class CLPTBSection : public CObject  
{
public:
	DECLARE_SERIAL(CLPTBSection)

	CLPTBSection();
	virtual ~CLPTBSection();

	void Serialize(CArchive& archive);

private:
	char m_Header[4];
	LONG m_DataSize;
	CLPROSection *m_LPROSection;
};

#endif // !defined(AFX_LPTBSECTION_H__2BB7B9C7_422A_4FA8_9E32_376898E75824__INCLUDED_)
