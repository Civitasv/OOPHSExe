#pragma once
class CGeoObject
{
private:
	//目标名称
	CString name;
	//目标id
	int id;
	//外界矩形
	CRect crRect;
protected:
	//目标类型,1,2,3,4可以分别表示点、线、面、文字等
	int type;
public:
	int lineType; //线型
	int areaType; //面型
	int lineWidth; //线宽
	int r,g,b;	//线色
	int r2,g2,b2;	//面填充
	CGeoObject(void);
	virtual ~CGeoObject(void);
	
	void setName(CString name);
	CString getName();

	void setId(int id);
	int getId();

	virtual void draw(CDC *pDC);
	void setRect(CRect rect);
	/*void setRect(int x,int y,int width,int height);*/
	CRect getRect();
	
	void setType(int type);
	int getType();
	virtual void clipObj(CRect wcRect1);
};

