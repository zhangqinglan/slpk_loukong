#pragma once
#include<string>
#include <iostream>
#include<stdio.h>
#include<fstream>
#include<sstream>
#include <ogrsf_frmts/ogrsf_frmts.h>
#include "ReadShp.h"
#include "ZipHelper.h"
using namespace std;
class BinModify
{
public:
	BinModify();
	void modifynodebin(string shppath, OGRPoint slectnode, double elevation);//����ѹƽ��Χ�ڵĽڵ�ID�����ݽڵ�ID��ȡbin�ļ������ĵ������
	void dighole(string shppath, OGRPoint slectnode, double elevation);//�ڿ�
	void transparent(string shppath, OGRPoint slectnode, double transparency);//ģ��͸��
	void writebin(string outbin);
	~BinModify();
};

