// 이 MFC 샘플 소스 코드는 MFC Microsoft Office Fluent 사용자 인터페이스("Fluent UI")를 
// 사용하는 방법을 보여 주며, MFC C++ 라이브러리 소프트웨어에 포함된 
// Microsoft Foundation Classes Reference 및 관련 전자 문서에 대해 
// 추가적으로 제공되는 내용입니다.  
// Fluent UI를 복사, 사용 또는 배포하는 데 대한 사용 약관은 별도로 제공됩니다.  
// Fluent UI 라이선싱 프로그램에 대한 자세한 내용은 
// https://go.microsoft.com/fwlink/?LinkId=238214.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

// ChildView.cpp: CChildView 클래스의 구현
//

#include "stdafx.h"
#include "IntravascularOCT.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

int test22 =200;

test22 += 30;

test22 -= 55;


CChildView::CChildView()
{
	b_ViewMode = false;
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_COMMAND(ID_BUTTON_VIEW_CHANGE, &CChildView::OnButtonViewChange)
END_MESSAGE_MAP()



// CChildView 메시지 처리기

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), nullptr);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.
	
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	
	// 그리기 메시지에 대해서는 CWnd::OnPaint()를 호출하지 마십시오.
	CRect rect;

	GetClientRect(rect);

	//DLG 배치
	LONG xPos[3];

	xPos[0] = rect.left;
	xPos[1] = rect.left + rect.Width() / 2;
	xPos[2] = rect.right;

	LONG yPos[3];

	yPos[0] = rect.top;
	yPos[1] = rect.top + rect.Height() / 2;
	yPos[2] = rect.bottom;

	if (b_ViewMode)
	{
		CRect SubRect[4];
		SubRect[0] = CRect(xPos[0], yPos[0], xPos[1], yPos[1]); //Axial
		SubRect[1] = CRect(xPos[1], yPos[0], xPos[2], yPos[1]); //Coronal
		SubRect[2] = CRect(xPos[0], yPos[1], xPos[1], yPos[2]); //Sagital
		SubRect[3] = CRect(xPos[1], yPos[1], xPos[2], yPos[2]); //3DView


		for (int viewType = 0; viewType < 4; viewType++)
		{
			if (::IsWindow(m_dlgVtkView[viewType].GetSafeHwnd()))
			{
				m_dlgVtkView[viewType].MoveWindow(SubRect[viewType]);
			}
		}
	}
	else
	{
		CRect SubRect[4];
		SubRect[0] = CRect(0, 0, 1, 1); //Axial
		SubRect[1] = CRect(0, 0, 1, 1); //Coronal
		SubRect[2] = CRect(0, 0, 1, 1); //Sagital
		SubRect[3] = CRect(0, 0, xPos[2], yPos[2]); //3DView


		for (int viewType = 0; viewType < 4; viewType++)
		{
			if (::IsWindow(m_dlgVtkView[viewType].GetSafeHwnd()))
			{
				m_dlgVtkView[viewType].MoveWindow(SubRect[viewType]);
			}
		}
	}
}



int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	// VTK View Dialog 생성
	for (int viewType = 0; viewType < 4; viewType++) {
		m_dlgVtkView[viewType].set_view_type(viewType);
		if (!m_dlgVtkView[viewType].Create(IDD_VOLUME_VIEW, this))
			return -1;
		m_dlgVtkView[viewType].ShowWindow(SW_SHOW);
	}

	return 0;
}


BOOL CChildView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	return FALSE;
	//return CWnd::OnEraseBkgnd(pDC);
}


void CChildView::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if (!::IsWindow(GetSafeHwnd()))
		return;

	if (cx == 0 || cy == 0)
		return;

	CRect rect;
	GetClientRect(rect);

	// 메인 뷰에 포함된 Dialog 배치 (4분할)
	LONG xPos[3];
	xPos[0] = rect.left;
	xPos[1] = rect.left + rect.Width() / 2;
	xPos[2] = rect.right;

	LONG yPos[3];
	yPos[0] = rect.top;
	yPos[1] = rect.top + rect.Height() / 2;
	yPos[2] = rect.bottom;

	//CRect subRect[4];
	//subRect[0] = CRect(xPos[0], yPos[0], xPos[1], yPos[1]);		// Axial
	//subRect[1] = CRect(xPos[1], yPos[0], xPos[2], yPos[1]);		// Coronal
	//subRect[2] = CRect(xPos[0], yPos[1], xPos[1], yPos[2]);		// Sagittal
	//subRect[3] = CRect(xPos[1], yPos[1], xPos[2], yPos[2]);		// 3D View

	//// VTK Window 배치
	//for (int viewType = 0; viewType < 4; viewType++) {
	//	if (::IsWindow(m_dlgVtkView[viewType].GetSafeHwnd())) {
	//		m_dlgVtkView[viewType].MoveWindow(subRect[viewType]);
	//	}
	//}

	if (b_ViewMode)
	{
		CRect SubRect[4];
		SubRect[0] = CRect(xPos[0], yPos[0], xPos[1], yPos[1]); //Axial
		SubRect[1] = CRect(xPos[1], yPos[0], xPos[2], yPos[1]); //Coronal
		SubRect[2] = CRect(xPos[0], yPos[1], xPos[1], yPos[2]); //Sagital
		SubRect[3] = CRect(xPos[1], yPos[1], xPos[2], yPos[2]); //3DView


		for (int viewType = 0; viewType < 4; viewType++)
		{
			if (::IsWindow(m_dlgVtkView[viewType].GetSafeHwnd()))
			{
				m_dlgVtkView[viewType].MoveWindow(SubRect[viewType]);
			}
		}
	}
	else
	{
		CRect SubRect[4];
		SubRect[0] = CRect(0, 0, 1, 1); //Axial
		SubRect[1] = CRect(0, 0, 1, 1); //Coronal
		SubRect[2] = CRect(0, 0, 1, 1); //Sagital
		SubRect[3] = CRect(0, 0, xPos[2], yPos[2]); //3DView


		for (int viewType = 0; viewType < 4; viewType++)
		{
			if (::IsWindow(m_dlgVtkView[viewType].GetSafeHwnd()))
			{
				m_dlgVtkView[viewType].MoveWindow(SubRect[viewType]);
			}
		}
	}
}

CVolumeView* CChildView::GetDlgVTKView(int viewType) {
	if (viewType < 0 || viewType > 3)
		return NULL;

	return &m_dlgVtkView[viewType];
}

void CChildView::OnButtonViewChange()
{
	// TODO: Add your command handler code here
	if (b_ViewMode)
		b_ViewMode = false;
	else
		b_ViewMode = true;
	Invalidate();
}
