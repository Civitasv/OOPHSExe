
// OOPHSExeView.h : COOPHSExeView ��Ľӿ�
//
#include "oophsexedoc.h"
#pragma once

#include "GeoMap.h"

class COOPHSExeView : public CView
{
protected: // �������л�����
	COOPHSExeView();
	DECLARE_DYNCREATE(COOPHSExeView);

// ����
public:
	COOPHSExeDoc* GetDocument() const;

// ����
public:

// ��д
public:
	
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	

// ʵ��
public:
	//�����ͼʵ������
	CGeoMap *map;
	bool isMaploaded;
	CPoint ptOrg;	//��ʼ��
	CPoint ptEnd;	//������
	bool isMousePressed;
	bool isZoomIn;	//���Ų���
	bool isReturn;	//����ȫͼ
	bool isTranslate;	//ƽ�Ʋ���
	bool isClip;	//���в���
	CRect wcRect;
	CBitmap bmp;	//����ƽ�Ƶ�˫�����ڴ�ͼƬ
	CDC* dcMem;		//�ڴ�CDC*
	//CGeoMap map2;
	virtual ~COOPHSExeView();
	void readOPT();	//��ȡ��ɫ�ļ�
	void readAnno(); //��ȡע���ļ�
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

// ���ɵ���Ϣӳ�亯��
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

#ifndef _DEBUG  // OOPHSExeView.cpp �еĵ��԰汾
inline COOPHSExeDoc* COOPHSExeView::GetDocument() const
   { return reinterpret_cast<COOPHSExeDoc*>(m_pDocument); }
#endif

