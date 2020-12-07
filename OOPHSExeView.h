
// OOPHSExeView.h : COOPHSExeView 类的接口
//
#include "oophsexedoc.h"
#pragma once

#include "GeoMap.h"

class COOPHSExeView : public CView
{
protected: // 仅从序列化创建
	COOPHSExeView();
	DECLARE_DYNCREATE(COOPHSExeView);

// 特性
public:
	COOPHSExeDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	

// 实现
public:
	//引入地图实例对象
	CGeoMap *map;
	bool isMaploaded;
	CPoint ptOrg;	//起始点
	CPoint ptEnd;	//结束点
	bool isMousePressed;
	bool isZoomIn;	//缩放操作
	bool isReturn;	//返回全图
	bool isTranslate;	//平移操作
	bool isClip;	//裁切操作
	CRect wcRect;
	CBitmap bmp;	//用于平移的双缓存内存图片
	CDC* dcMem;		//内存CDC*
	//CGeoMap map2;
	virtual ~COOPHSExeView();
	void readOPT();	//读取颜色文件
	void readAnno(); //读取注记文件
	void readChina(FILE *fp); 
	void readWuhan(FILE *fp);
	void readCHN(FILE *fp);
	void readClip(FILE *fp);
	void readProj(FILE *fp);
	void convertColor(int color,CGeoObject *obj);
	
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnFileOpen();
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnButton32777();
	afx_msg void OnButton32779();
	afx_msg void OnUpdateButton32777(CCmdUI *pCmdUI);
	afx_msg void OnUpdateButton32779(CCmdUI *pCmdUI);
	afx_msg void OnButton32780();
	afx_msg void OnUpdateButton32780(CCmdUI *pCmdUI);
	afx_msg void OnButton32782();
	afx_msg void OnUpdateButton32782(CCmdUI *pCmdUI);
	
	afx_msg void OnSize(UINT nType, int cx, int cy);
	void makeProj(CMapProjection *mapProj);
};

#ifndef _DEBUG  // OOPHSExeView.cpp 中的调试版本
inline COOPHSExeDoc* COOPHSExeView::GetDocument() const
   { return reinterpret_cast<COOPHSExeDoc*>(m_pDocument); }
#endif

