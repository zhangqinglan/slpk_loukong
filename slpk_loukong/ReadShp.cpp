#include "ReadShp.h"



ReadShp::ReadShp()
{

}
vector<OGRPoint> ReadShp::readShp(string shppath, vector<OGRPoint> p)
{
	vector<OGRPoint> slectnodes;//�����ѹƽ��Χ�ڵĽڵ�
	string filename = shppath;
	GDALAllRegister();
	GDALDataset   *poDS;
	CPLSetConfigOption("GDAL_FILENAME_IS_UTF8", "NO");  //���������������
	CPLSetConfigOption("SHAPE_ENCODING", "");
	//��ȡshp�ļ�
	poDS = (GDALDataset*)GDALOpenEx(filename.c_str(), GDAL_OF_VECTOR, NULL, NULL, NULL);

	if (poDS == NULL)
	{
		cout << "Open failed.\n%s" << endl;
		//return 0;
	}

	OGRLayer  *poLayer;
	poLayer = poDS->GetLayer(0); //��ȡ��
	OGRFeature *poFeature;

	poLayer->ResetReading();
	int i = 0;
	while ((poFeature = poLayer->GetNextFeature()) != NULL)
	{
		double area = 0;
		OGRGeometry *laugeometry;
		laugeometry = poFeature->GetGeometryRef();
		if (laugeometry != NULL)
		{
			OGRwkbGeometryType laugeotype = laugeometry->getGeometryType();
			if (laugeotype == wkbPolygon)
			{
				OGRPolygon* pPolygon = (OGRPolygon*)laugeometry;
				cout << "multipolygon" << endl;
				OGRMultiPolygon *laumltupolygon = (OGRMultiPolygon *)laugeometry;
				OGRPolygon *laupolygon1 = NULL;
				int nCross = 0;
				for (int k = 0; k < p.size(); k++)
				{
					for (int i = 0; i < laumltupolygon->getNumGeometries(); i++)
					{
						//laupolygon1 = (OGRPolygon*)laumltupolygon->getGeometryRef(i);
						OGRLinearRing *laulr = (OGRLinearRing*)pPolygon->getExteriorRing();
						int pointcount = laulr->getNumPoints();
						//�������

						for (int j = 0; j < pointcount; j++)
						{
							OGRPoint p1;
							p1.setX(laulr->getX(j));
							p1.setY(laulr->getY(j));
							OGRPoint p2;
							p2.setX(laulr->getX((j + 1) % pointcount));
							p2.setY(laulr->getY((j + 1) % pointcount));
							if (p1.getY() == p2.getY())
								continue;
							if (p[k].getY() < min(p1.getY(), p2.getY()))
								continue;
							if (p[k].getY() >= max(p1.getY(), p2.getY()))
								continue;
							// �󽻵��x����
							double x = (double)(p[k].getY() - p1.getY()) * (double)(p2.getX() - p1.getX()) / (double)(p2.getY() - p1.getY()) + p1.getX();
							// ֻͳ��p1p2��p�������ߵĽ���  
							if (x > p[k].getX())
							{
								nCross++;
							}
							if (nCross % 2 == 1)
							{
								slectnodes.push_back(p[k]);
							}


						}
					}

				}
			}

		}
	}
	return slectnodes;
}
vector<OGRPoint> ReadShp::selectnodes(string shppath, vector<DefPoint> p)
{
	vector<OGRPoint> slectnodes;//�����ѹƽ��Χ�ڵĽڵ�
	string filename = shppath;
	GDALAllRegister();
	GDALDataset   *poDS;
	CPLSetConfigOption("GDAL_FILENAME_IS_UTF8", "NO");  //���������������
	CPLSetConfigOption("SHAPE_ENCODING", "");
	//��ȡshp�ļ�
	poDS = (GDALDataset*)GDALOpenEx(filename.c_str(), GDAL_OF_VECTOR, NULL, NULL, NULL);

	if (poDS == NULL)
	{
		cout << "Open failed.\n%s" << endl;
		//return 0;
	}

	OGRLayer  *poLayer;
	poLayer = poDS->GetLayer(0); //��ȡ��
	OGRFeature *poFeature;

	poLayer->ResetReading();
	int i = 0;
	while ((poFeature = poLayer->GetNextFeature()) != NULL)
	{
		double area = 0;
		OGRGeometry *laugeometry;
		laugeometry = poFeature->GetGeometryRef();
		if (laugeometry != NULL)
		{
			OGRwkbGeometryType laugeotype = laugeometry->getGeometryType();
			if (laugeotype == wkbPolygon)
			{
				OGRMultiPolygon *laumltupolygon = (OGRMultiPolygon *)laugeometry;
				int nCross = 0;
				geos::io::WKTReader wkt_read;
				char * buff = nullptr;
				laugeometry->exportToWkt(&buff);
				wkt_read.read(buff);
				Geometry* geoms = wkt_read.read(buff);
				for (int k = 0; k < p.size(); k++)
				{


					Geometry* mpoly2 = p[k].createploygon();
					for (int i = 0; i < laumltupolygon->getNumGeometries(); i++)
					{

						Geometry *intersection = geoms->intersection(mpoly2);
						//cout << "Intersection: " << intersection->toString() << endl;
						if (intersection->toString() != "GEOMETRYCOLLECTION EMPTY")//����ڵ������ѹƽ��Χ�ཻ��ѡȡ�ýڵ�
						{
							OGRPoint node;
							node.setX(p[k].x);
							node.setY(p[k].y);
							node.setZ(p[k].z);
							node.setM(p[k].id);
							slectnodes.push_back(node);
						}
					}

				}
			}

		}
	}
	return slectnodes;
}


