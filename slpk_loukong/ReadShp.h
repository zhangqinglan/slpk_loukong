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
	vector<OGRPoint> readShp(string shppath, vector<OGRPoint> p);//根据点集及输入的面获取在面中的点集
	vector<OGRPoint> selectnodes(string shppath, vector<DefPoint> p);//根据点集及输入的面获取在面中的点集
	//bool ReadDXF(string filePath, vector<vector<OGRPoint>>& vertexPoint);
	bool slectvertex(string shppath, OGRPoint p);//判断顶点是否在压平范围内
	bool moreslectvertex(string shppath, OGRPoint p);//判断顶点是否在压平范围内,这里的shp文件为多个多边形
};

