
// OOPHSExeView.cpp : COOPHSExeView 类的实现
//

#include "stdafx.h"
#include <afxpriv.h>
#include <math.h>
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
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
		// 标准打印命令
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

	// COOPHSExeView 构造/析构

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
			dcMem->DeleteDC();	//回收对应图片
			bmp.DeleteObject();	//解除图片与CDC*间的绑定
			delete dcMem;
		}
	}

	BOOL COOPHSExeView::PreCreateWindow(CREATESTRUCT& cs)
	{
		// TODO: 在此处通过修改
		//  CREATESTRUCT cs 来修改窗口类或样式

		return CView::PreCreateWindow(cs);
	}

	// COOPHSExeView 绘制

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
			dcMem = new CDC();	//新建DC
			dcMem->CreateCompatibleDC(pDC);	//兼容于pDC
			bmp.CreateCompatibleBitmap(pDC,rect.Width(),rect.Height());
			dcMem->SelectObject(&bmp);
		}
		pDC->DPtoLP(&rect);
		OnPrepareDC(dcMem);
		dcMem->FillSolidRect(rect,pDC->GetBkColor());
		map->draw(dcMem);
		pDC->BitBlt(rect.left,rect.top,rect.Width(),rect.Height(),dcMem,rect.left,rect.top,SRCCOPY);

	}


	// COOPHSExeView 打印

	BOOL COOPHSExeView::OnPreparePrinting(CPrintInfo* pInfo)
	{
		// 默认准备
		return DoPreparePrinting(pInfo);
	}

	void COOPHSExeView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
	{
		// TODO: 添加额外的打印前进行的初始化过程
	}

	void COOPHSExeView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
	{
		// TODO: 添加打印后进行的清理过程
	}


	// COOPHSExeView 诊断

#ifdef _DEBUG
	void COOPHSExeView::AssertValid() const
	{
		CView::AssertValid();
	}

	void COOPHSExeView::Dump(CDumpContext& dc) const
	{
		CView::Dump(dc);
	}

	COOPHSExeDoc* COOPHSExeView::GetDocument() const // 非调试版本是内联的
	{
		ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COOPHSExeDoc)));
		return (COOPHSExeDoc*)m_pDocument;
	}
