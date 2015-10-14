// MidtermProjectView.cpp : CMidtermProjectView Ŭ������ ����
//

#include "stdafx.h"
#include "MidtermProject.h"

#include "MainFrm.h"
#include "MidtermProjectDoc.h"
#include "MidtermProjectView.h"
#include "RGBBYTE.h"
#include "HistogramDlg.h" 
#include <math.h>
#include <iostream>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMidtermProjectView

IMPLEMENT_DYNCREATE(CMidtermProjectView, CScrollView)

BEGIN_MESSAGE_MAP(CMidtermProjectView, CScrollView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CScrollView::OnFilePrintPreview)
	ON_COMMAND(ID_VIEW_ZOOM1, &CMidtermProjectView::OnViewZoom1)
	ON_COMMAND(ID_VIEW_ZOOM2, &CMidtermProjectView::OnViewZoom2)
	ON_COMMAND(ID_VIEW_ZOOM3, &CMidtermProjectView::OnViewZoom3)
	ON_COMMAND(ID_VIEW_ZOOM4, &CMidtermProjectView::OnViewZoom4)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ZOOM1, &CMidtermProjectView::OnUpdateViewZoom1)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ZOOM2, &CMidtermProjectView::OnUpdateViewZoom2)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ZOOM3, &CMidtermProjectView::OnUpdateViewZoom3)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ZOOM4, &CMidtermProjectView::OnUpdateViewZoom4)
	ON_WM_MOUSEMOVE()
	//	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_DIBINVERSE, &CMidtermProjectView::OnDibinverse)
	ON_COMMAND(ID_DIBCONTRAST, &CMidtermProjectView::OnDibcontrast)
	ON_COMMAND(ID_GAMMACORRECTION, &CMidtermProjectView::OnGammacorrection)
	ON_COMMAND(ID_HISTOGRAM, &CMidtermProjectView::OnHistogram)
	ON_COMMAND(ID_HISTO_EQUALIZE, &CMidtermProjectView::OnHistoEqualize)
	ON_COMMAND(ID_K_MEAN, &CMidtermProjectView::OnKMean)
	ON_COMMAND(ID_LBG, &CMidtermProjectView::OnLBG)
END_MESSAGE_MAP()

// CMidtermProjectView ����/�Ҹ�

CMidtermProjectView::CMidtermProjectView()
//: m_nZoom(1)
{
	m_nZoom = 1;
}

CMidtermProjectView::~CMidtermProjectView()
{
}

BOOL CMidtermProjectView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CScrollView::PreCreateWindow(cs);
}

// CMidtermProjectView �׸���

void CMidtermProjectView::OnDraw(CDC* pDC)
{
	CMidtermProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	if (pDoc->m_Dib.IsValid())
	{
		int w = pDoc->m_Dib.GetWidth();
		int h = pDoc->m_Dib.GetHeight();
		pDoc->m_Dib.Draw(pDC->m_hDC, 0, 0, w*m_nZoom, h*m_nZoom);
	}
}

void CMidtermProjectView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;

	CMidtermProjectDoc* pDoc = GetDocument();
	if (pDoc->m_Dib.IsValid())
	{
		sizeTotal.cx = pDoc->m_Dib.GetWidth();
		sizeTotal.cy = pDoc->m_Dib.GetHeight();
	}
	else
	{
		sizeTotal.cx = sizeTotal.cy = 100;
	}

	SetScrollSizes(MM_TEXT, sizeTotal);

	ResizeParentToFit(TRUE);
}

void CMidtermProjectView::SetScrollSizeToFit(void)
{
	CSize sizeTotal;

	CMidtermProjectDoc* pDoc = GetDocument();
	if (pDoc->m_Dib.IsValid())
	{
		int w = pDoc->m_Dib.GetWidth();
		int h = pDoc->m_Dib.GetHeight();

		sizeTotal.cx = w*m_nZoom;
		sizeTotal.cy = h*m_nZoom;
	}
	else
	{
		sizeTotal.cx = sizeTotal.cy = 100;
	}

	SetScrollSizes(MM_TEXT, sizeTotal);

	ResizeParentToFit(TRUE);
}

// CMidtermProjectView �μ�

BOOL CMidtermProjectView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CMidtermProjectView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CMidtermProjectView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}


// CMidtermProjectView ����

