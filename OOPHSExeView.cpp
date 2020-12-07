
// OOPHSExeView.cpp : COOPHSExeView ���ʵ��
//

#include "stdafx.h"
#include <afxpriv.h>
#include <math.h>
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "OOPHSExe.h"
#endif
#include "string"
#include "OOPHSExeDoc.h"
#include "OOPHSExeView.h"
#include "excel.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// COOPHSExeView

IMPLEMENT_DYNCREATE(COOPHSExeView, CView)

	BEGIN_MESSAGE_MAP(COOPHSExeView, CView)
		// ��׼��ӡ����
		ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
		ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
		ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
		ON_COMMAND(ID_FILE_OPEN, &COOPHSExeView::OnFileOpen)
		//		ON_WM_MOUSEHWHEEL()
		//ON_WM_MOUSEWHEEL()
		//ON_WM_MOUSEMOVE()
		//ON_WM_LBUTTONDBLCLK()
		ON_WM_MOUSEMOVE()
		ON_WM_LBUTTONUP()
		ON_WM_LBUTTONDOWN()
		ON_COMMAND(ID_BUTTON32777, &COOPHSExeView::OnButton32777)
		ON_COMMAND(ID_BUTTON32779, &COOPHSExeView::OnButton32779)
		ON_UPDATE_COMMAND_UI(ID_BUTTON32777, &COOPHSExeView::OnUpdateButton32777)
		ON_UPDATE_COMMAND_UI(ID_BUTTON32779, &COOPHSExeView::OnUpdateButton32779)
		ON_COMMAND(ID_BUTTON32780, &COOPHSExeView::OnButton32780)
		ON_UPDATE_COMMAND_UI(ID_BUTTON32780, &COOPHSExeView::OnUpdateButton32780)
		ON_COMMAND(ID_BUTTON32782, &COOPHSExeView::OnButton32782)
		ON_UPDATE_COMMAND_UI(ID_BUTTON32782, &COOPHSExeView::OnUpdateButton32782)
		ON_WM_SIZE()
	END_MESSAGE_MAP()

	// COOPHSExeView ����/����

	COOPHSExeView::COOPHSExeView()
	{
		this->map = NULL;
		this->isMaploaded = FALSE;
		this->ptOrg = NULL;
		this->ptEnd = NULL;
		isMousePressed = FALSE;
		this->isZoomIn = FALSE;
		this->isReturn = FALSE;
		this->wcRect = NULL;
		this->isTranslate = FALSE;
		this->isClip = FALSE;
		this->dcMem = NULL;
	}

	COOPHSExeView::~COOPHSExeView()
	{
		if(map!=NULL){
			delete map;
		}
		if(dcMem !=NULL){
			dcMem->DeleteDC();	//���ն�ӦͼƬ
			bmp.DeleteObject();	//���ͼƬ��CDC*��İ�
			delete dcMem;
		}
	}

	BOOL COOPHSExeView::PreCreateWindow(CREATESTRUCT& cs)
	{
		// TODO: �ڴ˴�ͨ���޸�
		//  CREATESTRUCT cs ���޸Ĵ��������ʽ

		return CView::PreCreateWindow(cs);
	}

	// COOPHSExeView ����

	void COOPHSExeView::OnDraw(CDC* pDC)
	{
		COOPHSExeDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		if (!pDoc)
			return;
		if(map == NULL)
			return;
		CRect rect;
		GetClientRect(&rect);
		/*
		if(map!=NULL){
		int layerSize = map->geoLayers.GetSize();
		for(int i=0;i<layerSize;i++){
		int objectSize = (map->geoLayers).GetAt(i)->geoObjects.GetSize();
		}

		map->draw(pDC);
		}
		*/
		if(dcMem == NULL){
			dcMem = new CDC();	//�½�DC
			dcMem->CreateCompatibleDC(pDC);	//������pDC
			bmp.CreateCompatibleBitmap(pDC,rect.Width(),rect.Height());
			dcMem->SelectObject(&bmp);
		}
		pDC->DPtoLP(&rect);
		OnPrepareDC(dcMem);
		dcMem->FillSolidRect(rect,pDC->GetBkColor());
		map->draw(dcMem);
		pDC->BitBlt(rect.left,rect.top,rect.Width(),rect.Height(),dcMem,rect.left,rect.top,SRCCOPY);

	}


	// COOPHSExeView ��ӡ

	BOOL COOPHSExeView::OnPreparePrinting(CPrintInfo* pInfo)
	{
		// Ĭ��׼��
		return DoPreparePrinting(pInfo);
	}

	void COOPHSExeView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
	{
		// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
	}

	void COOPHSExeView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
	{
		// TODO: ��Ӵ�ӡ����е��������
	}


	// COOPHSExeView ���

