// SVGMSection.h: interface for the CSVGMSection class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SVGMSECTION_H__9EE01B52_EAEB_4758_95F8_2D71FAEF2D78__INCLUDED_)
#define AFX_SVGMSECTION_H__9EE01B52_EAEB_4758_95F8_2D71FAEF2D78__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSVGMSection : public CObject  
{
public:
	DECLARE_SERIAL(CSVGMSection)

	CSVGMSection();
	virtual ~CSVGMSection();

	void Serialize(CArchive& archive);

private:
	char m_Header[4];
	LONG m_DataSize;
	char *m_Buffer;
};

#endif // !defined(AFX_SVGMSECTION_H__9EE01B52_EAEB_4758_95F8_2D71FAEF2D78__INCLUDED_)