bool ReadShp::slectvertex(string shppath, OGRPoint p)
{
	//vector<OGRPoint> slectnodes;//�����ѹƽ��Χ�ڵĽڵ�
	string filename = shppath;
	GDALAllRegister();
	GDALDataset   *poDS;
	CPLSetConfigOption("GDAL_FILENAME_IS_UTF8", "NO");  //���������������
	CPLSetConfigOption("SHAPE_ENCODING", "");
	//��ȡshp�ļ�
	poDS = (GDALDataset*)GDALOpenEx(filename.c_str(), GDAL_OF_VECTOR, NULL, NULL, NULL);

	if (poDS == NULL)
	{
		cout << "Open failed.\n%s" << endl;
		//return;
	}

	OGRLayer  *poLayer;
	poLayer = poDS->GetLayer(0); //��ȡ��
	OGRFeature *poFeature;

	poLayer->ResetReading();
	int i = 0;
	while ((poFeature = poLayer->GetNextFeature()) != NULL)
	{
		double area = 0;
		OGRGeometry *laugeometry;
		laugeometry = poFeature->GetGeometryRef();
		if (laugeometry != NULL)
		{
			OGRwkbGeometryType laugeotype = laugeometry->getGeometryType();
			if (laugeotype == wkbPolygon)
			{
				OGRPolygon* pPolygon = (OGRPolygon*)laugeometry;
				//OGRPolygon* pPolygon = (OGRPolygon*)OGRGeometryFactory::createGeometry(wkbPolygon);//���ں��������ж����
				//int pointcount = boundary->getNumPoints();
				//OGRLinearRing* pRing = (OGRLinearRing*)OGRGeometryFactory::createGeometry(wkbLinearRing);//���ں��������ж���α߽�
				cout << "multipolygon" << endl;
				//OGRMultiPolygon *laumltupolygon = (OGRMultiPolygon *)laugeometry;
				//OGRPolygon *laupolygon1 = NULL;
				int nCross = 0;

				for (int i = 0; i < 1; i++)
				{
					//laupolygon1 = (OGRPolygon*)laumltupolygon->getGeometryRef(i);
					OGRLinearRing *laulr = (OGRLinearRing*)pPolygon->getExteriorRing();
					int pointcount = laulr->getNumPoints();
					//OGRLinearRing *laulr = (OGRLinearRing*)laupolygon1->getInteriorRing;
					//�������

					for (int j = 0; j < pointcount; j++)
					{
						OGRPoint p1;
						p1.setX(laulr->getX(j));
						p1.setY(laulr->getY(j));
						OGRPoint p2;
						p2.setX(laulr->getX((j + 1) % pointcount));
						p2.setY(laulr->getY((j + 1) % pointcount));
						if (p1.getY() == p2.getY())
							continue;
						if (p.getY() < min(p1.getY(), p2.getY()))
							continue;
						if (p.getY() >= max(p1.getY(), p2.getY()))
							continue;
						// �󽻵��x����
						double x = (double)(p.getY() - p1.getY()) * (double)(p2.getX() - p1.getX()) / (double)(p2.getY() - p1.getY()) + p1.getX();
						// ֻͳ��p1p2��p�������ߵĽ���  
						if (x > p.getX())
						{
							nCross++;
						}
						return (nCross % 2 == 1);
					}
				}

			}

		}
	}
}

