#pragma once
#include <iostream>
#include <gdal.h>
#include <gdal_priv.h>
#include <ogrsf_frmts/ogrsf_frmts.h>
#include "cpl_conv.h"
#include "cpl_json.h"
#include "ogr_core.h"
#include "ogr_spatialref.h"
#include <vector>
#include "geos.h"


#include <memory>
using namespace std;
class  DefPoint
{
public:

	double x, y, z, halfx, halfy, halfz;
	int id;
	DefPoint(double X, double Y, double Z, double HX, double HY, double HZ, int ID);
	//根据点信息构建面
	void createploygonshp();
	Geometry* createploygon();
	~DefPoint();
};