#ifdef _DEBUG
void CMidtermProjectView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CMidtermProjectView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CMidtermProjectDoc* CMidtermProjectView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMidtermProjectDoc)));
	return (CMidtermProjectDoc*)m_pDocument;
}
#endif //_DEBUG


// CMidtermProjectView �޽��� ó����

BOOL CMidtermProjectView::OnEraseBkgnd(CDC* pDC)
{
	CBrush br;
	br.CreateHatchBrush(HS_DIAGCROSS, RGB(200, 200, 200));
	FillOutsideRect(pDC, &br);

	return TRUE;      // Erased
}

void CMidtermProjectView::OnViewZoom1()
{
	m_nZoom = 1;
	SetScrollSizeToFit();
	Invalidate(TRUE);
}

void CMidtermProjectView::OnViewZoom2()
{
	m_nZoom = 2;
	SetScrollSizeToFit();
	Invalidate(TRUE);
}

void CMidtermProjectView::OnViewZoom3()
{
	m_nZoom = 3;
	SetScrollSizeToFit();
	Invalidate(TRUE);
}

void CMidtermProjectView::OnViewZoom4()
{
	m_nZoom = 4;
	SetScrollSizeToFit();
	Invalidate(TRUE);
}


void CMidtermProjectView::OnUpdateViewZoom1(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_nZoom == 1);
}

void CMidtermProjectView::OnUpdateViewZoom2(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_nZoom == 2);
}

void CMidtermProjectView::OnUpdateViewZoom3(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_nZoom == 3);
}

void CMidtermProjectView::OnUpdateViewZoom4(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_nZoom == 4);
}

void CMidtermProjectView::OnMouseMove(UINT nFlags, CPoint point)
{
	// ���¹ٿ� ���콺 ��ǥ �� �̹��� ���� ǥ��
	CPoint pt = point + GetScrollPosition();
	pt.x /= m_nZoom;
	pt.y /= m_nZoom;
	ShowImageInfo(pt);

	CScrollView::OnMouseMove(nFlags, point);
}

void CMidtermProjectView::ShowImageInfo(CPoint point)
{
	CMainFrame* pFrame = (CMainFrame *)AfxGetMainWnd();
	CMidtermProjectDoc* pDoc = GetDocument();
	int w = pDoc->m_Dib.GetWidth();
	int h = pDoc->m_Dib.GetHeight();
	int c = pDoc->m_Dib.GetPaletteNums();

	CString strText;

	// ���¹ٿ� ���콺 ��ǥ ǥ��

	if (point.x >= 0 && point.y >= 0 && point.x < w && point.y < h)
	{
		strText.Format(_T("(%d, %d)"), point.x, point.y);
		pFrame->m_wndStatusBar.SetPaneText(0, strText);
	}

	// ���¹ٿ� �̹��� ���� ǥ��

	if (c == 0)
	{
		strText.Format(_T("w:%d  h:%d  c:16M"), w, h);
	}
	else
	{
		strText.Format(_T("w:%d  h:%d  c:%d"), w, h, c);
	}
	pFrame->m_wndStatusBar.SetPaneText(1, strText);
}


void CMidtermProjectView::OnDibinverse()
{
	register int i, j, w, h;
	RGBBYTE** ptr;

	CMidtermProjectDoc* pDoc = GetDocument();
	if (pDoc->m_Dib.IsValid())
	{
		w = pDoc->m_Dib.GetWidth();
		h = pDoc->m_Dib.GetHeight();

		ptr = pDoc->m_Dib.GetRGBPtr();
	}

	for (j = 0; j < h; j++)
		for (i = 0; i < w; i++)
		{
			ptr[j][i].r = 255 - ptr[j][i].r;
			ptr[j][i].g = 255 - ptr[j][i].g;
			ptr[j][i].b = 255 - ptr[j][i].b;
		}
	Invalidate();
	//AfxNewImage(pDoc->m_Dib);
}