bool ReadShp::moreslectvertex(string shppath, OGRPoint p)
{
	//vector<OGRPoint> slectnodes;//�����ѹƽ��Χ�ڵĽڵ�
	string filename = shppath;
	GDALAllRegister();
	GDALDataset   *poDS;
	CPLSetConfigOption("GDAL_FILENAME_IS_UTF8", "NO");  //���������������
	CPLSetConfigOption("SHAPE_ENCODING", "");
	//��ȡshp�ļ�
	poDS = (GDALDataset*)GDALOpenEx(filename.c_str(), GDAL_OF_VECTOR, NULL, NULL, NULL);

	if (poDS == NULL)
	{
		cout << "Open failed.\n%s" << endl;
		//return;
	}

	OGRLayer  *poLayer;
	poLayer = poDS->GetLayer(0); //��ȡ��
	OGRFeature *poFeature;

	poLayer->ResetReading();
	int i = 0;
	while ((poFeature = poLayer->GetNextFeature()) != NULL)
	{
		double area = 0;
		OGRGeometry *laugeometry;
		laugeometry = poFeature->GetGeometryRef();
		if (laugeometry != NULL)
		{
			OGRwkbGeometryType laugeotype = laugeometry->getGeometryType();
			if (laugeotype == wkbPolygon)
			{
				OGRPolygon* pPolygon = (OGRPolygon*)laugeometry;
				cout << "multipolygon" << endl;
				OGRMultiPolygon *laumltupolygon = (OGRMultiPolygon *)laugeometry;
				//OGRPolygon *laupolygon1 = NULL;
				int nCross = 0;
				int count = laumltupolygon->getNumGeometries();

				//�д���һ���Ľ���2020.12.28��
				for (int i = 0; i < laumltupolygon->getNumGeometries(); i++)
				{
					//laupolygon1 = (OGRPolygon*)laumltupolygon->getGeometryRef(i);
					OGRLinearRing *laulr = (OGRLinearRing*)pPolygon->getExteriorRing();
					//OGRLinearRing *laulr = (OGRLinearRing*)laupolygon1->getExteriorRing();
					int pointcount = laulr->getNumPoints();
					//OGRLinearRing *laulr = (OGRLinearRing*)laupolygon1->getInteriorRing;
					//�������

					for (int j = 0; j < pointcount; j++)
					{
						OGRPoint p1;
						p1.setX(laulr->getX(j));
						p1.setY(laulr->getY(j));
						OGRPoint p2;
						p2.setX(laulr->getX((j + 1) % pointcount));
						p2.setY(laulr->getY((j + 1) % pointcount));
						if (p1.getY() == p2.getY())
							continue;
						if (p.getY() < min(p1.getY(), p2.getY()))
							continue;
						if (p.getY() >= max(p1.getY(), p2.getY()))
							continue;
						// �󽻵��x����
						double x = (double)(p.getY() - p1.getY()) * (double)(p2.getX() - p1.getX()) / (double)(p2.getY() - p1.getY()) + p1.getX();
						// ֻͳ��p1p2��p�������ߵĽ���  
						if (x > p.getX())
						{
							nCross++;
						}
						return (nCross % 2 == 1);
					}
				}

			}
			else if (laugeotype == wkbMultiPolygon)
			{
				OGRMultiPolygon *laumltupolygon = (OGRMultiPolygon *)laugeometry;
				OGRPolygon *laupolygon1 = NULL;
				OGRPolygon *rdPolygon = NULL;
				int nCross = 0;
				int count = laumltupolygon->getNumGeometries();
				for (int i = 0; i < laumltupolygon->getNumGeometries(); i++)
				{
					laupolygon1 = (OGRPolygon*)laumltupolygon->getGeometryRef(i);
					//rdPolygon = (OGRPolygon *)rdPolygon->Union(laupolygon1);
					//OGRLinearRing *laulr = (OGRLinearRing*)pPolygon->getExteriorRing();
					OGRLinearRing *laulr = (OGRLinearRing*)laupolygon1->getExteriorRing();
					int pointcount = laulr->getNumPoints();
					//OGRLinearRing *laulr = (OGRLinearRing*)laupolygon1->getInteriorRing;
					//�������

					for (int j = 0; j < pointcount; j++)
					{
						OGRPoint p1;
						p1.setX(laulr->getX(j));
						p1.setY(laulr->getY(j));
						OGRPoint p2;
						p2.setX(laulr->getX((j + 1) % pointcount));
						p2.setY(laulr->getY((j + 1) % pointcount));
						if (p1.getY() == p2.getY())
							continue;
						if (p.getY() < min(p1.getY(), p2.getY()))
							continue;
						if (p.getY() >= max(p1.getY(), p2.getY()))
							continue;
						// �󽻵��x����
						double x = (double)(p.getY() - p1.getY()) * (double)(p2.getX() - p1.getX()) / (double)(p2.getY() - p1.getY()) + p1.getX();
						// ֻͳ��p1p2��p�������ߵĽ���  
						if (x > p.getX())
						{
							nCross++;
						}
						return (nCross % 2 == 1);
					}
				}
			}

		}
	}
}