#endif //_DEBUG


	// COOPHSExeView 消息处理程序
	/*void COOPHSExeView::OnFileOpen(){

	}*/
	void COOPHSExeView::OnFileOpen()
	{
		// TODO: 在此添加命令处理程序代码
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
		if(!fileName.CompareNoCase(CString("C:\\大二上\\c++实习\\china1.dat"))){
			readChina(fp);
		}
		else if(!fileName.CompareNoCase(CString("C:\\大二上\\c++实习\\wuhan.txt"))){
			readWuhan(fp);
		}
		else if(!fileName.CompareNoCase(CString("D:\\大二下\\计算机图形学\\chnFillTest.txt"))){
			readCHN(fp);
		}
		else if(!fileName.CompareNoCase(CString("D:\\大二下\\计算机图形学\\clipData.txt"))){
			readClip(fp);
		}
		else if(!fileName.CompareNoCase(CString("D:\\大二下\\计算机图形学\\BOUNT_line.mif"))){
			readProj(fp);
		}
		else if(!fileName.CompareNoCase(CString("D:\\大二下\\计算机图形学\\diquJie_polyline.mif"))){
			readProj(fp);
		}

		Invalidate();
	}

	void COOPHSExeView::readProj(FILE *fp){
		CGeoLayer *layer = new CGeoLayer();
		map->addLayer(layer);
		CMapProjection *mapProj = new CMapProjection();
		map->mapProj = mapProj;
		/*-----------读取范围------------*/
		double left,top,right,bottom;
		char *str = new char[];
		char tag;
		fscanf(fp,"%s %s",str,str);
		fscanf(fp,"%s %s",str,str);
		fscanf(fp,"%s %s %s %s %s %c%lf%c%lf%c %c%lf%c%lf",str,str,str,str,str,&tag,&left,&tag,&bottom,&tag,&tag,&right,&tag,&top);
		map->setRect(CRect(left*pow(10,6),top*pow(10,6),right*pow(10,6),bottom*pow(10,6)));
		this->wcRect = map->getRect();
		mapProj->wcRect = map->getRect();
		/*-----------跳过几行-------------*/
		while(strcmp(str,"LINE") != 0 && strcmp(str,"PLINE") != 0)
			fscanf(fp,"%s",str);
		/*-----------循环读取polyline-----*/
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
	
	// 进行墨卡托投影
	void COOPHSExeView::makeProj(CMapProjection *mapProj)
	{
		// 设置map区域
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
		/*--------------------读取范围---------------------*/
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
			//读取多边形个数
			fscanf_s(fp,"%d",&n);
			for(int i=0;i<n;i++){
				fscanf_s(fp,"%d",&m);
				for(int j=0;j<m;j++){
					fscanf_s(fp,"%d%d",&x,&y);
					if(i==0)
						((CGeoPolygon *)obj)->addPoint(CPoint(x,y));
				}
			}
			// 读取内部点
			fscanf_s(fp,"%d%d",&x,&y);
			((CGeoPolygon *)obj)->seeds.Add(CPoint(x,y));
			// 读取颜色
			fscanf_s(fp,"%d",&color);
			convertColor(color,obj);
		}
		fclose(fp);
	}

	void COOPHSExeView::convertColor(int color,CGeoObject *obj)//16进制颜色值
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
		/*--------------------读取范围---------------------*/
		int left,top,right,bottom;
		fscanf_s(fp,"%d,%d%d,%d",&left,&top,&right,&bottom);
		map->setRect(CRect(left,top,right,bottom));
		this->wcRect = map->getRect();
		/*-------------------------------------------------*/
		/*--------------------读取层数---------------------*/
		int layerNum;
		fscanf_s(fp,"%d",&layerNum);
		/*--------------------读取每一层-------------------*/
		for(int i=0;i<layerNum;i++){
			CGeoLayer *layer = new CGeoLayer();
			map->addLayer(layer);
			//读取层名大小
			int layerSize;
			fscanf_s(fp,"%d",&layerSize);
			//读取层名
			char *layerName = new char[layerSize+1];
			char tag;
			fread( &tag , sizeof(char) , 1 , fp ) ;  
			fread( layerName , sizeof(char) , layerSize+1 , fp ) ;  
			layerName[layerSize] = '\0';
			layer->setName(CString(layerName));
			delete []layerName;
			//读取目标数目
			int number;
			fscanf_s(fp,"%d",&number);
			CGeoObject *obj = NULL;
			//判断目标类型并读取每一个目标
			for(int i=0;i<number;i++){
				//获取目标类型
				int type;
				fscanf_s(fp,"%d",&type);
				/*switch(type){
				case 1:addPolylines();break;
				case 2:addPolygons();break;
				case 4:addAnnotations();break;
				}*/
				if(type==1){
					//每一条线上的点
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
					//每一个面上的点
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
		// TODO: 在此添加专用代码和/或调用基类
		// TODO: Add your specialized code here and/or call the base class
		//添加一个bool变量，控制是否是最新需要变换的这个数据加载，如果没有加载，则不需要坐标变换

		if( !this->isMaploaded ) 
			return;
		CSize windowsize; 
		CSize logicsize;
		CPoint pt;	
		CRect rectD;

		this->GetClientRect(&rectD);//取得客户区矩形区域大小
		windowsize = rectD.Size();
		pt = rectD.CenterPoint();//取得客户区矩形区域中心点坐标

		pDC->SetMapMode(MM_ISOTROPIC); //设置指定设备环境的映射方式
		pDC->SetViewportExt(windowsize);  //设定视口尺寸
		pDC->SetViewportOrg(pt); //设置视口中心为坐标系原点

		logicsize = wcRect.Size();  //设定窗口对应尺寸
		double ratio = -windowsize.cx*1.0/windowsize.cy;
		logicsize.cx = logicsize.cy*ratio;
		//CRect rect(-932833,1937773,2109383,-572515);
		pt = wcRect.CenterPoint(); //设置窗口中心为对应原点
		//size = rect.Size();
		//pt = rect.CenterPoint();
		pDC->SetWindowExt(logicsize);   //设置窗口长宽
		pDC->SetWindowOrg(pt);	//设置窗口原点
		CView::OnPrepareDC(pDC, pInfo);
	}

	//读取颜色文件
	void COOPHSExeView::readOPT(){
		FILE *fp;
		fopen_s(&fp,"C:\\大二上\\c++实习\\china1.opt","r");
		/*--------------------读取层数---------------------*/
		int layerNum;
		fscanf_s(fp,"%d",&layerNum);
		for(int i=0;i<layerNum;i++){
			//读取层名
			char name[20];
			char tag;
			int j = 0;
			//跳过第一个\n
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
			//根据层名获得某一层
			CGeoLayer* layer = map->getLayerByName(CString(layerName));
			//读取线型
			int lineType;
			fscanf_s(fp,"%d",&lineType);
			//读取线宽
			double lineWidth = 0;
			if(lineType == 1){
				fscanf_s(fp,"%lf",&lineWidth);
			}
			//读取线色
			int r=0,g=0,b=0;
			if(lineType==1&&lineWidth!=0){
				fscanf_s(fp,"%d,%d,%d",&r,&g,&b);
			}
			//读取面型
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
		CString Infilepath = CString("C:\\大二上\\c++实习\\chnCity.xls");
		std::string path;
		path = CT2A(Infilepath);
		//char* path = const_cast<char*>(line1.c_str()); //sting 转 char*
		Excel excl;
		bool bInit = excl.initExcel();

		//打开excel文件
		if (!excl.open(path.c_str()))
		{
			AfxMessageBox(_T("excel文件打开出错!"));
		}

		CString strSheetName = excl.getSheetName(1);//获取第一个sheet名  
		bool bLoad = excl.loadSheet(strSheetName);//装载sheet  
		int nRow = excl.getRowCount();//获取sheet中行数  
		int nCol = excl.getColumnCount();//获取sheet中列数  
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
				cell = excl.getCellString(i, j);  ////获取一个单元格数据
				// cells = CT2A(cell);      //将获取的单元格转换为string类型数据
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
		// TODO: 在此添加消息处理程序代码和/或调用默认值
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
			// TODO: 在此添加消息处理程序代码和/或调用默认值
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

			// TODO: 在此添加消息处理程序代码和/或调用默认值
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
			// TODO: 在此添加消息处理程序代码和/或调用默认值
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
			// TODO: 在此添加消息处理程序代码和/或调用默认值
			this->ptEnd = this->ptOrg = point;
			CView::OnLButtonDown(nFlags, point);
		}
	}


	void COOPHSExeView::OnButton32777()
	{
		// TODO: 在此添加命令处理程序代码
		if(this->isZoomIn == TRUE){
			this->isZoomIn = FALSE;
		}else{
			this->isZoomIn = TRUE;
		}
	}


	void COOPHSExeView::OnButton32779()
	{
		// TODO: 在此添加命令处理程序代码
		this->wcRect = map->getRect();
		Invalidate();
	}


	void COOPHSExeView::OnUpdateButton32777(CCmdUI *pCmdUI)
	{
		// TODO: 在此添加命令更新用户界面处理程序代码
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
		// TODO: 在此添加命令处理程序代码
		if(this->isClip == TRUE){
			this->isClip = FALSE;
		}else{
			this->isClip = TRUE;
		}
	}



	void COOPHSExeView::OnUpdateButton32782(CCmdUI *pCmdUI)
	{
		// TODO: 在此添加命令更新用户界面处理程序代码
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


	