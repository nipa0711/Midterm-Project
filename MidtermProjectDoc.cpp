// MidtermProjectDoc.cpp : CMidtermProjectDoc Ŭ������ ����
//

#include "stdafx.h"
#include "MidtermProject.h"

#include "MidtermProjectDoc.h"

#include "FileNewDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMidtermProjectDoc

IMPLEMENT_DYNCREATE(CMidtermProjectDoc, CDocument)

BEGIN_MESSAGE_MAP(CMidtermProjectDoc, CDocument)
	ON_COMMAND(ID_WINDOW_DUPLICATE, &CMidtermProjectDoc::OnWindowDuplicate)
	ON_COMMAND(ID_EDIT_COPY, &CMidtermProjectDoc::OnEditCopy)
END_MESSAGE_MAP()


// CMidtermProjectDoc ����/�Ҹ�

CMidtermProjectDoc::CMidtermProjectDoc()
{
	// TODO: ���⿡ ��ȸ�� ���� �ڵ带 �߰��մϴ�.

}

CMidtermProjectDoc::~CMidtermProjectDoc()
{
}

BOOL CMidtermProjectDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	BOOL bSuccess = TRUE;

	if( theApp.m_pNewDib == NULL )
	{
		CFileNewDlg dlg;
		if( dlg.DoModal() == IDOK )
		{
			if( dlg.m_nType == 0 ) // �׷��̽����� �̹���
				bSuccess = m_Dib.CreateGrayImage(dlg.m_nWidth, dlg.m_nHeight);
			else // Ʈ��Į�� �̹���
				bSuccess = m_Dib.CreateRGBImage(dlg.m_nWidth, dlg.m_nHeight);
		}
		else
		{
			bSuccess = FALSE;
		}
	}
	else
	{
		m_Dib.Copy(theApp.m_pNewDib);
		theApp.m_pNewDib = NULL;
	}

	return bSuccess;
}

// CMidtermProjectDoc serialization

void CMidtermProjectDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	}
	else
	{
		// TODO: ���⿡ �ε� �ڵ带 �߰��մϴ�.
	}
}


// CMidtermProjectDoc ����

#ifdef _DEBUG
void CMidtermProjectDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMidtermProjectDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMidtermProjectDoc ���


BOOL CMidtermProjectDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	return  m_Dib.Load(lpszPathName);
}

BOOL CMidtermProjectDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	return  m_Dib.Save(lpszPathName);
}

void CMidtermProjectDoc::OnEditCopy()
{
	if( m_Dib.IsValid() )
		m_Dib.CopyToClipboard();
}

void CMidtermProjectDoc::OnWindowDuplicate()
{
	AfxNewImage(m_Dib);
}

