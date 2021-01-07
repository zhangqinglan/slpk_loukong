#include "BinModify.h"
BinModify::BinModify()
{
}
//压平
void BinModify::modifynodebin(string shppath, OGRPoint slectnode, double elevation)
{
	//首先根据传入的压平范围内的节点，获取节点ID
	int nodeid = slectnode.getM();
	string inbin = "process/nodes/" + to_string(nodeid) + "/geometries/0.bin.gz";
	string uncombin = "process/nodes/" + to_string(nodeid) + "/geometries/0";
	string uncombin1 = "process/nodes/" + to_string(nodeid) + "/geometries/0/0.bin";
	//解压bin压缩包
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
	fin.read((char*)vertexIndexcount, sizeof(int) * (1 * 1));//从bin中读取顶点索引数量
	//std::cout << 1 << ": " << vertexIndexcount[0] << std::endl;
	int w_vertexIndexcount = vertexIndexcount[0];
	outF.write(reinterpret_cast<char*>(&w_vertexIndexcount), sizeof(w_vertexIndexcount));//将顶点索引数量写入新bin中
	fin.read((char*)vertexIndexcountdef, sizeof(int) * (1 * 1));
	//std::cout << 2 << ": " << vertexIndexcountdef[0] << std::endl;
	int w_vertexIndexcountdef = vertexIndexcountdef[0];
	outF.write(reinterpret_cast<char*>(&w_vertexIndexcountdef), sizeof(w_vertexIndexcountdef));//将定义的顶点索引数量写入新bin中
	int vertexcount = vertexIndexcount[0];
	//根据顶点索引的数量，遍历读取bin中顶点的相对坐标，判断其是否在压平范围内，并修改重新保存到新的bin文件中
	for (int i = 0; i < vertexIndexcount[0]; i++)
	{
		float_t Position[1 * 3];
		fin.read((char*)Position, sizeof(float_t) * (1 * 3));
		//删除判断顶点是否在压平范围内
		//OGRPoint vertex;
		//vertex.setX(Position[0] + slectnode.getX());
		//vertex.setY(Position[1] + slectnode.getY());
		//vertex.setZ(Position[2] + slectnode.getZ());
		//ReadShp getvertx;
		////bool modifyvertex = getvertx.slectvertex(shppath, vertex);//判断顶点是否在压平范围内
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
	//根据顶点索引的数量，遍历读取bin中顶点的法线坐标，保存到新的bin文件中
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
	//根据顶点索引的数量，遍历读取bin中顶点的纹理坐标，保存到新的bin文件中
	for (int i = 0; i < vertexIndexcount[0]; i++)
	{
		float_t Uv0[1 * 2];
		fin.read((char*)Uv0, sizeof(float_t) * (1 * 2));
		float_t Uv0_x = Uv0[0];
		float_t Uv0_y = Uv0[1];
		outF.write(reinterpret_cast<char*>(&Uv0_x), sizeof(Uv0_x));
		outF.write(reinterpret_cast<char*>(&Uv0_y), sizeof(Uv0_y));
	}
	//根据顶点索引的数量，遍历读取bin中颜色，保存到新的bin文件中
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
	//将 FeatureId写入到新的bin中
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
	//删除原有的bin文件及压缩包
	remove(inbin.c_str());//删除bin压缩包
	remove(uncombin1.c_str());
	_rmdir(uncombin.c_str());//删除bin文件
	//压缩新的bin文件
	uncompessbin.exeCompress(outbin, inbin);
	//删除新bin未压缩文件
	remove(outbin.c_str());
	//system("pause");
}

//挖坑
void BinModify::dighole(string shppath, OGRPoint slectnode, double elevation)
{
	//首先根据传入的压平范围内的节点，获取节点ID
	int nodeid = slectnode.getM();
	string inbin = "process/nodes/" + to_string(nodeid) + "/geometries/0.bin.gz";
	string uncombin = "process/nodes/" + to_string(nodeid) + "/geometries/0";
	string uncombin1 = "process/nodes/" + to_string(nodeid) + "/geometries/0/0.bin";
	//解压bin压缩包
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
	fin.read((char*)vertexIndexcount, sizeof(int) * (1 * 1));//从bin中读取顶点索引数量
	//std::cout << 1 << ": " << vertexIndexcount[0] << std::endl;
	int w_vertexIndexcount = vertexIndexcount[0];
	outF.write(reinterpret_cast<char*>(&w_vertexIndexcount), sizeof(w_vertexIndexcount));//将顶点索引数量写入新bin中
	fin.read((char*)vertexIndexcountdef, sizeof(int) * (1 * 1));
	//std::cout << 2 << ": " << vertexIndexcountdef[0] << std::endl;
	int w_vertexIndexcountdef = vertexIndexcountdef[0];
	outF.write(reinterpret_cast<char*>(&w_vertexIndexcountdef), sizeof(w_vertexIndexcountdef));//将定义的顶点索引数量写入新bin中
	int vertexcount = vertexIndexcount[0];
	//根据顶点索引的数量，遍历读取bin中顶点的相对坐标，判断其是否在压平范围内，并修改重新保存到新的bin文件中
	for (int i = 0; i < vertexIndexcount[0]; i++)
	{
		float_t Position[1 * 3];
		fin.read((char*)Position, sizeof(float_t) * (1 * 3));
		//删除判断顶点是否在压平范围内
		//OGRPoint vertex;
		//vertex.setX(Position[0] + slectnode.getX());
		//vertex.setY(Position[1] + slectnode.getY());
		//vertex.setZ(Position[2] + slectnode.getZ());
		//ReadShp getvertx;
		////bool modifyvertex = getvertx.slectvertex(shppath, vertex);//判断顶点是否在压平范围内
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
	//根据顶点索引的数量，遍历读取bin中顶点的法线坐标，保存到新的bin文件中
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
	//根据顶点索引的数量，遍历读取bin中顶点的纹理坐标，保存到新的bin文件中
	for (int i = 0; i < vertexIndexcount[0]; i++)
	{
		float_t Uv0[1 * 2];
		fin.read((char*)Uv0, sizeof(float_t) * (1 * 2));
		float_t Uv0_x = Uv0[0];
		float_t Uv0_y = Uv0[1];
		outF.write(reinterpret_cast<char*>(&Uv0_x), sizeof(Uv0_x));
		outF.write(reinterpret_cast<char*>(&Uv0_y), sizeof(Uv0_y));
	}
	//根据顶点索引的数量，遍历读取bin中颜色，保存到新的bin文件中
	for (size_t i = 0; i < vertexIndexcount[0]; i++)
	{
		uint8_t Color_x[1 * 4];
		fin.read((char*)Color_x, sizeof(uint8_t) * (1 * 4));
		uint8_t Color_x0 = Color_x[0];
		uint8_t Color_x1 = Color_x[1];
		uint8_t Color_x2 = Color_x[2];
		uint8_t Color_x3 = 0;//改变颜色，挖坑
		outF.write(reinterpret_cast<char*>(&Color_x0), sizeof(Color_x0));
		outF.write(reinterpret_cast<char*>(&Color_x1), sizeof(Color_x1));
		outF.write(reinterpret_cast<char*>(&Color_x2), sizeof(Color_x2));
		outF.write(reinterpret_cast<char*>(&Color_x3), sizeof(Color_x3));
	}
	//将 FeatureId写入到新的bin中
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
	//删除原有的bin文件及压缩包
	remove(inbin.c_str());//删除bin压缩包
	remove(uncombin1.c_str());
	_rmdir(uncombin.c_str());//删除bin文件
	//压缩新的bin文件
	uncompessbin.exeCompress(outbin, inbin);
	//删除新bin未压缩文件
	remove(outbin.c_str());
	//system("pause");
}

//模型透明
void BinModify::transparent(string shppath, OGRPoint slectnode, double transparency)
{
	//转换透明度，输入的为0-1之间的数字，需转化为0-255之间
	uint8_t transparency_color = 254 * transparency;
	//首先根据传入的压平范围内的节点，获取节点ID
	int nodeid = slectnode.getM();
	string inbin = "process/nodes/" + to_string(nodeid) + "/geometries/0.bin.gz";
	string uncombin = "process/nodes/" + to_string(nodeid) + "/geometries/0";
	string uncombin1 = "process/nodes/" + to_string(nodeid) + "/geometries/0/0.bin";
	//解压bin压缩包
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
	fin.read((char*)vertexIndexcount, sizeof(int) * (1 * 1));//从bin中读取顶点索引数量
	//std::cout << 1 << ": " << vertexIndexcount[0] << std::endl;
	int w_vertexIndexcount = vertexIndexcount[0];
	outF.write(reinterpret_cast<char*>(&w_vertexIndexcount), sizeof(w_vertexIndexcount));//将顶点索引数量写入新bin中
	fin.read((char*)vertexIndexcountdef, sizeof(int) * (1 * 1));
	//std::cout << 2 << ": " << vertexIndexcountdef[0] << std::endl;
	int w_vertexIndexcountdef = vertexIndexcountdef[0];
	outF.write(reinterpret_cast<char*>(&w_vertexIndexcountdef), sizeof(w_vertexIndexcountdef));//将定义的顶点索引数量写入新bin中
	int vertexcount = vertexIndexcount[0];
	//根据顶点索引的数量，遍历读取bin中顶点的相对坐标，判断其是否在压平范围内，并修改重新保存到新的bin文件中
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
	//根据顶点索引的数量，遍历读取bin中顶点的法线坐标，保存到新的bin文件中
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
	//根据顶点索引的数量，遍历读取bin中顶点的纹理坐标，保存到新的bin文件中
	for (int i = 0; i < vertexIndexcount[0]; i++)
	{
		float_t Uv0[1 * 2];
		fin.read((char*)Uv0, sizeof(float_t) * (1 * 2));
		float_t Uv0_x = Uv0[0];
		float_t Uv0_y = Uv0[1];
		outF.write(reinterpret_cast<char*>(&Uv0_x), sizeof(Uv0_x));
		outF.write(reinterpret_cast<char*>(&Uv0_y), sizeof(Uv0_y));
	}
	//根据顶点索引的数量，遍历读取bin中颜色，保存到新的bin文件中
	for (size_t i = 0; i < vertexIndexcount[0]; i++)
	{
		uint8_t Color_x[1 * 4];
		fin.read((char*)Color_x, sizeof(uint8_t) * (1 * 4));
		uint8_t Color_x0 = Color_x[0];
		uint8_t Color_x1 = Color_x[1];
		uint8_t Color_x2 = Color_x[2];
		uint8_t Color_x3 = transparency_color;//模型透明
		outF.write(reinterpret_cast<char*>(&Color_x0), sizeof(Color_x0));
		outF.write(reinterpret_cast<char*>(&Color_x1), sizeof(Color_x1));
		outF.write(reinterpret_cast<char*>(&Color_x2), sizeof(Color_x2));
		outF.write(reinterpret_cast<char*>(&Color_x3), sizeof(Color_x3));
	}
	//将 FeatureId写入到新的bin中
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
	//删除原有的bin文件及压缩包
	remove(inbin.c_str());//删除bin压缩包
	remove(uncombin1.c_str());
	_rmdir(uncombin.c_str());//删除bin文件
	//压缩新的bin文件
	uncompessbin.exeCompress(outbin, inbin);
	//删除新bin未压缩文件
	remove(outbin.c_str());
	//system("pause");
}
BinModify::~BinModify()
{
}