void CMidtermProjectView::OnDibcontrast()
{
	register int i, j, w, h, n = 100;
	RGBBYTE** ptr;

	CMidtermProjectDoc* pDoc = GetDocument();
	if (pDoc->m_Dib.IsValid())
	{
		w = pDoc->m_Dib.GetWidth();
		h = pDoc->m_Dib.GetHeight();

		ptr = pDoc->m_Dib.GetRGBPtr();
	}
	BYTE value;
	for (j = 0; j < h; j++)
		for (i = 0; i < w; i++)
		{
			value = (ptr[j][i].r + ptr[j][i].g + ptr[j][i].b) / 3;
			ptr[j][i].r = ptr[j][i].g = ptr[j][i].b =
				limit(value + ((value - 128) * n / 100));
		}

	Invalidate();
}

void CMidtermProjectView::OnGammacorrection()
{
	register int i, j, w, h;
	float value;
	RGBBYTE** ptr;

	CMidtermProjectDoc* pDoc = GetDocument();
	if (pDoc->m_Dib.IsValid())
	{
		w = pDoc->m_Dib.GetWidth();
		h = pDoc->m_Dib.GetHeight();

		ptr = pDoc->m_Dib.GetRGBPtr();
		AfxNewImage(pDoc->m_Dib);
	}
	float gamma = 2.5;
	float invgamma = 1.f / gamma;

	for (j = 0; j < h; j++)
		for (i = 0; i < w; i++)
		{
			value = (ptr[j][i].r + ptr[j][i].g + ptr[j][i].b) / 3.0f;
			//pow�������� �ݵ�� #include <math.h> ����Ǿ� �ִ��� Ȯ��
			ptr[j][i].r = ptr[j][i].g = ptr[j][i].b =
				(BYTE)limit(pow(value / 255.f, invgamma) * 255 + 0.5f);
		}
	Invalidate();
}

void CMidtermProjectView::OnHistogram()
{
	register int i, j, w, h;
	BYTE value;
	RGBBYTE** ptr;

	CMidtermProjectDoc* pDoc = GetDocument();
	if (pDoc->m_Dib.IsValid())
	{
		w = pDoc->m_Dib.GetWidth();
		h = pDoc->m_Dib.GetHeight();

		ptr = pDoc->m_Dib.GetRGBPtr();
	}

	// ������׷� ���

	int temp[256];
	float histo[256] = { 0.f, };
	memset(temp, 0, sizeof(int) * 256);
	for (j = 0; j < h; j++)
		for (i = 0; i < w; i++)
		{
			value = (ptr[j][i].r + ptr[j][i].g + ptr[j][i].b) / 3;
			temp[value]++;
		}

	// ������׷� ����ȭ(histogram normalization)

	float area = (float)w*h;
	for (i = 0; i < 256; i++)
		histo[i] = temp[i] / area;

	CHistogramDlg dlg;
	dlg.SetImage(histo);
	dlg.DoModal();
}

void CMidtermProjectView::OnHistoEqualize()
{
	register int i, j, w, h;
	BYTE value;
	RGBBYTE** ptr;

	CMidtermProjectDoc* pDoc = GetDocument();
	if (pDoc->m_Dib.IsValid())
	{
		w = pDoc->m_Dib.GetWidth();
		h = pDoc->m_Dib.GetHeight();

		ptr = pDoc->m_Dib.GetRGBPtr();
		AfxNewImage(pDoc->m_Dib);
	}
	int temp[256];
	float histo[256] = { 0.f, };

	memset(temp, 0, sizeof(int) * 256);
	for (j = 0; j < h; j++)
		for (i = 0; i < w; i++)
		{
			value = (ptr[j][i].r + ptr[j][i].g + ptr[j][i].b) / 3;
			temp[value]++;
		}

	// ������׷� ����ȭ

	float area = (float)w*h;
	for (i = 0; i < 256; i++)
		histo[i] = temp[i] / area;

	// ������׷� ���� �Լ� ���

	double cdf[256] = { 0.0, };
	cdf[0] = histo[0];
	for (i = 1; i < 256; i++)
		cdf[i] = cdf[i - 1] + histo[i];

	// ������׷� �յ�ȭ

	for (j = 0; j < h; j++)
		for (i = 0; i < w; i++)
		{
			value = (ptr[j][i].r + ptr[j][i].g + ptr[j][i].b) / 3;
			ptr[j][i].r = ptr[j][i].g = ptr[j][i].b = (BYTE)limit(cdf[value] * 255);
		}
	Invalidate();
}



