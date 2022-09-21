// SaveFile.h: interface for the CSaveFile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SAVEFILE_H__DD265216_7F89_451F_B5F6_B11E7FAC1710__INCLUDED_)
#define AFX_SAVEFILE_H__DD265216_7F89_451F_B5F6_B11E7FAC1710__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxtempl.h>
#include "SVGMSection.h"
#include "WKNFSection.h"
#include "DRLSSection.h"
#include "DRNTSection.h"
#include "RESSection.h"
#include "RESEntry.h"
#include "LPTBSection.h"

class CSaveFile  
{
public:
	CSaveFile();
	virtual ~CSaveFile();
	BOOL read(const char *filename);
	BOOL write(const char *filename);
	int GetNumDrivers();

private:
	BOOL PopulateRemainingMembers();

// Attributes
public:
	CString m_Filename;
	CSVGMSection *m_SVGMSection;
	CWKNFSection *m_WKNFSection;
	CDRLSSection *m_DRLSSection;
	CTypedPtrArray < CObArray, CRESSection* > m_RESSections;
	CTypedPtrArray < CObArray, CLPTBSection* > m_LPTBSections;

	CTypedPtrArray < CObArray, CRESEntry* > m_RES[4]; // In qualifying order (m_Drivers[CRESEntry::m_Unknown3] to get driver info)

	CDRNTSection *m_Drivers[44]; // In order of 0-based index (CDRNTSection::m_Index0)
	int m_Order[43]; // of 0-based index of driver

	int m_RESCount;
};

#endif // !defined(AFX_SAVEFILE_H__DD265216_7F89_451F_B5F6_B11E7FAC1710__INCLUDED_)
