// SaveFile.cpp: implementation of the CSaveFile class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SaveGameEditor.h"
#include "SaveFile.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSaveFile::CSaveFile() : m_SVGMSection(0), m_WKNFSection(0), m_DRLSSection(0)
{

}

CSaveFile::~CSaveFile()
{
	if (m_SVGMSection)
	{
		delete m_SVGMSection;
	}

	if (m_WKNFSection)
	{
		delete m_WKNFSection;
	}

	if (m_DRLSSection)
	{
		delete m_DRLSSection;
	}

	int i = 0;

	while (i < m_RESSections.GetSize())
	{
		delete m_RESSections.GetAt(i++);
	}

	m_RESSections.RemoveAll();

	i = 0;

	while (i < m_LPTBSections.GetSize())
	{
		delete m_LPTBSections.GetAt(i++);
	}

	m_LPTBSections.RemoveAll();
}

BOOL CSaveFile::read(const char *filename)
{
	TRACE("JDN - Starting read of %s...\n", filename);

	BOOL retStatus = TRUE;
	CFile *infile = NULL;

	try
	{
		infile = new CFile(filename, CFile::modeRead | CFile::typeBinary);
	}
	catch(CFileException *e)
	{
		infile = NULL;
		e->Delete();
	}

	if (infile != NULL)
	{
		m_Filename = CString(filename);

		CArchive ar(infile, CArchive::load);

		while(TRUE)
		{
			char header[5];

			try
			{
				for (int i = 0; i < 4; i++)
				{
					ar >> header[i];
				}
			}
			catch(CArchiveException *e)
			{
				if (e->m_cause == CArchiveException::endOfFile)
				{
					e->Delete();
					break;
				}
				else
				{
					TRACE("CArchiveException caught!");
					e->Delete();
				}
			}

			header[4] = '\0';

			if (strcmp(header, "MGVS") == 0)
			{
				TRACE("Reading SVGM section...\n");

				m_SVGMSection = new CSVGMSection();
				m_SVGMSection->Serialize(ar);
			}
			else if (strcmp(header, "FNKW") == 0)
			{
				TRACE("Reading WKNF section...\n");

				m_WKNFSection = new CWKNFSection();
				m_WKNFSection->Serialize(ar);
			}
			else if (strcmp(header, "SLRD") == 0)
			{
				TRACE("Reading DRLS section...\n");

				m_DRLSSection = new CDRLSSection();
				m_DRLSSection->Serialize(ar);
			}
			else if (strcmp(header, " SER") == 0)
			{
				TRACE("Reading RES section...\n");

				CRESSection *sec = new CRESSection();
				sec->Serialize(ar);

				m_RESSections.Add(sec);
			}
			else if (strcmp(header, "BTPL") == 0)
			{
				TRACE("Reading LPTB section...\n");

				CLPTBSection *sec = new CLPTBSection();
				sec->Serialize(ar);

				m_LPTBSections.Add(sec);
			}
			else
			{
				AfxMessageBox("Unsupported file type!", MB_OK);
				retStatus = FALSE;
				break;
			}
		}

		ar.Close();
		infile->Close();
		delete infile;

		if (retStatus)
		{
			retStatus = PopulateRemainingMembers();
		}
	}
	else
	{
		retStatus = FALSE;
	}

	TRACE("JDN - %s\n", retStatus ? "succeeded" : "failed");

	return retStatus;
}

BOOL CSaveFile::write(const char *filename)
{
	TRACE("JDN - Starting write of %s...\n", filename);

	BOOL retStatus = TRUE;
	CFile *outfile = NULL;

	try
	{
		if (filename == 0)
		{
			outfile = new CFile((LPCTSTR)m_Filename, CFile::typeBinary | CFile::modeWrite);
		}
		else
		{
			outfile = new CFile(filename, CFile::modeCreate | CFile::typeBinary | CFile::modeWrite);
		}
	}
	catch(CFileException *e)
	{
		outfile = NULL;
		e->Delete();
	}

	if (outfile != NULL)
	{
		// First, update the RES sections with the new driver order
		// ...

		for (int which = 0; which < m_RESCount; which++)
		{
			for (int i = 0; i < m_RES[which].GetSize(); i++)
			{
				CRESEntry* entry = m_RES[which].GetAt(i);
				entry->m_Unknown3 = m_Order[i];
				entry->m_Unknown2 = m_Order[i] + 1;
			}
		}

		// Now save the file

		CArchive ar(outfile, CArchive::store);
		m_SVGMSection->Serialize(ar);
		m_WKNFSection->Serialize(ar);
		m_DRLSSection->Serialize(ar);

		int i = 0;

		for (i = 0; i < m_RESSections.GetSize(); i++)
		{
			CRESSection* sec = m_RESSections.GetAt(i);
			sec->Serialize(ar);
		}

		for (i = 0; i < m_LPTBSections.GetSize(); i++)
		{
			CLPTBSection* sec = m_LPTBSections.GetAt(i);
			sec->Serialize(ar);
		}

		ar.Close();
		outfile->Close();
		delete outfile;
	}

	TRACE("JDN - %s\n", retStatus ? "succeeded" : "failed");

	return retStatus;
}

