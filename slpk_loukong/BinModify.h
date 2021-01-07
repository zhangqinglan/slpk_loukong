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
	void modifynodebin(string shppath, OGRPoint slectnode, double elevation);//传入压平范围内的节点ID，根据节点ID获取bin文件和中心点的坐标
	void dighole(string shppath, OGRPoint slectnode, double elevation);//挖坑
	void transparent(string shppath, OGRPoint slectnode, double transparency);//模型透明
	void writebin(string outbin);
	~BinModify();
};

