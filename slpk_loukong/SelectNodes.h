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
//�ӽڵ�ҳ�����ļ��л�ȡ���нڵ������µĵ㼯�����жϵ��Ƿ���ѹƽ��Χ�ڣ�ѡ����ڷ�Χ�ڵĽڵ�
class SelectNodes
{
public:
	vector<string> visitFiles(string path);
	vector<OGRPoint> getallnodes();
	vector<DefPoint> getall();

};

