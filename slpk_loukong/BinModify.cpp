#include "BinModify.h"
BinModify::BinModify()
{
}
//ѹƽ
void BinModify::modifynodebin(string shppath, OGRPoint slectnode, double elevation)
{
	//���ȸ��ݴ����ѹƽ��Χ�ڵĽڵ㣬��ȡ�ڵ�ID
	int nodeid = slectnode.getM();
	string inbin = "process/nodes/" + to_string(nodeid) + "/geometries/0.bin.gz";
	string uncombin = "process/nodes/" + to_string(nodeid) + "/geometries/0";
	string uncombin1 = "process/nodes/" + to_string(nodeid) + "/geometries/0/0.bin";
	//��ѹbinѹ����
	ZipHelper uncompessbin;
	uncompessbin.exeUnCompress(uncombin, inbin);
	ifstream fin;
	fin.open(uncombin1, ios::binary);
	if (!fin)
	{
		cout << "open error!" << endl;
		return;
	}
	string path = inbin.substr(0, inbin.find_last_of('/'));
	string outbin = path + "/0.bin";
	std::ofstream outF(outbin, std::ios::binary);
	int vertexIndexcount[1 * 1];
	int vertexIndexcountdef[1 * 1];
	fin.read((char*)vertexIndexcount, sizeof(int) * (1 * 1));//��bin�ж�ȡ������������
	//std::cout << 1 << ": " << vertexIndexcount[0] << std::endl;
	int w_vertexIndexcount = vertexIndexcount[0];
	outF.write(reinterpret_cast<char*>(&w_vertexIndexcount), sizeof(w_vertexIndexcount));//��������������д����bin��
	fin.read((char*)vertexIndexcountdef, sizeof(int) * (1 * 1));
	//std::cout << 2 << ": " << vertexIndexcountdef[0] << std::endl;
	int w_vertexIndexcountdef = vertexIndexcountdef[0];
	outF.write(reinterpret_cast<char*>(&w_vertexIndexcountdef), sizeof(w_vertexIndexcountdef));//������Ķ�����������д����bin��
	int vertexcount = vertexIndexcount[0];
	//���ݶ���������������������ȡbin�ж����������꣬�ж����Ƿ���ѹƽ��Χ�ڣ����޸����±��浽�µ�bin�ļ���
	for (int i = 0; i < vertexIndexcount[0]; i++)
	{
		float_t Position[1 * 3];
		fin.read((char*)Position, sizeof(float_t) * (1 * 3));
		//ɾ���ж϶����Ƿ���ѹƽ��Χ��
		//OGRPoint vertex;
		//vertex.setX(Position[0] + slectnode.getX());
		//vertex.setY(Position[1] + slectnode.getY());
		//vertex.setZ(Position[2] + slectnode.getZ());
		//ReadShp getvertx;
		////bool modifyvertex = getvertx.slectvertex(shppath, vertex);//�ж϶����Ƿ���ѹƽ��Χ��
		//bool modifyvertex = getvertx.moreslectvertex(shppath, vertex);
		//if (modifyvertex)
		//{
		//	
		//	float_t Position_x = Position[0];
		//	float_t Position_y = Position[1];
		//	float_t Position_z = elevation - slectnode.getZ();
		//	outF.write(reinterpret_cast<char*>(&Position_x), sizeof(Position_x));
		//	outF.write(reinterpret_cast<char*>(&Position_y), sizeof(Position_y));
		//	outF.write(reinterpret_cast<char*>(&Position_z), sizeof(Position_z));

		//}
		//else
		//{
		//	float_t Position_x = Position[0];
		//	float_t Position_y = Position[1];
		//	float_t Position_z = Position[2];
		//	outF.write(reinterpret_cast<char*>(&Position_x), sizeof(Position_x));
		//	outF.write(reinterpret_cast<char*>(&Position_y), sizeof(Position_y));
		//	outF.write(reinterpret_cast<char*>(&Position_z), sizeof(Position_z));
		//}

		float_t Position_x = Position[0];
		float_t Position_y = Position[1];
		float_t Position_z = elevation - slectnode.getZ();
		outF.write(reinterpret_cast<char*>(&Position_x), sizeof(Position_x));
		outF.write(reinterpret_cast<char*>(&Position_y), sizeof(Position_y));
		outF.write(reinterpret_cast<char*>(&Position_z), sizeof(Position_z));




	}
	//���ݶ���������������������ȡbin�ж���ķ������꣬���浽�µ�bin�ļ���
	for (int i = 0; i < vertexIndexcount[0]; i++)
	{
		float_t Normal[1 * 3];
		fin.read((char*)Normal, sizeof(float_t) * (1 * 3));
		float_t Normal_x = Normal[0];
		float_t Normal_y = Normal[1];
		float_t Normal_z = Normal[2];
		outF.write(reinterpret_cast<char*>(&Normal_x), sizeof(Normal_x));
		outF.write(reinterpret_cast<char*>(&Normal_y), sizeof(Normal_y));
		outF.write(reinterpret_cast<char*>(&Normal_z), sizeof(Normal_z));
	}
	//���ݶ���������������������ȡbin�ж�����������꣬���浽�µ�bin�ļ���
	for (int i = 0; i < vertexIndexcount[0]; i++)
	{
		float_t Uv0[1 * 2];
		fin.read((char*)Uv0, sizeof(float_t) * (1 * 2));
		float_t Uv0_x = Uv0[0];
		float_t Uv0_y = Uv0[1];
		outF.write(reinterpret_cast<char*>(&Uv0_x), sizeof(Uv0_x));
		outF.write(reinterpret_cast<char*>(&Uv0_y), sizeof(Uv0_y));
	}
	//���ݶ���������������������ȡbin����ɫ�����浽�µ�bin�ļ���
	for (size_t i = 0; i < vertexIndexcount[0]; i++)
	{
		uint8_t Color_x[1 * 4];
		fin.read((char*)Color_x, sizeof(uint8_t) * (1 * 4));
		uint8_t Color_x0 = Color_x[0];
		uint8_t Color_x1 = Color_x[1];
		uint8_t Color_x2 = Color_x[2];
		uint8_t Color_x3 = Color_x[3];
		outF.write(reinterpret_cast<char*>(&Color_x0), sizeof(Color_x0));
		outF.write(reinterpret_cast<char*>(&Color_x1), sizeof(Color_x1));
		outF.write(reinterpret_cast<char*>(&Color_x2), sizeof(Color_x2));
		outF.write(reinterpret_cast<char*>(&Color_x3), sizeof(Color_x3));
	}
	//�� FeatureIdд�뵽�µ�bin��
	uint64_t FeatureId[1 * 1];
	fin.read((char*)FeatureId, sizeof(uint64_t) * (1 * 1));
	outF.write(reinterpret_cast<char*>(&FeatureId), sizeof(FeatureId));
	uint32_t FaceRange_start[1 * 1];
	fin.read((char*)FaceRange_start, sizeof(uint32_t) * (1 * 1));
	outF.write(reinterpret_cast<char*>(&FaceRange_start), sizeof(FaceRange_start));
	uint32_t FaceRange_end[1 * 1];
	fin.read((char*)FaceRange_end, sizeof(uint32_t) * (1 * 1));
	outF.write(reinterpret_cast<char*>(&FaceRange_end), sizeof(FaceRange_end));
	//cout << "vsize " << endl;
	fin.close();
	outF.close();
	//ɾ��ԭ�е�bin�ļ���ѹ����
	remove(inbin.c_str());//ɾ��binѹ����
	remove(uncombin1.c_str());
	_rmdir(uncombin.c_str());//ɾ��bin�ļ�
	//ѹ���µ�bin�ļ�
	uncompessbin.exeCompress(outbin, inbin);
	//ɾ����binδѹ���ļ�
	remove(outbin.c_str());
	//system("pause");
}

