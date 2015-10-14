// MidtermProjectView.h : CMidtermProjectView Ŭ������ �������̽�
//


#pragma once


class CMidtermProjectView : public CScrollView
{
protected: // serialization������ ��������ϴ�.
	CMidtermProjectView();
	DECLARE_DYNCREATE(CMidtermProjectView)

// Ư���Դϴ�.
public:
	CMidtermProjectDoc* GetDocument() const;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

protected:
	virtual void OnInitialUpdate(); // ���� �� ó�� ȣ��Ǿ����ϴ�.
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �����Դϴ�.
public:
	virtual ~CMidtermProjectView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
public:
	// �̹��� Ȯ�� ����
	int m_nZoom;

protected:
	void SetScrollSizeToFit(void);
	void ShowImageInfo(CPoint point);

public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);

	afx_msg void OnViewZoom1();
	afx_msg void OnViewZoom2();
	afx_msg void OnViewZoom3();
	afx_msg void OnViewZoom4();

	afx_msg void OnUpdateViewZoom1(CCmdUI *pCmdUI);
	afx_msg void OnUpdateViewZoom2(CCmdUI *pCmdUI);
	afx_msg void OnUpdateViewZoom3(CCmdUI *pCmdUI);
	afx_msg void OnUpdateViewZoom4(CCmdUI *pCmdUI);
    afx_msg void OnDibinverse();
    afx_msg void OnDibcontrast();
    afx_msg void OnGammacorrection();
    afx_msg void OnHistogram();
    afx_msg void OnHistoEqualize();
	afx_msg void OnKMean();
	afx_msg void K_Mean_Clustering(BYTE** image, int* ME, int K, int T, int w, int h); // , float* saveMean
	afx_msg void K_Mean_Clustering(BYTE** image, int* ME, int K, int T, int w, int h, float* saveMean); // 
	afx_msg void OnLBG();
	afx_msg void LBG_Clustering(BYTE** image, int* ME, int K, int T, int w, int h, float* saveMean);
	afx_msg int CalcMidHist(BYTE** image, int w, int h);
};

#ifndef _DEBUG  // MidtermProjectView.cpp�� ����� ����
inline CMidtermProjectDoc* CMidtermProjectView::GetDocument() const
   { return reinterpret_cast<CMidtermProjectDoc*>(m_pDocument); }
#endif

