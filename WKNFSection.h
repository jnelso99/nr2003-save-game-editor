// WKNFSection.h: interface for the CWKNFSection class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WKNFSECTION_H__418FF97F_B956_4A2B_88C1_EDD570CD63B1__INCLUDED_)
#define AFX_WKNFSECTION_H__418FF97F_B956_4A2B_88C1_EDD570CD63B1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CWKNFSection : public CObject  
{
public:
	DECLARE_SERIAL(CWKNFSection)

	CWKNFSection();
	virtual ~CWKNFSection();

	void Serialize(CArchive& archive);

private:
	char m_Header[4];
	LONG m_DataSize;
	char *m_Buffer;
};

#endif // !defined(AFX_WKNFSECTION_H__418FF97F_B956_4A2B_88C1_EDD570CD63B1__INCLUDED_)