#ifdef _DEBUG
	void COOPHSExeView::AssertValid() const
	{
		CView::AssertValid();
	}

	void COOPHSExeView::Dump(CDumpContext& dc) const
	{
		CView::Dump(dc);
	}

	COOPHSExeDoc* COOPHSExeView::GetDocument() const // �ǵ��԰汾��������
	{
		ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COOPHSExeDoc)));
		return (COOPHSExeDoc*)m_pDocument;
	}
#endif //_DEBUG


	// COOPHSExeView ��Ϣ�������
	/*void COOPHSExeView::OnFileOpen(){

	}*/
	void COOPHSExeView::OnFileOpen()
	{
		// TODO: �ڴ���������������
		CFileDialog dlg(true);
		if( dlg.DoModal() != IDOK )
			return;

		CString fileName = dlg.GetPathName();
		USES_CONVERSION;
		//CString --> char *
		char *filename = T2A(fileName);
		FILE *fp;
		fopen_s(&fp,filename,"r");

		if(fp==NULL)
		{
			MessageBox(CString("File Open Failed!"));
			return;
		}

		if(map!=NULL)
			delete map;
		map = new CGeoMap();
		if(!fileName.CompareNoCase(CString("C:\\�����\\c++ʵϰ\\china1.dat"))){
			readChina(fp);
		}
		else if(!fileName.CompareNoCase(CString("C:\\�����\\c++ʵϰ\\wuhan.txt"))){
			readWuhan(fp);
		}
		else if(!fileName.CompareNoCase(CString("D:\\�����\\�����ͼ��ѧ\\chnFillTest.txt"))){
			readCHN(fp);
		}
		else if(!fileName.CompareNoCase(CString("D:\\�����\\�����ͼ��ѧ\\clipData.txt"))){
			readClip(fp);
		}
		else if(!fileName.CompareNoCase(CString("D:\\�����\\�����ͼ��ѧ\\BOUNT_line.mif"))){
			readProj(fp);
		}
		else if(!fileName.CompareNoCase(CString("D:\\�����\\�����ͼ��ѧ\\diquJie_polyline.mif"))){
			readProj(fp);
		}

		Invalidate();
	}

	void COOPHSExeView::readProj(FILE *fp){
		CGeoLayer *layer = new CGeoLayer();
		map->addLayer(layer);
		CMapProjection *mapProj = new CMapProjection();
		map->mapProj = mapProj;
		/*-----------��ȡ��Χ------------*/
		double left,top,right,bottom;
		char *str = new char[];
		char tag;
		fscanf(fp,"%s %s",str,str);
		fscanf(fp,"%s %s",str,str);
		fscanf(fp,"%s %s %s %s %s %c%lf%c%lf%c %c%lf%c%lf",str,str,str,str,str,&tag,&left,&tag,&bottom,&tag,&tag,&right,&tag,&top);
		map->setRect(CRect(left*pow(10,6),top*pow(10,6),right*pow(10,6),bottom*pow(10,6)));
		this->wcRect = map->getRect();
		mapProj->wcRect = map->getRect();
		/*-----------��������-------------*/
		while(strcmp(str,"LINE") != 0 && strcmp(str,"PLINE") != 0)
			fscanf(fp,"%s",str);
		/*-----------ѭ����ȡpolyline-----*/
		int count;
		int i = 1;
		double latiude,logitude;
		while(!feof(fp)){
			if(strcmp(str,"LINE") == 0){
				CGeoObject *obj = new CGeoPolyline();
				layer->addObjects(obj);
				obj->setId(i);
				i++;
				fscanf(fp,"%lf %lf",&logitude,&latiude);
				((CGeoPolyline *)obj)->addPoint(CPoint(logitude*pow(10,6),latiude*pow(10,6)));
				fscanf(fp,"%lf %lf",&logitude,&latiude);
				((CGeoPolyline *)obj)->addPoint(CPoint(logitude*pow(10,6),latiude*pow(10,6)));
			}
			else{
				fscanf(fp,"%d",&count);
				CGeoObject *obj = new CGeoPolyline();
				obj->setId(i);
				i++;
				layer->addObjects(obj);
				for(int i=0;i<count;i++){
					fscanf(fp,"%lf %lf",&logitude,&latiude);
					((CGeoPolyline *)obj)->addPoint(CPoint(logitude*pow(10,6),latiude*pow(10,6)));
				}
			}
			fscanf(fp,"%s",str);
		}
		makeProj(mapProj);
		fclose(fp);
		this->isMaploaded = TRUE;
	}
	
	// ����ī����ͶӰ
	void COOPHSExeView::makeProj(CMapProjection *mapProj)
	{
		// ����map����
		float latProj,lonProj;
		CRect rect;
		mapProj->getXY(map->getRect().top/pow(10,6),map->getRect().left/pow(10,6),&latProj,&lonProj);
		rect.left = latProj;
		rect.top = lonProj;
		mapProj->getXY(map->getRect().bottom/pow(10,6),map->getRect().right/pow(10,6),&latProj,&lonProj);
		rect.right = latProj;
		rect.bottom = lonProj;
		map->setRect(rect);
		
		this->wcRect = rect;
		
		for(int i=0;i<map->geoLayers.GetSize();i++){
			for(int j=0;j<map->geoLayers.GetAt(i)->geoObjects.GetSize();j++){
				CGeoPolyline *polyline = (CGeoPolyline* )map->geoLayers.GetAt(i)->geoObjects.GetAt(j);
				for(int k=0;k<polyline->pts.GetSize();k++){
					mapProj->getXY(polyline->pts.GetAt(k).y/pow(10,6),polyline->pts.GetAt(k).x/pow(10,6),&latProj,&lonProj);
					polyline->pts.GetAt(k) = CPoint(latProj,lonProj);
				}
			}
		}
			
	}

	void COOPHSExeView::readClip(FILE *fp){
		/*--------------------��ȡ��Χ---------------------*/
		int left,top,right,bottom;
		fscanf_s(fp,"%d%d%d%d",&left,&top,&right,&bottom);
		map->setRect(CRect(left,top,right,bottom));
		this->wcRect = map->getRect();
		CGeoLayer *layer = new CGeoLayer();
		map->addLayer(layer);
		int count,x,y;
		while(!feof(fp)){
			CGeoObject *obj = new CGeoPolyline();
			layer->addObjects(obj);
			fscanf_s(fp,"%d",&count);
			for(int i=0;i<count;i++){
				fscanf_s(fp,"%d%d",&x,&y);
				((CGeoPolyline *)obj)->addPoint(CPoint(x,y));
			}
		}
		fclose(fp);
		this->isMaploaded = TRUE;
	}

	void COOPHSExeView::readCHN(FILE *fp){
		CGeoLayer *layer = new CGeoLayer();
		map->addLayer(layer);
		int m,n,x,y,color;
		while(!feof(fp)){
			CGeoObject *obj = new CGeoPolygon();
			obj->areaType = 1;
			layer->addObjects(obj);
			//��ȡ����θ���
			fscanf_s(fp,"%d",&n);
			for(int i=0;i<n;i++){
				fscanf_s(fp,"%d",&m);
				for(int j=0;j<m;j++){
					fscanf_s(fp,"%d%d",&x,&y);
					if(i==0)
						((CGeoPolygon *)obj)->addPoint(CPoint(x,y));
				}
			}
			// ��ȡ�ڲ���
			fscanf_s(fp,"%d%d",&x,&y);
			((CGeoPolygon *)obj)->seeds.Add(CPoint(x,y));
			// ��ȡ��ɫ
			fscanf_s(fp,"%d",&color);
			convertColor(color,obj);
		}
		fclose(fp);
	}

	void COOPHSExeView::convertColor(int color,CGeoObject *obj)//16������ɫֵ
	{
		obj->r2 = byte((color >> 16) & 255);
		obj->g2 = byte((color>> 8) & 255);
		obj->b2 = byte((color >> 0) & 255);
	}
	void COOPHSExeView::readWuhan(FILE *fp){
		CGeoLayer *layer = new CGeoLayer();
		map->addLayer(layer);
		//map1.addLayer(layer);
		int x1,y1,x2,y2;
		CGeoObject *obj = NULL;
		while( !feof(fp))
		{
			CGeoObject *obj = new CGeoPolyline;
			layer->addObjects(obj);
			fscanf_s(fp,"%d%d%d%d",&x1,&y1,&x2,&y2);
			((CGeoPolyline *)obj)->addPoint(CPoint(x1,y1));
			((CGeoPolyline *)obj)->addPoint(CPoint(x2,y2));
		}
		fclose(fp);
		this->isMaploaded = FALSE;
	}
	void COOPHSExeView::readChina(FILE *fp){
		/*--------------------��ȡ��Χ---------------------*/
		int left,top,right,bottom;
		fscanf_s(fp,"%d,%d%d,%d",&left,&top,&right,&bottom);
		map->setRect(CRect(left,top,right,bottom));
		this->wcRect = map->getRect();
		/*-------------------------------------------------*/
		/*--------------------��ȡ����---------------------*/
		int layerNum;
		fscanf_s(fp,"%d",&layerNum);
		/*--------------------��ȡÿһ��-------------------*/
		for(int i=0;i<layerNum;i++){
			CGeoLayer *layer = new CGeoLayer();
			map->addLayer(layer);
			//��ȡ������С
			int layerSize;
			fscanf_s(fp,"%d",&layerSize);
			//��ȡ����
			char *layerName = new char[layerSize+1];
			char tag;
			fread( &tag , sizeof(char) , 1 , fp ) ;  
			fread( layerName , sizeof(char) , layerSize+1 , fp ) ;  
			layerName[layerSize] = '\0';
			layer->setName(CString(layerName));
			delete []layerName;
			//��ȡĿ����Ŀ
			int number;
			fscanf_s(fp,"%d",&number);
			CGeoObject *obj = NULL;
			//�ж�Ŀ�����Ͳ���ȡÿһ��Ŀ��
			for(int i=0;i<number;i++){
				//��ȡĿ������
				int type;
				fscanf_s(fp,"%d",&type);
				/*switch(type){
				case 1:addPolylines();break;
				case 2:addPolygons();break;
				case 4:addAnnotations();break;
				}*/
				if(type==1){
					//ÿһ�����ϵĵ�
					int x,y;
					fscanf_s(fp,"%d,%d",&x,&y);
					obj = new CGeoPolyline;
					while(!(x==-99999&&y==-99999))
					{
						//layer->addObjects(obj);
						((CGeoPolyline *)obj)->addPoint(CPoint(x,y));
						fscanf_s(fp,"%d,%d",&x,&y);
					}
					layer->addObjects(obj);

				}else if(type==2){
					//ÿһ�����ϵĵ�
					int x,y;
					fscanf_s(fp,"%d,%d",&x,&y);
					obj = new CGeoPolygon;
					while(!(x==-99999&&y==-99999))
					{
						//layer->addObjects(obj);
						((CGeoPolygon *)obj)->addPoint(CPoint(x,y));
						fscanf_s(fp,"%d,%d",&x,&y);
					}
					layer->addObjects(obj);
				}
			}
		}

		readOPT();
		readAnno();
		fclose(fp);
		this->isMaploaded = TRUE;
	}
	void COOPHSExeView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo)
	{
		// TODO: �ڴ����ר�ô����/����û���
		// TODO: Add your specialized code here and/or call the base class
		//���һ��bool�����������Ƿ���������Ҫ�任��������ݼ��أ����û�м��أ�����Ҫ����任

		if( !this->isMaploaded ) 
			return;
		CSize windowsize; 
		CSize logicsize;
		CPoint pt;	
		CRect rectD;

		this->GetClientRect(&rectD);//ȡ�ÿͻ������������С
		windowsize = rectD.Size();
		pt = rectD.CenterPoint();//ȡ�ÿͻ��������������ĵ�����

		pDC->SetMapMode(MM_ISOTROPIC); //����ָ���豸������ӳ�䷽ʽ
		pDC->SetViewportExt(windowsize);  //�趨�ӿڳߴ�
		pDC->SetViewportOrg(pt); //�����ӿ�����Ϊ����ϵԭ��

		logicsize = wcRect.Size();  //�趨���ڶ�Ӧ�ߴ�
		double ratio = -windowsize.cx*1.0/windowsize.cy;
		logicsize.cx = logicsize.cy*ratio;
		//CRect rect(-932833,1937773,2109383,-572515);
		pt = wcRect.CenterPoint(); //���ô�������Ϊ��Ӧԭ��
		//size = rect.Size();
		//pt = rect.CenterPoint();
		pDC->SetWindowExt(logicsize);   //���ô��ڳ���
		pDC->SetWindowOrg(pt);	//���ô���ԭ��
		CView::OnPrepareDC(pDC, pInfo);
	}

	//��ȡ��ɫ�ļ�
	void COOPHSExeView::readOPT(){
		FILE *fp;
		fopen_s(&fp,"C:\\�����\\c++ʵϰ\\china1.opt","r");
		/*--------------------��ȡ����---------------------*/
		int layerNum;
		fscanf_s(fp,"%d",&layerNum);
		for(int i=0;i<layerNum;i++){
			//��ȡ����
			char name[20];
			char tag;
			int j = 0;
			//������һ��\n
			fread( &tag , sizeof(char) , 1 , fp );
			fread( &tag , sizeof(char) , 1 , fp );
			while(tag!='\n'){
				name[j] = tag;
				j++;
				fread( &tag , sizeof(char) , 1 , fp );
			}
			char *layerName = new char[j];

			for(int k=0;k<j;k++){
				layerName[k] = name[k];
			}
			layerName[j] = '\0';
			char a = layerName[j];
			//���ݲ������ĳһ��
			CGeoLayer* layer = map->getLayerByName(CString(layerName));
			//��ȡ����
			int lineType;
			fscanf_s(fp,"%d",&lineType);
			//��ȡ�߿�
			double lineWidth = 0;
			if(lineType == 1){
				fscanf_s(fp,"%lf",&lineWidth);
			}
			//��ȡ��ɫ
			int r=0,g=0,b=0;
			if(lineType==1&&lineWidth!=0){
				fscanf_s(fp,"%d,%d,%d",&r,&g,&b);
			}
			//��ȡ����
			int areaType;
			fscanf_s(fp,"%d",&areaType);
			int r2=0,g2=0,b2=0;
			if(areaType == 1){
				fscanf_s(fp,"%d,%d,%d",&r2,&g2,&b2);
			}
			int size = layer->geoObjects.GetSize();
			for(int i=0;i<size;i++){
				layer->geoObjects.GetAt(i)->lineType = lineType;
				if(lineType == 1){
					layer->geoObjects.GetAt(i)->lineType = lineWidth;
					if(lineWidth!=0){
						layer->geoObjects.GetAt(i)->r = r;
						layer->geoObjects.GetAt(i)->g = g;
						layer->geoObjects.GetAt(i)->b = b;
					}
				}
				layer->geoObjects.GetAt(i)->areaType = areaType;
				if(areaType==1){
					layer->geoObjects.GetAt(i)->r2 = r2;
					layer->geoObjects.GetAt(i)->g2 = g2;
					layer->geoObjects.GetAt(i)->b2 = b2;
				}
			}
		}
	}
	void COOPHSExeView::readAnno(){
		CString Infilepath = CString("C:\\�����\\c++ʵϰ\\chnCity.xls");
		std::string path;
		path = CT2A(Infilepath);
		//char* path = const_cast<char*>(line1.c_str()); //sting ת char*
		Excel excl;
		bool bInit = excl.initExcel();

		//��excel�ļ�
		if (!excl.open(path.c_str()))
		{
			AfxMessageBox(_T("excel�ļ��򿪳���!"));
		}

		CString strSheetName = excl.getSheetName(1);//��ȡ��һ��sheet��  
		bool bLoad = excl.loadSheet(strSheetName);//װ��sheet  
		int nRow = excl.getRowCount();//��ȡsheet������  
		int nCol = excl.getColumnCount();//��ȡsheet������  
		CString cell;
		std::string cells;
		CGeoObject *obj = NULL;
		CGeoLayer *layer = new CGeoLayer();
		CConvexHull *hull = new CConvexHull();
		map->addLayer(layer);
		layer->addObjects(hull);
		for (int i = 2; i <= nRow; ++i)
		{
			int x=0,y=0;
			obj = new CGeoAnno;
			for(int j = 1;j<=nCol;++j){
				cell = excl.getCellString(i, j);  ////��ȡһ����Ԫ������
				// cells = CT2A(cell);      //����ȡ�ĵ�Ԫ��ת��Ϊstring��������
				if(j == 1)
					((CGeoAnno *)obj) ->annoName = cell;
				else if(j == 2){
					((CGeoAnno *)obj) ->point.x = _ttoi(cell);
					x = _ttoi(cell);
				}
				else if(j == 3){
					((CGeoAnno *)obj) ->point.y = _ttoi(cell);
					y = _ttoi(cell);;
				}
			}
			hull->pts.Add(CPoint(x,y));
			layer->addObjects(obj);
		}
	}


	void COOPHSExeView::OnMouseMove(UINT nFlags, CPoint point)
	{
		if(isZoomIn == FALSE&&isClip==FALSE&&isTranslate==FALSE){
			return;
		}
		// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
		if(!this->isMousePressed){
			return;
		}
		CDC *pDC  = GetDC();
		pDC->SetROP2(R2_NOTXORPEN);
		if(isTranslate==FALSE)
			pDC->Rectangle(CRect(ptOrg,ptEnd));
		ptEnd = point;
		if(isTranslate==FALSE)
			pDC->Rectangle(CRect(ptOrg,ptEnd));

		CView::OnMouseMove(nFlags, point);
	}


	void COOPHSExeView::OnLButtonUp(UINT nFlags, CPoint point)
	{
		if(isZoomIn == TRUE){
			this->isMousePressed = FALSE;
			// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
			CDC *dc = this->GetDC();
			OnPrepareDC(dc);
			this->ptEnd = point;
			if(ptEnd.x == ptOrg.x&&ptEnd.y==ptOrg.y){
				return;
			}
			dc->DPtoLP(&ptOrg);
			dc->DPtoLP(&ptEnd);

			if(ptOrg.y<ptEnd.y){
				int x = ptOrg.y;
				ptOrg.y = ptEnd.y;
				ptEnd.y = x;
			}
			this->wcRect = CRect(ptOrg,ptEnd);
			dc->Rectangle(CRect(ptOrg,ptEnd));
			Invalidate();
			CView::OnLButtonUp(nFlags, point);
		}
		else if(isClip == TRUE)
		{
			this->isMousePressed = FALSE;

			// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
			CDC *dc = this->GetDC();
			OnPrepareDC(dc);
			this->ptEnd = point;
			if(ptEnd.x == ptOrg.x&&ptEnd.y==ptOrg.y){
				return;
			}
			dc->DPtoLP(&ptOrg);
			dc->DPtoLP(&ptEnd);
			CPoint downPoint = ptOrg;
			CPoint upPoint = ptEnd;
			int xmax = downPoint.x>upPoint.x?downPoint.x:upPoint.x;
			int ymax = downPoint.y>upPoint.y?downPoint.y:upPoint.y;
			int xmin = downPoint.x<upPoint.x?downPoint.x:upPoint.x;
			int ymin = downPoint.y<upPoint.y?downPoint.y:upPoint.y;
			CRect rect(xmin,ymax,xmax,ymin);;
			this->map->clipRect = rect;
			this->map->clipMap(rect);
			dc->Rectangle(rect);
			Invalidate();
			CView::OnLButtonUp(nFlags, point);
		}
		else if(isTranslate == TRUE){
			this->isMousePressed = FALSE;
			// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
			CDC *dc = this->GetDC();
			ptEnd = point;
			OnPrepareDC(dc);
			CRect rect;
			GetClientRect(&rect);
			int width = rect.Width();
			int height = rect.Height();

			CPoint p2(ptEnd),p1(ptOrg);
			dc->DPtoLP(&p2);
			dc->DPtoLP(&p1);
			CPoint p =p2-p1;
			dc->DPtoLP(&rect);
			dc->BitBlt(rect.left,rect.top,rect.Width(),rect.Height(),dcMem,rect.left-p.x,rect.top-p.y,SRCCOPY);
			CRect rect1;
			if(p.x>0)
				rect1 = CRect(0,0,ptEnd.x-ptOrg.x,height);
			else
				rect1 = CRect(width+(ptEnd.x-ptOrg.x),0,width,height);
			dc->DPtoLP(&rect1);
			dc->FillSolidRect(rect1,dc->GetBkColor());
			if(p.y>0)
				rect1 = CRect(0,height+(ptEnd.y-ptOrg.y),width,height);
			else
				rect1 = CRect(0,0,width,ptEnd.y-ptOrg.y);
			dc->DPtoLP(&rect1);
			dc->FillSolidRect(rect1,dc->GetBkColor());

		}
	}
	void COOPHSExeView::OnLButtonDown(UINT nFlags, CPoint point)
	{
		if(isZoomIn == TRUE||isClip==TRUE||isTranslate==TRUE){
			this->isMousePressed = TRUE;
			// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
			this->ptEnd = this->ptOrg = point;
			CView::OnLButtonDown(nFlags, point);
		}
	}


	void COOPHSExeView::OnButton32777()
	{
		// TODO: �ڴ���������������
		if(this->isZoomIn == TRUE){
			this->isZoomIn = FALSE;
		}else{
			this->isZoomIn = TRUE;
		}
	}


	void COOPHSExeView::OnButton32779()
	{
		// TODO: �ڴ���������������
		this->wcRect = map->getRect();
		Invalidate();
	}


	void COOPHSExeView::OnUpdateButton32777(CCmdUI *pCmdUI)
	{
		// TODO: �ڴ������������û����洦��������
		pCmdUI->SetCheck(isZoomIn == TRUE);
	}


	void COOPHSExeView::OnUpdateButton32779(CCmdUI *pCmdUI)
	{
		pCmdUI->SetCheck(isReturn == TRUE);
	}


	void COOPHSExeView::OnButton32780()
	{
		if(this->isTranslate == TRUE){
			this->isTranslate = FALSE;
		}else{
			this->isTranslate = TRUE;
		}
	}


	void COOPHSExeView::OnUpdateButton32780(CCmdUI *pCmdUI)
	{
		pCmdUI->SetCheck(isTranslate == TRUE);
	}


	void COOPHSExeView::OnButton32782()
	{
		// TODO: �ڴ���������������
		if(this->isClip == TRUE){
			this->isClip = FALSE;
		}else{
			this->isClip = TRUE;
		}
	}



	void COOPHSExeView::OnUpdateButton32782(CCmdUI *pCmdUI)
	{
		// TODO: �ڴ������������û����洦��������
		pCmdUI->SetCheck(isClip == TRUE);

	}


	void COOPHSExeView::OnSize(UINT nType, int cx, int cy)
	{
		CView::OnSize(nType, cx, cy);
		if(dcMem!=NULL){
			bmp.DeleteObject();
			CRect rect;
			GetClientRect(&rect);
			CDC *pDC = this->GetDC();
			bmp.CreateCompatibleBitmap(pDC,rect.Width(),rect.Height());
			dcMem->SelectObject(&bmp);
		}
	}


	