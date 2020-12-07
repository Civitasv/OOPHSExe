#pragma once
class CGeoObject
{
private:
	//Ŀ������
	CString name;
	//Ŀ��id
	int id;
	//������
	CRect crRect;
protected:
	//Ŀ������,1,2,3,4���Էֱ��ʾ�㡢�ߡ��桢���ֵ�
	int type;
public:
	int lineType; //����
	int areaType; //����
	int lineWidth; //�߿�
	int r,g,b;	//��ɫ
	int r2,g2,b2;	//�����
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

