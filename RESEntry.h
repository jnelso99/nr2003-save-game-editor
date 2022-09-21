// RESEntry.h: interface for the CRESEntry class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RESENTRY_H__88188383_6434_45CD_8A76_388E7C4DC66A__INCLUDED_)
#define AFX_RESENTRY_H__88188383_6434_45CD_8A76_388E7C4DC66A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CRESEntry : public CObject  
{
public:
	DECLARE_SERIAL(CRESEntry)

	CRESEntry();
	virtual ~CRESEntry();

	void Serialize(CArchive& archive);

public:
	float m_LapTime;
	short m_Unknown0; // Laps run?
	short m_Unknown1;
	char m_Unknown2; // 0-based index value in DRNT object
	char m_Unknown3; // 1-based index value in DRNT object
};

#endif // !defined(AFX_RESENTRY_H__88188383_6434_45CD_8A76_388E7C4DC66A__INCLUDED_)