void CMidtermProjectView::OnKMean()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.

	register int i, j, w, h;
	RGBBYTE** ptr = { NULL, }; // 24bit
	BYTE** grayPtr = { NULL, }; // 8bit

	// ����ȭ ����, ���� �Ӱ谪 ����
	int K = 2;
	int T = 1;

	int* ME = new int[K]; // ���� �߽ɰ� ���� �޸�

	CMidtermProjectDoc* pDoc = GetDocument();

	int select = pDoc->m_Dib.GetBitCount(); // ���� bit �� ����

	switch (select)
	{
	case 8:
	{
		if (pDoc->m_Dib.IsValid())
		{
			w = pDoc->m_Dib.GetWidth();
			h = pDoc->m_Dib.GetHeight();

			grayPtr = pDoc->m_Dib.GetPtr();
		}

		BYTE** image = new BYTE*[h];

		for (i = 0; i < h; i++)
		{
			image[i] = new BYTE[w];
		}

		for (j = 0; j < h; j++)
		{
			for (i = 0; i < w; i++)
			{
				image[j][i] = grayPtr[j][i];
			}
		}

		// �ʱ� ���� �߽ɰ��� ���� ���� �߻�
		srand((unsigned)time(NULL));

		for (i = 1; i < K; i++)
		{
			ME[i] = rand() % (255);
		}

		// ���� �Լ� ȣ��
		K_Mean_Clustering(image, ME, K, T, w, h);

		// ���� ��� �κ�
		for (j = 0; j < h; j++)
		{
			for (i = 0; i < w; i++)
			{
				grayPtr[j][i] = image[j][i];
			}
		}

		delete[] image;
		delete[] ME;

		break;
	}
	case 24:
	{
		if (pDoc->m_Dib.IsValid())
		{
			w = pDoc->m_Dib.GetWidth();
			h = pDoc->m_Dib.GetHeight();

			ptr = pDoc->m_Dib.GetRGBPtr();
		}

		BYTE** image = new BYTE*[h];

		for (i = 0; i < h; i++)
		{
			image[i] = new BYTE[w];
		}

		for (j = 0; j < h; j++)
		{
			for (i = 0; i < w; i++)
			{
				image[j][i] = (ptr[j][i].r + ptr[j][i].g + ptr[j][i].b) / 3.0f; // gray �� ����
			}
		}

		// �ʱ� ���� �߽ɰ��� ���� ���� �߻�
		srand((unsigned)time(NULL));

		for (i = 1; i < K; i++)
		{
			ME[i] = rand() % (255);
		}
		
		// ���� �Լ� ȣ��
		K_Mean_Clustering(image, ME, K, T, w, h); 
		
		// ���� ��� �κ�
		for (j = 0; j < h; j++)
		{
			for (i = 0; i < w; i++)
			{
				ptr[j][i].r = image[j][i];
				ptr[j][i].g = image[j][i];
				ptr[j][i].b = image[j][i];
			}
		}

		delete[] image;
		delete[] ME;

		break;
	}
	default:
		break;
	}

	Invalidate();
}

