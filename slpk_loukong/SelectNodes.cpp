#pragma warning(disable:4996)
#include "SelectNodes.h"
#include "json.h"
//获取文件夹中所有的文件
vector<string> SelectNodes::visitFiles(string path)
{
	vector<string> files;
	struct _finddata_t   filefind;
	string  curr = path + "/*.*";
	int   done = 0;
	intptr_t handle;
	//int filenum = 0;
	if ((handle = _findfirst(curr.c_str(), &filefind)) == -1)return files;
	while (!(done = _findnext(handle, &filefind)))
	{
		//printf("%s\n", filefind.name);
		if (!strcmp(filefind.name, "..")) {
			continue;
		}
		//for (i = 0; i < layer; i++)cout << "     ";
		if ((_A_SUBDIR == filefind.attrib)) //是目录
		{
			//printf("----------%s\n", filefind.name);
			//cout << filefind.name << "(dir)" << endl;
			/*curr = path + "\\" + filefind.name;
			dirs.push_back(curr);*/
			//filenum += 1;
		}
		else//不是目录，是文件     
		{
			//cout << path + "\\" + filefind.name << endl;
			curr = path + "/" + filefind.name;
			files.push_back(curr);
		}
	}
	_findclose(handle);
	return files;
}
vector<OGRPoint> SelectNodes::getallnodes()
{
	//已经将slpk模型文件解压到了process文件夹中，这里需根据路径获取节点页索引文件，并解压
	//遍历获取nodepages文件夹下面所有的压缩包，并解压
	vector<string> nodepages = visitFiles("process/nodepages");

	vector<OGRPoint> allnodes;
	for (int i = 0; i < nodepages.size(); i++)
	{
		string pagename = nodepages[i].substr(nodepages[i].find_last_of('/') + 1, nodepages[i].find_last_of('.') - 6 - nodepages[i].find_last_of('/'));
		string uncompesspath = "process/nodepages/" + pagename;
		string uncompesspath1 = "process/nodepages/" + pagename + "/" + pagename + ".json";
		ZipHelper uncompesspage;
		uncompesspage.exeUnCompress(uncompesspath, nodepages[i]);
		Json::Reader reader;
		Json::Value root;
		ifstream f;
		f.open(uncompesspath1, ios::binary);
		if (f.is_open())
		{
			bool parse_ok = reader.parse(f, root);
			f.close();
			if (parse_ok)
			{
				int nodescount = root["nodes"].size();//节点页索引中节点总数
				int j = 0;
				if (i == 0)//判定是否是首节点页，因为第一页中含有根节点要排除
				{
					j = 1;
				}
				for (j; j < nodescount; j++)
				{
					OGRPoint nodes;
					nodes.setX(root["nodes"][j]["obb"]["center"][0].asDouble());
					nodes.setY(root["nodes"][j]["obb"]["center"][1].asDouble());
					nodes.setZ(root["nodes"][j]["obb"]["center"][2].asDouble());
					nodes.setM(root["nodes"][j]["mesh"]["geometry"]["resource"].asDouble());//这里将节点ID放到M中
					allnodes.push_back(nodes);
				}

			}
		}
		remove(uncompesspath1.c_str());
		_rmdir(uncompesspath.c_str());//删除bin文件

	}
	return allnodes;
}
vector<DefPoint> SelectNodes::getall()
{
	//已经将slpk模型文件解压到了process文件夹中，这里需根据路径获取节点页索引文件，并解压
	//遍历获取nodepages文件夹下面所有的压缩包，并解压
	vector<string> nodepages = visitFiles("process/nodepages");

	vector<DefPoint> allnodes;
	for (int i = 0; i < nodepages.size(); i++)
	{
		string pagename = nodepages[i].substr(nodepages[i].find_last_of('/') + 1, nodepages[i].find_last_of('.') - 6 - nodepages[i].find_last_of('/'));
		string uncompesspath = "process/nodepages/" + pagename;
		string uncompesspath1 = "process/nodepages/" + pagename + "/" + pagename + ".json";
		ZipHelper uncompesspage;
		uncompesspage.exeUnCompress(uncompesspath, nodepages[i]);
		Json::Reader reader;
		Json::Value root;
		ifstream f;
		f.open(uncompesspath1, ios::binary);
		if (f.is_open())
		{
			bool parse_ok = reader.parse(f, root);
			f.close();
			if (parse_ok)
			{
				int nodescount = root["nodes"].size();//节点页索引中节点总数
				int j = 0;
				if (i == 0)//判定是否是首节点页，因为第一页中含有根节点要排除
				{
					j = 1;
				}
				for (j; j < nodescount; j++)
				{
					//OGRPoint nodes;
					//nodes.setX(root["nodes"][j]["obb"]["center"][0].asDouble());
					//nodes.setY(root["nodes"][j]["obb"]["center"][1].asDouble());
					//nodes.setZ(root["nodes"][j]["obb"]["center"][2].asDouble());
					//nodes.setM(root["nodes"][j]["mesh"]["geometry"]["resource"].asDouble());//这里将节点ID放到M中
					//allnodes.push_back(nodes);
					double x = root["nodes"][j]["obb"]["center"][0].asDouble();
					double y = root["nodes"][j]["obb"]["center"][1].asDouble();
					double z = root["nodes"][j]["obb"]["center"][2].asDouble();
					double hx = root["nodes"][j]["obb"]["halfSize"][0].asDouble();
					double hy = root["nodes"][j]["obb"]["halfSize"][1].asDouble();
					double hz = root["nodes"][j]["obb"]["halfSize"][2].asDouble();
					int id = root["nodes"][j]["mesh"]["geometry"]["resource"].asInt();
					DefPoint nodes(x, y, z, hx, hy, hz, id);
					allnodes.push_back(nodes);
				}

			}
		}
		remove(uncompesspath1.c_str());
		_rmdir(uncompesspath.c_str());//删除bin文件

	}
	return allnodes;
}
