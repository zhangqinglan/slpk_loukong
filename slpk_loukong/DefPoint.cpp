#include "DefPoint.h"

DefPoint::DefPoint(double X, double Y, double Z, double HX, double HY, double HZ, int ID)
{
	this->x = X;
	this->y = Y;
	this->z = Z;
	this->halfx = HX;
	this->halfy = HY;
	this->halfz = HZ;
	this->id = ID;
}
void DefPoint::createploygonshp()
{
	vector<double> x_all;
	vector<double> y_all;
	x_all.push_back(x - halfx);
	y_all.push_back(y - halfy);
	x_all.push_back(x - halfx);
	y_all.push_back(y + halfy);
	x_all.push_back(x + halfx);
	y_all.push_back(y + halfy);
	x_all.push_back(x + halfx);
	y_all.push_back(y - halfy);
	GDALAllRegister();
	OGRRegisterAll();
	const char *xjDriverName = "ESRI Shapefile";
	GDALDriver *xjDriver = OGRSFDriverRegistrar::GetRegistrar()->GetDriverByName(xjDriverName);
	if (xjDriver == NULL)
	{
		cout << "error of GDAL: Driver not available!!!" << endl;
		return;
	}
	string xjSavePath = id + ".shp";
	GDALDataset *xjDataset = xjDriver->Create(xjSavePath.c_str(), 0, 0, 0, GDT_Unknown, NULL);
	if (xjDataset == NULL)
	{
		cout << "error of GDAL: Creation of output file failed!!!" << endl;
		return;
	}

	//空间参考
	//OGRSpatialReference sf = CreateProjectionReference(120);

	OGRLayer *xjLayer = xjDataset->CreateLayer("polygon1", NULL, wkbPolygonZM, NULL);
	if (xjLayer == NULL)
	{
		cout << "error of GDAL: Layer creation failed!!!" << endl;
		return;
	}

	//创建属性字段
	OGRFieldDefn fieldID("ID", OFTInteger);
	fieldID.SetWidth(32);
	xjLayer->CreateField(&fieldID);
	OGRFieldDefn fieldNAME("NAME", OFTString);
	fieldNAME.SetWidth(32);
	xjLayer->CreateField(&fieldNAME);
	OGRFieldDefn fieldAREA("AREA", OFTReal);
	fieldAREA.SetPrecision(16);
	xjLayer->CreateField(&fieldAREA);

	//创建要素
	for (int i = 0; i < 1; i++)//这里一个节点只生成一个矩形
	{
		//创建要素
		OGRFeature *xjFeature = OGRFeature::CreateFeature(xjLayer->GetLayerDefn());
		//矢量面要素的边界是闭合环
		OGRLinearRing xjRing;
		//QList<xjPoint> list = xjListPoint.at(i);
		for (int j = 0; j < x_all.size(); j++)
		{
			//xjRing.addPoint(list.at(j).x, list.at(j).y, list.at(j).z);
			xjRing.addPoint(x_all[j], y_all[j]);

		}
		xjRing.closeRings();//首尾点重合形成闭合环

		//图层添加要素
		OGRPolygon xjPolygon;
		xjPolygon.addRing(&xjRing);
		xjFeature->SetGeometry(&xjPolygon);

		//设置属性
		xjFeature->SetFID(i);
		xjFeature->SetField(0, i);
		std::string pname = "name_" + to_string(i);
		xjFeature->SetField(1, pname.c_str());
		xjFeature->SetField("AREA", halfx*halfy * 4);

		//判断
		if (xjLayer->CreateFeature(xjFeature) != OGRERR_NONE)
		{
			cout << "error of GDAL: Failed to create feature in shapefile!!!" << endl;
			continue;
		}
		OGRFeature::DestroyFeature(xjFeature);
	}
	GDALClose(xjDataset);
	xjDataset = nullptr;
}
Geometry* DefPoint::createploygon()
{

	vector<double> x_all;
	vector<double> y_all;
	vector<double> z_all;
	x_all.push_back(x - halfx);
	y_all.push_back(y - halfy);
	z_all.push_back(z);
	x_all.push_back(x - halfx);
	y_all.push_back(y + halfy);
	z_all.push_back(z);
	x_all.push_back(x + halfx);
	y_all.push_back(y + halfy);
	z_all.push_back(z);
	x_all.push_back(x + halfx);
	y_all.push_back(y - halfy);
	z_all.push_back(z);
	x_all.push_back(x - halfx);
	y_all.push_back(y - halfy);
	z_all.push_back(z);
	//创建要素
	//OGRPolygon xjPolygon;
	OGRwkbGeometryType targetGeometryType;
	targetGeometryType = OGRwkbGeometryType::wkbPolygon;
	OGRPolygon* pOGRPolygon = (OGRPolygon*)OGRGeometryFactory::createGeometry(targetGeometryType);
	//OGRGeometry *xjPolygon;
	//OGRGeometry xGeometry;
	for (int i = 0; i < 1; i++)//这里一个节点只生成一个矩形
	{

		typedef Coordinate PT;
		GeometryFactory::unique_ptr factory;
		PrecisionModel *pm = new PrecisionModel(1.0, 0, 0);
		factory = GeometryFactory::create(pm, -1);

		CoordinateArraySequenceFactory csf; //构建第一个矩形p1
		CoordinateSequence* cs1 = csf.create(5, 3);//五个3维点，第三维度z始终为0
		for (int j = 0; j < x_all.size(); j++)
		{
			cs1->setAt(PT(x_all[j], y_all[j], z_all[j]), j);
		}
		LinearRing* ring1 = factory->createLinearRing(cs1); //点构成线
		Geometry* p1 = factory->createPolygon(ring1, NULL); //线构成面
		return p1;
	}

}

DefPoint::~DefPoint()
{

}