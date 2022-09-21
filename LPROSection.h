// LPROSection.h: interface for the CLPROSection class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LPROSECTION_H__DD2B8FAD_5232_4F90_89F2_31B59CA4F268__INCLUDED_)
#define AFX_LPROSECTION_H__DD2B8FAD_5232_4F90_89F2_31B59CA4F268__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CLPROSection : public CObject  
{
public:
	DECLARE_SERIAL(CLPROSection)

	CLPROSection();
	virtual ~CLPROSection();

	void Serialize(CArchive& archive);

private:
	char m_Header[4];
	LONG m_DataSize;
	char *m_Buffer;
};

#endif // !defined(AFX_LPROSECTION_H__DD2B8FAD_5232_4F90_89F2_31B59CA4F268__INCLUDED_)
