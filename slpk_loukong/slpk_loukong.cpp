#include <iostream>
#include "ZipHelper.h"
#include "BinModify.h"
#include "SelectNodes.h"
#include "DefPoint.h"
#include "geos.h"
#include <thread>
#include <mutex>
#include "DeleteProcess.h"
#include "JsonModify.h"

//多线程函数
std::mutex mtx;

//将slpk文件夹中的slpk文件按线程数分批
vector<vector<OGRPoint>> splitnodes(vector<OGRPoint>nodes, int count)
{
	int nodenum;
	if (nodes.size() % count == 0)
	{
		nodenum = nodes.size() / count;
	}
	else if (nodes.size() % count != 0)
	{
		nodenum = nodes.size() / count + 1;
	}
	vector<vector<OGRPoint>> nodesfiles;
	for (int i = 0; i < count; i++)
	{
		vector<OGRPoint> node;
		for (int j = i * nodenum; j < (i + 1)* nodenum&&j < nodes.size(); j++)
		{
			node.push_back(nodes[j]);
		}
		nodesfiles.push_back(node);
	}
	return nodesfiles;
}

void modifynode(vector<OGRPoint> nodes, double z)
{
	std::lock_guard<std::mutex> mtx_locker(mtx);
	BinModify modifybin;
	for (int i = 0; i < nodes.size(); i++)
	{
		modifybin.modifynodebin("D:/work_data/work_code/I3S工具/shp/yaping.shp", nodes[i], z);//节点bin文件修改
		cout << "完成修改第" << i << "个" << nodes[i].getM() << "bin" << endl;
	}
}

void dighole(vector<OGRPoint> nodes, double z)
{
	std::lock_guard<std::mutex> mtx_locker(mtx);
	BinModify modifybin;
	for (int i = 0; i < nodes.size(); i++)
	{
		modifybin.dighole("D:/work_data/work_code/I3S工具/shp/yaping.shp", nodes[i], z);//节点bin文件修改
		cout << "完成修改第" << i << "个" << nodes[i].getM() << "bin" << endl;
	}
}

