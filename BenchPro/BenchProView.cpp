
// BenchProView.cpp : implementation of the CBenchProView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "BenchPro.h"
#endif

#include "BenchProDoc.h"
#include "BenchProView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CBenchProView

IMPLEMENT_DYNCREATE(CBenchProView, CView)

BEGIN_MESSAGE_MAP(CBenchProView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CBenchProView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CBenchProView construction/destruction

CBenchProView::CBenchProView() noexcept
{
	// TODO: add construction code here

}

CBenchProView::~CBenchProView()
{
}

BOOL CBenchProView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CBenchProView drawing

void CBenchProView::OnDraw(CDC* /*pDC*/)
{
	CBenchProDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CBenchProView printing


void CBenchProView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CBenchProView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CBenchProView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CBenchProView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CBenchProView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

//void CBenchProView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
//{
//#ifndef SHARED_HANDLERS
//	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
//#endif
//}


// CBenchProView diagnostics

#ifdef _DEBUG
void CBenchProView::AssertValid() const
{
	CView::AssertValid();
}

void CBenchProView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CBenchProDoc* CBenchProView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBenchProDoc)));
	return (CBenchProDoc*)m_pDocument;
}
#endif //_DEBUG


// CBenchProView message handlers
