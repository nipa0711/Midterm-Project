// MidtermProjectDoc.h : CMidtermProjectDoc Ŭ������ �������̽�
//


#pragma once

#include "dib.h"

class CMidtermProjectDoc : public CDocument
{
protected: // serialization������ ��������ϴ�.
	CMidtermProjectDoc();
	DECLARE_DYNCREATE(CMidtermProjectDoc)

// Ư���Դϴ�.
public:

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// �����Դϴ�.
public:
	virtual ~CMidtermProjectDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()

public:
	// �̹��� ��ü
	CDib m_Dib;

	// ���� �ҷ����� & �����ϱ�
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);

public:
	afx_msg void OnWindowDuplicate();
	afx_msg void OnEditCopy();
};