void transparent(vector<OGRPoint> nodes, double z)
{
	std::lock_guard<std::mutex> mtx_locker(mtx);
	BinModify modifybin;
	for (int i = 0; i < nodes.size(); i++)
	{
		modifybin.transparent("D:/work_data/work_code/I3S工具/shp/yaping.shp", nodes[i], z);//节点bin文件修改
		cout << "完成修改第" << i << "个" << nodes[i].getM() << "bin" << endl;
	}
}
int main()
{
	//std::cout << "Hello World!\n";
	//测试解压slpk模型文件
	//ZipHelper uncompessslpk;
	//uncompessslpk.exeUnCompress("D:/work_data/work_code/I3S工具/test/yaping/w_yaping1","D:/work_data/work_code/I3S工具/test/yaping/w_yaping1_1.slpk");
	//测试解压文件压缩包
	//uncompessslpk.exeUnCompress("D:/work_data/work_code/I3S工具/test/wout1", "D:/work_data/work_code/I3S工具/test/wout1/3dSceneLayer.json.gz");

	//测试文件压缩为slpk
	//uncompessslpk.CreateZipFromDir("D:/work_data/work_code/I3S工具/test/yaping/w_yaping2", "D:/work_data/work_code/I3S工具/test/yaping/w_yaping2_1.slpk");
	//测试文件压缩
	//uncompessslpk.exeCompress("D:/work_data/work_code/I3S工具/test/wout1/metadata.json", "D:/work_data/work_code/I3S工具/test/metadata.json.gz");

	//测试bin文件的读取
	//BinModify readb;
	//readb.readbin("0.bin");

	//测试：修改bin(2020.12.28 )
	//BinModify modifybin;
	//OGRPoint slectnode;
	//slectnode.setM(186);
	//slectnode.setX(70749.991893467319);
	//slectnode.setY(230150.0000038147);
	//slectnode.setZ(35.531691134530604);
	//modifybin.modifynodebin("D:/work_data/work_code/I3S工具/shp/morepolygon.shp",slectnode, 10);

	//测试：根据压平范围从节点页中获取压平范围中的节点坐标及ID
	//SelectNodes getnodes;
	//vector<OGRPoint> allnodes = getnodes.getallnodes();//从节点页索引中获取所有节点坐标及ID
	//ReadShp getslectnodes;
	//vector<OGRPoint> slectnodes = getslectnodes.readShp("D:/work_data/work_code/I3S工具/shp/yaping.shp", allnodes);
	//cout << slectnodes.size() << endl;
	//system("pause");

	////测试：根据压平范围及节点面从节点页中获取压平范围中的节点坐标及ID（2020.12.31）
	//SelectNodes getnodes;
	//vector<DefPoint> allnodes = getnodes.getall();//从节点页索引中获取所有节点坐标及ID
	//ReadShp getslectnodes;
	////vector<OGRPoint> slectnodes = getslectnodes.readShp("D:/work_data/work_code/I3S工具/shp/yaping.shp", allnodes);
	//vector<OGRPoint> slectnodes = getslectnodes.selectnodes("D:/work_data/work_code/I3S工具/shp/yaping.shp", allnodes);
	//cout << slectnodes.size() << endl;
	//system("pause");

	////测试：获取需要压平的节点，并对节点中的bin文件进行修改（2021.01.04）
	//SelectNodes getnodes;
	//vector<DefPoint> allnodes = getnodes.getall();//从节点页索引中获取所有节点坐标及ID
	//ReadShp getslectnodes;
	////vector<OGRPoint> slectnodes = getslectnodes.readShp("D:/work_data/work_code/I3S工具/shp/yaping.shp", allnodes);
	//vector<OGRPoint> selectnodes = getslectnodes.selectnodes("D:/work_data/work_code/I3S工具/shp/yaping.shp", allnodes);//获取压平范围内的节点
	//BinModify modifybin;
	//for (int i=0;i< selectnodes.size();i++)
	//{
	//	modifybin.modifynodebin("D:/work_data/work_code/I3S工具/shp/yaping.shp", selectnodes[i], 10);//节点bin文件修改
	//	cout << "完成修改第"<<i<<"个"<< selectnodes[i].getM()<<"bin" << endl;
	//}
	//ZipHelper compessslpk;
	//compessslpk.CreateZipFromDir("process", "yaping0105_2.slpk");
	//system("pause");

	//ZipHelper compessslpk;
	////compessslpk.exeCompress("process/3dSceneLayer.json", "process/3dSceneLayer.json.gz");
	//compessslpk.CreateZipFromDir("yaping0104", "yaping0104_1.slpk");

	////测试多线程（2021.01.05）
	//// 定义线程的 id 变量，多个变量使用数组
	//
	//SelectNodes getnodes;
	//vector<DefPoint> allnodes = getnodes.getall();//从节点页索引中获取所有节点坐标及ID
	//ReadShp getslectnodes;
	////vector<OGRPoint> slectnodes = getslectnodes.readShp("D:/work_data/work_code/I3S工具/shp/yaping.shp", allnodes);
	//vector<OGRPoint> selectnodes = getslectnodes.selectnodes("D:/work_data/work_code/I3S工具/shp/yaping.shp", allnodes);//获取压平范围内的节点
	//std::thread threads[10];
	//vector<vector<OGRPoint>> nodesvector = splitnodes(selectnodes, 10);
	//for (int i = 0; i < 10; i++)
	//	threads[i] = std::thread(modifynode, nodesvector[i],20);
	//for (auto &thread : threads)
	//	thread.join();
	//ZipHelper compessslpk;
	//compessslpk.CreateZipFromDir("process", "yaping0105_3.slpk");
	//system("pause");

	////挖坑测试（2021.01.05）
	//ZipHelper uncompessslpk;
 //   uncompessslpk.exeUnCompress("process","yaping0105_3.slpk");

	//SelectNodes getnodes;
	//vector<DefPoint> allnodes = getnodes.getall();//从节点页索引中获取所有节点坐标及ID
	//ReadShp getslectnodes;
	////vector<OGRPoint> slectnodes = getslectnodes.readShp("D:/work_data/work_code/I3S工具/shp/yaping.shp", allnodes);
	//vector<OGRPoint> selectnodes = getslectnodes.selectnodes("D:/work_data/work_code/I3S工具/shp/yaping.shp", allnodes);//获取压平范围内的节点
	//std::thread threads[10];
	//vector<vector<OGRPoint>> nodesvector = splitnodes(selectnodes, 10);
	//for (int i = 0; i < 10; i++)
	//	threads[i] = std::thread(dighole, nodesvector[i], 20);
	//for (auto &thread : threads)
	//	thread.join();
	//ZipHelper compessslpk;
	//compessslpk.CreateZipFromDir("process", "dighole0105_1.slpk");
	////system("pause");
	//DeleteProcess deletepr;
	//vector<string> dir = deletepr.deletefile("process");
	//deletepr.deletedir(dir);
	//system("rd /s/q process");

////模型透明测试（2021.01.05）
//	ZipHelper uncompessslpk;
//	uncompessslpk.exeUnCompress("process", "yaping0105_3.slpk");
//	SelectNodes getnodes;
//	vector<DefPoint> allnodes = getnodes.getall();//从节点页索引中获取所有节点坐标及ID
//	ReadShp getslectnodes;
//	//vector<OGRPoint> slectnodes = getslectnodes.readShp("D:/work_data/work_code/I3S工具/shp/yaping.shp", allnodes);
//	vector<OGRPoint> selectnodes = getslectnodes.selectnodes("D:/work_data/work_code/I3S工具/shp/yaping.shp", allnodes);//获取压平范围内的节点
//	std::thread threads[10];
//	vector<vector<OGRPoint>> nodesvector = splitnodes(selectnodes, 10);
//	for (int i = 0; i < 10; i++)
//		threads[i] = std::thread(transparent, nodesvector[i], 0.4);
//	for (auto &thread : threads)
//		thread.join();
//	ZipHelper compessslpk;
//	compessslpk.CreateZipFromDir("process", "transparent0105.slpk");
//	//system("pause");
//	DeleteProcess deletepr;
//	deletepr.removeDir("process");


//测试：修改json文件（2021.01.06）
 //   JsonModify json3d;
 //   json3d.modify3dScene();
	//DeleteProcess deletepr;
	//deletepr.removeDir("process");


}