void CMidtermProjectView::K_Mean_Clustering(BYTE** image, int* ME, int K, int T, int w, int h) // , float* saveMean
{
	float* C_mean = new float[K]; // �� ������ �߽ɰ� ��� �޸�
	float* distance = new float[K]; // �� �������� �߽� �Ÿ� ��
	int* Count = new int[K]; // �� ������ ���� ����
	int* Cluster = new int[K]; // �� ���� ���� �ȼ��� �� ���� ���� �޸�

	int i, j, k, s;

	// ���� ��ȣ�� ����� �޸�
	int** label = new int*[h];

	for (i = 0; i < h; i++)
	{
		label[i] = new int[w];
		memset(label[i], 0, sizeof(int)*w);
	}

	float min, temp_mean, Sum_mean;

	for (k = 0; k < K; k++)
	{
		C_mean[k] = distance[k] = 0.0f;
		Count[k] = Cluster[k] = 0;
	}

	Sum_mean = min = temp_mean = 0.0f;

	for (k = 0; k < K; k++)
	{
		C_mean[k] = (float)ME[k]; // �ʱ� ��հ��� �ֱ�
	}

	for (i = 0; i < h; i++)
	{
		for (j = 0; j < w; j++)
		{
			// �� �ȼ��� �� ���� �߽ɰ������ �Ÿ��� ���ϱ�
			for (k = 0; k < K; k++)
			{
				distance[k] = (float)fabs(C_mean[k] - (float)image[i][j]);
			}
			min = distance[0];
			s = 0;
			// �Ÿ����� ���� ���� ��հ��� ã�´�.
			for (k = 1; k < K; k++)
			{
				if (distance[k] <= min)
				{
					min = distance[k];
					s = k;					
				}
			}
			// �ش� �ȼ����� �ջ�(���߿� ���ο� Ŭ�������� ��� ����� ����)
			Cluster[s] += image[i][j];

			// �ش� �ȼ��� �Ÿ��� ���� ����� Ŭ������ ��ȣ�� ����
			label[i][j] = s;

			// ���ο� ���(�߽�) ����� ���� ���� ī��Ʈ
			Count[s]++;
		}
	} // end of for

	for (k = 0; k < K; k++)
	{
		temp_mean = C_mean[k];

		if (Count[k] == 0)
		{
			C_mean[k] = 0.0;
		}
		else
		{
			// �� ������ ��� ���ϱ�
			C_mean[k] = (float)(Cluster[k] / Count[k]);
		}

		// �� ������ �߽ɰ��� ���� �߽ɰ����� ���̰� ���ϱ�
		Sum_mean += (float)fabs(C_mean[k] - temp_mean);
		temp_mean = (float) 0.0;
	}

	if (Sum_mean <= T) // ���� �߽ɰ��� �հ� ���� �߽ɰ��� ���� ���� ����
	{
		for (k = 0; k < K; k++)
		{
			for (i = 0; i < h; i++) // �� ������ ���ο� �߽ɰ����� ä�� ��
			{
				for (j = 0; j < w; j++)
				{
					if (label[i][j] == k)
					{
						image[i][j] = (unsigned char)C_mean[k];
						//saveMean[k] = C_mean[k];
					}
				}
			}

			std::cout << "k : " << k << "\ndistance : " << distance[k] << "\nC-mean : " << C_mean[k] << "\nSum-mean : " << Sum_mean << "\nME : " << ME[k] << "\ntemp mean : "<< temp_mean << std::endl;

		}

		

		return; // ���̰� ���� ���ٸ� ����ȭ ����
	}
	else // ���̰� ũ�ٸ� �ٽ� Ŭ������ ����� ��
	{
		Sum_mean = 0.0;
		for (k = 0; k < K; k++)
		{
			ME[k] = (int)C_mean[k];
		}
		K_Mean_Clustering(image, ME, K, T, w, h); // , saveMean
	}

	// �޸� ����
	for (i = 0; i < h; i++)
	{
		delete[] label[i];
	}
	delete[] label;
	delete[] C_mean;
	delete[] distance;
	delete[] Count;
	delete[] Cluster;
}

void CMidtermProjectView::OnLBG()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	register int i, j, w, h;
	RGBBYTE** ptr = { NULL, }; // 24bit
	BYTE** grayPtr = { NULL, }; // 8bit

	// ����ȭ ����, ���� �Ӱ谪 ����
	int K = 3;
	int T = 1;
	int midHistValue;

	int* ME = new int[K]; // ���� �߽ɰ� ���� �޸�

	CMidtermProjectDoc* pDoc = GetDocument();

	int select = pDoc->m_Dib.GetBitCount(); // ���� bit �� ����

	switch (select)
	{
	case 8:
	{

		break;
	}
	case 24:
	{
		if (pDoc->m_Dib.IsValid())
		{
			w = pDoc->m_Dib.GetWidth();
			h = pDoc->m_Dib.GetHeight();

			ptr = pDoc->m_Dib.GetRGBPtr();
		}	

		BYTE** image = new BYTE*[h];
		BYTE** temp = new BYTE*[h];

		for (i = 0; i < h; i++)
		{
			image[i] = new BYTE[w];
			temp[i] = new BYTE[w];
		}

		for (j = 0; j < h; j++)
		{
			for (i = 0; i < w; i++)
			{
				image[j][i] = (ptr[j][i].r + ptr[j][i].g + ptr[j][i].b) / 3.0f; // gray �� ����
			}
		}	
		
		midHistValue = CalcMidHist(image, w, h);

		ME[0] = midHistValue;

		float* saveMean = new float[K]; // �� ������ �߽ɰ� ��� �޸�

		LBG_Clustering(image, ME, K, T, w, h, saveMean);


		// ���� ��� �κ�
		for (j = 0; j < h; j++)
		{
			for (i = 0; i < w; i++)
			{
				ptr[j][i].r = image[j][i];
				ptr[j][i].g = image[j][i];
				ptr[j][i].b = image[j][i];
			}
		}
		delete[] image;
		delete[] ME;

		break;
	}
	default:
		break;
	}

	Invalidate();
}


