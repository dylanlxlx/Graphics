
// Wu-anti-aliasingView.h: CWuantialiasingView 类的接口
//

#pragma once
#include "CP2.h"

class CWuantialiasingView : public CView
{
protected: // 仅从序列化创建
	CWuantialiasingView() noexcept;
	DECLARE_DYNCREATE(CWuantialiasingView)

// 特性
public:
	CWuantialiasingDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	void DrawAntiAliasingCircle(CDC* pDC);
	void DrawPointInCircle(CDC* pDC, CP2 p,COLORREF c1,COLORREF c2);
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CWuantialiasingView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // Wu-anti-aliasingView.cpp 中的调试版本
inline CWuantialiasingDoc* CWuantialiasingView::GetDocument() const
   { return reinterpret_cast<CWuantialiasingDoc*>(m_pDocument); }
#endif

