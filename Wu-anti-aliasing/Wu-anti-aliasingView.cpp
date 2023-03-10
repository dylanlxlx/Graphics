
// Wu-anti-aliasingView.cpp: CWuantialiasingView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Wu-anti-aliasing.h"
#endif

#include "Wu-anti-aliasingDoc.h"
#include "Wu-anti-aliasingView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "CP2.h"


// CWuantialiasingView

IMPLEMENT_DYNCREATE(CWuantialiasingView, CView)

BEGIN_MESSAGE_MAP(CWuantialiasingView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CWuantialiasingView 构造/析构

CWuantialiasingView::CWuantialiasingView() noexcept
{
	// TODO: 在此处添加构造代码

}

CWuantialiasingView::~CWuantialiasingView()
{
}

BOOL CWuantialiasingView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式
	return CView::PreCreateWindow(cs);
}

// CWuantialiasingView 绘图

void CWuantialiasingView::DrawAntiAliasingCircle(CDC* pDC)
{
	int r = 200;	//圆半径
	double e = r;	//误差项
	double h = r;
	CP2 p;
	for (p.x = 0, p.y = r; p.x <= p.y; p.x++)	//八分之一圆 （x < y）
	{
		e = h - sqrt(r * r - pow(p.x + 1, 2));  // e = h - √(r² - (x + 1)²)
		if (e >= 1) {
			h--;
			e--;
			p.y--;
		}
		//颜色
		COLORREF c1 = RGB(188, 188, 188 * e);
		COLORREF c2 = RGB(188, 188, 188 * (1 - e));
		DrawPointInCircle(pDC, p, c1, c2);
	}
}

void CWuantialiasingView::DrawPointInCircle(CDC* pDC, CP2 p, COLORREF c1, COLORREF c2)
{
	pDC->SetPixel(round(p.x), round(p.y), c1);
	pDC->SetPixel(round(p.x), round(p.y - 1), c2);

	pDC->SetPixel(round(p.y), round(p.x), c1);
	pDC->SetPixel(round(p.y - 1), round(p.x), c2);

	pDC->SetPixel(round(p.y), -round(p.x), c1);
	pDC->SetPixel(round(p.y - 1), -round(p.x), c2);

	pDC->SetPixel(round(p.x), -round(p.y), c1);
	pDC->SetPixel(round(p.x), -round(p.y - 1), c2);

	pDC->SetPixel(-round(p.x), -round(p.y), c1);
	pDC->SetPixel(-round(p.x), -round(p.y - 1), c2);

	pDC->SetPixel(-round(p.y), -round(p.x), c1);
	pDC->SetPixel(-round(p.y - 1), -round(p.x), c2);

	pDC->SetPixel(-round(p.y), round(p.x), c1);
	pDC->SetPixel(-round(p.y - 1), round(p.x), c2);

	pDC->SetPixel(-round(p.x), round(p.y), c1);
	pDC->SetPixel(-round(p.x), round(p.y - 1), c2);
}

void CWuantialiasingView::OnDraw(CDC* pDC)
{
	CWuantialiasingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码

	//圆心固定至窗口中心
	CRect cr;
	GetWindowRect(&cr);
	double px = cr.Width() / 2.0;
	double py = cr.Height() / 2.0;
	pDC->SetViewportOrg(round(px), round(py));

	DrawAntiAliasingCircle(pDC);
}


// CWuantialiasingView 打印

BOOL CWuantialiasingView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CWuantialiasingView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CWuantialiasingView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CWuantialiasingView 诊断

#ifdef _DEBUG
void CWuantialiasingView::AssertValid() const
{
	CView::AssertValid();
}

void CWuantialiasingView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CWuantialiasingDoc* CWuantialiasingView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWuantialiasingDoc)));
	return (CWuantialiasingDoc*)m_pDocument;
}
#endif //_DEBUG


// CWuantialiasingView 消息处理程序
