#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <io.h>
#include "ZipHelper.h"
#include "json.h"
#include <gdal.h>
#include <ogrsf_frmts/ogrsf_frmts.h>
#include "DefPoint.h"
using namespace std;
//从节点页索引文件中获取所有节点生成新的点集，并判断点是否在压平范围内，选择出在范围内的节点
class SelectNodes
{
public:
	vector<string> visitFiles(string path);
	vector<OGRPoint> getallnodes();
	vector<DefPoint> getall();

};

