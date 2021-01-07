#pragma once
#include <string>
#include <iostream>
#include <gdal.h>
#include <gdal_priv.h>
#include <ogrsf_frmts/ogrsf_frmts.h>
#include <algorithm>
#include "DefPoint.h"

using namespace std;
class ReadShp
{
public:
	//string m_ShpFile_fp;
	ReadShp();
	vector<OGRPoint> readShp(string shppath, vector<OGRPoint> p);//���ݵ㼯����������ȡ�����еĵ㼯
	vector<OGRPoint> selectnodes(string shppath, vector<DefPoint> p);//���ݵ㼯����������ȡ�����еĵ㼯
	//bool ReadDXF(string filePath, vector<vector<OGRPoint>>& vertexPoint);
	bool slectvertex(string shppath, OGRPoint p);//�ж϶����Ƿ���ѹƽ��Χ��
	bool moreslectvertex(string shppath, OGRPoint p);//�ж϶����Ƿ���ѹƽ��Χ��,�����shp�ļ�Ϊ��������
};