//�ڿ�
void BinModify::dighole(string shppath, OGRPoint slectnode, double elevation)
{
	//���ȸ��ݴ����ѹƽ��Χ�ڵĽڵ㣬��ȡ�ڵ�ID
	int nodeid = slectnode.getM();
	string inbin = "process/nodes/" + to_string(nodeid) + "/geometries/0.bin.gz";
	string uncombin = "process/nodes/" + to_string(nodeid) + "/geometries/0";
	string uncombin1 = "process/nodes/" + to_string(nodeid) + "/geometries/0/0.bin";
	//��ѹbinѹ����
	ZipHelper uncompessbin;
	uncompessbin.exeUnCompress(uncombin, inbin);
	ifstream fin;
	fin.open(uncombin1, ios::binary);
	if (!fin)
	{
		cout << "open error!" << endl;
		return;
	}
	string path = inbin.substr(0, inbin.find_last_of('/'));
	string outbin = path + "/0.bin";
	std::ofstream outF(outbin, std::ios::binary);
	int vertexIndexcount[1 * 1];
	int vertexIndexcountdef[1 * 1];
	fin.read((char*)vertexIndexcount, sizeof(int) * (1 * 1));//��bin�ж�ȡ������������
	//std::cout << 1 << ": " << vertexIndexcount[0] << std::endl;
	int w_vertexIndexcount = vertexIndexcount[0];
	outF.write(reinterpret_cast<char*>(&w_vertexIndexcount), sizeof(w_vertexIndexcount));//��������������д����bin��
	fin.read((char*)vertexIndexcountdef, sizeof(int) * (1 * 1));
	//std::cout << 2 << ": " << vertexIndexcountdef[0] << std::endl;
	int w_vertexIndexcountdef = vertexIndexcountdef[0];
	outF.write(reinterpret_cast<char*>(&w_vertexIndexcountdef), sizeof(w_vertexIndexcountdef));//������Ķ�����������д����bin��
	int vertexcount = vertexIndexcount[0];
	//���ݶ���������������������ȡbin�ж����������꣬�ж����Ƿ���ѹƽ��Χ�ڣ����޸����±��浽�µ�bin�ļ���
	for (int i = 0; i < vertexIndexcount[0]; i++)
	{
		float_t Position[1 * 3];
		fin.read((char*)Position, sizeof(float_t) * (1 * 3));
		//ɾ���ж϶����Ƿ���ѹƽ��Χ��
		//OGRPoint vertex;
		//vertex.setX(Position[0] + slectnode.getX());
		//vertex.setY(Position[1] + slectnode.getY());
		//vertex.setZ(Position[2] + slectnode.getZ());
		//ReadShp getvertx;
		////bool modifyvertex = getvertx.slectvertex(shppath, vertex);//�ж϶����Ƿ���ѹƽ��Χ��
		//bool modifyvertex = getvertx.moreslectvertex(shppath, vertex);
		//if (modifyvertex)
		//{
		//	
		//	float_t Position_x = Position[0];
		//	float_t Position_y = Position[1];
		//	float_t Position_z = elevation - slectnode.getZ();
		//	outF.write(reinterpret_cast<char*>(&Position_x), sizeof(Position_x));
		//	outF.write(reinterpret_cast<char*>(&Position_y), sizeof(Position_y));
		//	outF.write(reinterpret_cast<char*>(&Position_z), sizeof(Position_z));

		//}
		//else
		//{
		//	float_t Position_x = Position[0];
		//	float_t Position_y = Position[1];
		//	float_t Position_z = Position[2];
		//	outF.write(reinterpret_cast<char*>(&Position_x), sizeof(Position_x));
		//	outF.write(reinterpret_cast<char*>(&Position_y), sizeof(Position_y));
		//	outF.write(reinterpret_cast<char*>(&Position_z), sizeof(Position_z));
		//}

		float_t Position_x = Position[0];
		float_t Position_y = Position[1];
		float_t Position_z = Position[2];
		outF.write(reinterpret_cast<char*>(&Position_x), sizeof(Position_x));
		outF.write(reinterpret_cast<char*>(&Position_y), sizeof(Position_y));
		outF.write(reinterpret_cast<char*>(&Position_z), sizeof(Position_z));




	}
	//���ݶ���������������������ȡbin�ж���ķ������꣬���浽�µ�bin�ļ���
	for (int i = 0; i < vertexIndexcount[0]; i++)
	{
		float_t Normal[1 * 3];
		fin.read((char*)Normal, sizeof(float_t) * (1 * 3));
		float_t Normal_x = Normal[0];
		float_t Normal_y = Normal[1];
		float_t Normal_z = Normal[2];
		outF.write(reinterpret_cast<char*>(&Normal_x), sizeof(Normal_x));
		outF.write(reinterpret_cast<char*>(&Normal_y), sizeof(Normal_y));
		outF.write(reinterpret_cast<char*>(&Normal_z), sizeof(Normal_z));
	}
	//���ݶ���������������������ȡbin�ж�����������꣬���浽�µ�bin�ļ���
	for (int i = 0; i < vertexIndexcount[0]; i++)
	{
		float_t Uv0[1 * 2];
		fin.read((char*)Uv0, sizeof(float_t) * (1 * 2));
		float_t Uv0_x = Uv0[0];
		float_t Uv0_y = Uv0[1];
		outF.write(reinterpret_cast<char*>(&Uv0_x), sizeof(Uv0_x));
		outF.write(reinterpret_cast<char*>(&Uv0_y), sizeof(Uv0_y));
	}
	//���ݶ���������������������ȡbin����ɫ�����浽�µ�bin�ļ���
	for (size_t i = 0; i < vertexIndexcount[0]; i++)
	{
		uint8_t Color_x[1 * 4];
		fin.read((char*)Color_x, sizeof(uint8_t) * (1 * 4));
		uint8_t Color_x0 = Color_x[0];
		uint8_t Color_x1 = Color_x[1];
		uint8_t Color_x2 = Color_x[2];
		uint8_t Color_x3 = 0;//�ı���ɫ���ڿ�
		outF.write(reinterpret_cast<char*>(&Color_x0), sizeof(Color_x0));
		outF.write(reinterpret_cast<char*>(&Color_x1), sizeof(Color_x1));
		outF.write(reinterpret_cast<char*>(&Color_x2), sizeof(Color_x2));
		outF.write(reinterpret_cast<char*>(&Color_x3), sizeof(Color_x3));
	}
	//�� FeatureIdд�뵽�µ�bin��
	uint64_t FeatureId[1 * 1];
	fin.read((char*)FeatureId, sizeof(uint64_t) * (1 * 1));
	outF.write(reinterpret_cast<char*>(&FeatureId), sizeof(FeatureId));
	uint32_t FaceRange_start[1 * 1];
	fin.read((char*)FaceRange_start, sizeof(uint32_t) * (1 * 1));
	outF.write(reinterpret_cast<char*>(&FaceRange_start), sizeof(FaceRange_start));
	uint32_t FaceRange_end[1 * 1];
	fin.read((char*)FaceRange_end, sizeof(uint32_t) * (1 * 1));
	outF.write(reinterpret_cast<char*>(&FaceRange_end), sizeof(FaceRange_end));
	//cout << "vsize " << endl;
	fin.close();
	outF.close();
	//ɾ��ԭ�е�bin�ļ���ѹ����
	remove(inbin.c_str());//ɾ��binѹ����
	remove(uncombin1.c_str());
	_rmdir(uncombin.c_str());//ɾ��bin�ļ�
	//ѹ���µ�bin�ļ�
	uncompessbin.exeCompress(outbin, inbin);
	//ɾ����binδѹ���ļ�
	remove(outbin.c_str());
	//system("pause");
}