BOOL CSaveFile::PopulateRemainingMembers()
{
	BOOL retStatus = TRUE;
	int i = 0;
	m_RESCount = 0;

	for (i = 0; i < m_RESSections.GetSize(); i++)
	{
		CRESSection* sec = m_RESSections.GetAt(i);

		if (sec->m_Type == SESS_QUALIFY0 || sec->m_Type == SESS_QUALIFY1)
		{
			for (int j = 0; j < sec->m_Entries.GetSize(); j++)
			{
				CRESEntry* entry = sec->m_Entries.GetAt(j);

				if (entry->m_LapTime < 0.0)
				{
					break;
				}

				int count = m_RES[m_RESCount].GetSize();
				int k = 0;

				while((k < count) && (m_RES[m_RESCount].GetAt(k)->m_LapTime <= entry->m_LapTime))
				{
					k++;
				}

				m_RES[m_RESCount].InsertAt(k, entry);
			}

			m_RESCount++;
		}
	}

	if (m_RESCount == 0)
	{
		AfxMessageBox("No qualifying results found!  Be sure to actually run a qualifying session before saving the game!", MB_OK);
		retStatus = FALSE;
	}

	if (retStatus)
	{
		for (i = 0; i < m_RESCount; i++)
		{
			if (m_RES[i].GetSize() <= 0)
			{
				AfxMessageBox("No qualifying results found!  Be sure to actually run a qualifying session before saving the game!", MB_OK);
				retStatus = FALSE;
				break;
			}
		}
	}

	if (!retStatus)
	{
		return retStatus;
	}

#ifdef _DEBUG
	TRACE("--- Times ---\n");

	for (int k0 = 0; k0 < 4; k0++)
	{
		for (int j = 0; j < m_RES[k0].GetSize(); j++)
		{
			CRESEntry* entry = m_RES[k0].GetAt(j);

			TRACE("%d - %d - %f (%d)\n", k0, j, entry->m_LapTime, entry->m_Unknown3);
		}
	}
#endif

	// Now, fill up the drivers list

	for (i = 0; i < m_DRLSSection->m_DRNTSections.GetSize(); i++)
	{
		CDRNTSection* entry = m_DRLSSection->m_DRNTSections.GetAt(i);
		m_Drivers[entry->m_Index0] = entry;
	}

#ifdef _DEBUG
	TRACE("--- Drivers ---\n");

	for (int k1 = 0; k1 < m_DRLSSection->m_DRNTSections.GetSize(); k1++)
	{
		CDRNTSection* entry = m_Drivers[k1];
		TRACE("%d - %d - %s %s (%d)\n", k1, entry->m_Index0, entry->m_FirstName, entry->m_LastName, entry->m_CarNumber);
	}
#endif

	// Now, fill up the order

	for (i = 0; i < m_RES[0].GetSize(); i++)
	{
		m_Order[i] = m_RES[0].GetAt(i)->m_Unknown3;
	}

#ifdef _DEBUG
	TRACE("--- Starting Order ---\n");

	for (int k2 = 0; k2 < m_RES[0].GetSize(); k2++)
	{
		TRACE("%d - %d - %s %s (%d)\n", k2, m_Order[k2], m_Drivers[m_Order[k2]]->m_FirstName, m_Drivers[m_Order[k2]]->m_LastName, m_Drivers[m_Order[k2]]->m_CarNumber);
	}
#endif

	return retStatus;
}

int CSaveFile::GetNumDrivers()
{
	return m_RES[0].GetSize();
}