int CMidtermProjectView::CalcMidHist(BYTE** image, int w, int h)
{
	// �׷��̽����� ������׷�
	int hist[256];
	float histGray[256] = { 0.f, };
	memset(hist, 0, sizeof(int) * 256);

	// ������׷� ����ȭ
	float area = (float)w*h;

	for (int j = 0; j < h; j++)
	{
		for (int i = 0; i < w; i++)
		{
			hist[image[j][i]]++;
		}
	}
	double cdf[256] = { 0.f, };
	cdf[0] = hist[0];

	int midHistValue = 0; // ������׷� �߰���

	for (int i = 0; i < 256; i++)
	{
		histGray[i] = hist[i] / area;
	}

	// ������׷� ���� �Լ� ���
	for (int i = 1; i < 256; i++)
	{
		cdf[i] = cdf[i - 1] + hist[i];
		midHistValue += cdf[i];
	}

	midHistValue = midHistValue / area;
	std::cout << "midHistValue : " << midHistValue << std::endl; // �Ҽ����� ���� �� �ֳ�?

	return midHistValue;
}

void CMidtermProjectView::LBG_Clustering(BYTE** image, int* ME, int K, int T, int w, int h, float* saveMean)
{
	int midHistValue = CalcMidHist(image, w, h);
	ME[0] = midHistValue;

	K_Mean_Clustering(image, ME, 2, T, w, h, saveMean);

	CDib Dib1, Dib2, Dib3, Dib4;
	Dib1.CreateRGBImage(w, h, 0x00FFFFFF);
	Dib2.CreateRGBImage(w, h, 0x00FFFFFF);
	RGBBYTE** ptr1 = Dib1.GetRGBPtr();
	RGBBYTE** ptr2 = Dib2.GetRGBPtr();

	Dib3.CreateGrayImage(w, h, 0x00FFFFFF);
	Dib4.CreateGrayImage(w, h, 0x00FFFFFF);
	BYTE** compare1 = Dib3.GetPtr();
	BYTE** compare2 = Dib4.GetPtr();


	for (int i = 0; i < K; i++)
	{
		std::cout << "saveMean : " << saveMean[i] << std::endl;
	}


	// ���� ��� �κ�
	for (int j = 0; j < h; j++)
	{
		for (int i = 0; i < w; i++)
		{
			if (image[j][i] == saveMean[0])
			{
				ptr1[j][i].r = image[j][i];
				ptr1[j][i].g = image[j][i];
				ptr1[j][i].b = image[j][i];
			}

			if (image[j][i] == saveMean[1])
			{
				ptr2[j][i].r = image[j][i];
				ptr2[j][i].g = image[j][i];
				ptr2[j][i].b = image[j][i];
			}
		}
	}
	

	if (K>2)
	{
		for (int a = 1; a < K; a++)
		{
			if (fabs(saveMean[a-1] - midHistValue) > fabs(saveMean[a] - midHistValue)) // ��� �Ÿ��� ū�Ÿ� ���
			{
				for (int j = 0; j < h; j++)
				{
					for (int i = 0; i < w; i++)
					{
						if (image[j][i] == saveMean[a-1])
						{
							compare1[j][i] = image[j][i];
						}
					}
				}
				midHistValue = CalcMidHist(compare1, w, h);
				ME[a] = midHistValue;
				K_Mean_Clustering(compare1, ME, 2, T, w, h);
			}
			else
			{
				for (int j = 0; j < h; j++)
				{
					for (int i = 0; i < w; i++)
					{
						if (image[j][i] == saveMean[a])
						{
							compare2[j][i] = image[j][i];
						}
					}
				}
				midHistValue = CalcMidHist(compare2, w, h);
				ME[a] = midHistValue;
				K_Mean_Clustering(compare2, ME, 2, T, w, h);
			}
		}
	}

	AfxNewImage(Dib1);
	AfxNewImage(Dib2);
}