//ģ��͸��
void BinModify::transparent(string shppath, OGRPoint slectnode, double transparency)
{
	//ת��͸���ȣ������Ϊ0-1֮������֣���ת��Ϊ0-255֮��
	uint8_t transparency_color = 254 * transparency;
	//���ȸ��ݴ����ѹƽ��Χ�ڵĽڵ㣬��ȡ�ڵ�ID
	int nodeid = slectnode.getM();
	string inbin = "process/nodes/" + to_string(nodeid) + "/geometries/0.bin.gz";
	string uncombin = "process/nodes/" + to_string(nodeid) + "/geometries/0";
	string uncombin1 = "process/nodes/" + to_string(nodeid) + "/geometries/0/0.bin";
	//��ѹbinѹ����
	ZipHelper uncompessbin;
	uncompessbin.exeUnCompress(uncombin, inbin);
	ifstream fin;
	fin.open(uncombin1, ios::binary);
	if (!fin)
	{
		cout << "open error!" << endl;
		return;
	}
	string path = inbin.substr(0, inbin.find_last_of('/'));
	string outbin = path + "/0.bin";
	std::ofstream outF(outbin, std::ios::binary);
	int vertexIndexcount[1 * 1];
	int vertexIndexcountdef[1 * 1];
	fin.read((char*)vertexIndexcount, sizeof(int) * (1 * 1));//��bin�ж�ȡ������������
	//std::cout << 1 << ": " << vertexIndexcount[0] << std::endl;
	int w_vertexIndexcount = vertexIndexcount[0];
	outF.write(reinterpret_cast<char*>(&w_vertexIndexcount), sizeof(w_vertexIndexcount));//��������������д����bin��
	fin.read((char*)vertexIndexcountdef, sizeof(int) * (1 * 1));
	//std::cout << 2 << ": " << vertexIndexcountdef[0] << std::endl;
	int w_vertexIndexcountdef = vertexIndexcountdef[0];
	outF.write(reinterpret_cast<char*>(&w_vertexIndexcountdef), sizeof(w_vertexIndexcountdef));//������Ķ�����������д����bin��
	int vertexcount = vertexIndexcount[0];
	//���ݶ���������������������ȡbin�ж����������꣬�ж����Ƿ���ѹƽ��Χ�ڣ����޸����±��浽�µ�bin�ļ���
	for (int i = 0; i < vertexIndexcount[0]; i++)
	{
		float_t Position[1 * 3];
		fin.read((char*)Position, sizeof(float_t) * (1 * 3));
		float_t Position_x = Position[0];
		float_t Position_y = Position[1];
		float_t Position_z = Position[2];
		outF.write(reinterpret_cast<char*>(&Position_x), sizeof(Position_x));
		outF.write(reinterpret_cast<char*>(&Position_y), sizeof(Position_y));
		outF.write(reinterpret_cast<char*>(&Position_z), sizeof(Position_z));
	}
	//���ݶ���������������������ȡbin�ж���ķ������꣬���浽�µ�bin�ļ���
	for (int i = 0; i < vertexIndexcount[0]; i++)
	{
		float_t Normal[1 * 3];
		fin.read((char*)Normal, sizeof(float_t) * (1 * 3));
		float_t Normal_x = Normal[0];
		float_t Normal_y = Normal[1];
		float_t Normal_z = Normal[2];
		outF.write(reinterpret_cast<char*>(&Normal_x), sizeof(Normal_x));
		outF.write(reinterpret_cast<char*>(&Normal_y), sizeof(Normal_y));
		outF.write(reinterpret_cast<char*>(&Normal_z), sizeof(Normal_z));
	}
	//���ݶ���������������������ȡbin�ж�����������꣬���浽�µ�bin�ļ���
	for (int i = 0; i < vertexIndexcount[0]; i++)
	{
		float_t Uv0[1 * 2];
		fin.read((char*)Uv0, sizeof(float_t) * (1 * 2));
		float_t Uv0_x = Uv0[0];
		float_t Uv0_y = Uv0[1];
		outF.write(reinterpret_cast<char*>(&Uv0_x), sizeof(Uv0_x));
		outF.write(reinterpret_cast<char*>(&Uv0_y), sizeof(Uv0_y));
	}
	//���ݶ���������������������ȡbin����ɫ�����浽�µ�bin�ļ���
	for (size_t i = 0; i < vertexIndexcount[0]; i++)
	{
		uint8_t Color_x[1 * 4];
		fin.read((char*)Color_x, sizeof(uint8_t) * (1 * 4));
		uint8_t Color_x0 = Color_x[0];
		uint8_t Color_x1 = Color_x[1];
		uint8_t Color_x2 = Color_x[2];
		uint8_t Color_x3 = transparency_color;//ģ��͸��
		outF.write(reinterpret_cast<char*>(&Color_x0), sizeof(Color_x0));
		outF.write(reinterpret_cast<char*>(&Color_x1), sizeof(Color_x1));
		outF.write(reinterpret_cast<char*>(&Color_x2), sizeof(Color_x2));
		outF.write(reinterpret_cast<char*>(&Color_x3), sizeof(Color_x3));
	}
	//�� FeatureIdд�뵽�µ�bin��
	uint64_t FeatureId[1 * 1];
	fin.read((char*)FeatureId, sizeof(uint64_t) * (1 * 1));
	outF.write(reinterpret_cast<char*>(&FeatureId), sizeof(FeatureId));
	uint32_t FaceRange_start[1 * 1];
	fin.read((char*)FaceRange_start, sizeof(uint32_t) * (1 * 1));
	outF.write(reinterpret_cast<char*>(&FaceRange_start), sizeof(FaceRange_start));
	uint32_t FaceRange_end[1 * 1];
	fin.read((char*)FaceRange_end, sizeof(uint32_t) * (1 * 1));
	outF.write(reinterpret_cast<char*>(&FaceRange_end), sizeof(FaceRange_end));
	//cout << "vsize " << endl;
	fin.close();
	outF.close();
	//ɾ��ԭ�е�bin�ļ���ѹ����
	remove(inbin.c_str());//ɾ��binѹ����
	remove(uncombin1.c_str());
	_rmdir(uncombin.c_str());//ɾ��bin�ļ�
	//ѹ���µ�bin�ļ�
	uncompessbin.exeCompress(outbin, inbin);
	//ɾ����binδѹ���ļ�
	remove(outbin.c_str());
	//system("pause");
}
BinModify::~BinModify()
{
}