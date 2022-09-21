// DRNTSection.h: interface for the CDRNTSection class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DRNTSECTION_H__49D334DA_1E65_49CD_9DC0_673E8E822F19__INCLUDED_)
#define AFX_DRNTSECTION_H__49D334DA_1E65_49CD_9DC0_673E8E822F19__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDRNTSection : public CObject  
{
public:
	DECLARE_SERIAL(CDRNTSection)

	CDRNTSection();
	virtual ~CDRNTSection();

	void Serialize(CArchive& archive);
	LONG GetRealDataSize();

public:
	char m_Header[4];
	LONG m_DataSize;
	LONG m_RealDataSize;
	char m_FirstName[16];
	char m_LastName[16];
	char m_CarFile[32];
	LONG m_CarMake;		// 0 = Chevy, 1 = Dodge, 2 = Ford, 3 = Pontiac
	LONG m_Unknown1;	// 0 = Pace car, 1 = Not pace car
	LONG m_Unknown2;	// Always 0?
	LONG m_CarNumber;
	LONG m_Unknown3;	// 0 for pace car, 150 for player car, 250 for computer car
	LONG m_Index1;		// 1-based index?
	LONG m_Index0;		// 0-based index?
	char m_Unknown4[4];	// [0] - 0 = player car, 1 = not player car?
						// [1] - 0 = pace car, 1 = not pace car?
						// [2] - 3 for player car, 0 for all other cars?
};

#endif // !defined(AFX_DRNTSECTION_H__49D334DA_1E65_49CD_9DC0_673E8E822F19__INCLUDED_)
