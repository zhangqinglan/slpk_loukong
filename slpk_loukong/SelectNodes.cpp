#pragma warning(disable:4996)
#include "SelectNodes.h"
#include "json.h"
//��ȡ�ļ��������е��ļ�
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
		if ((_A_SUBDIR == filefind.attrib)) //��Ŀ¼
		{
			//printf("----------%s\n", filefind.name);
			//cout << filefind.name << "(dir)" << endl;
			/*curr = path + "\\" + filefind.name;
			dirs.push_back(curr);*/
			//filenum += 1;
		}
		else//����Ŀ¼�����ļ�     
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
	//�Ѿ���slpkģ���ļ���ѹ����process�ļ����У����������·����ȡ�ڵ�ҳ�����ļ�������ѹ
	//������ȡnodepages�ļ����������е�ѹ����������ѹ
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
				int nodescount = root["nodes"].size();//�ڵ�ҳ�����нڵ�����
				int j = 0;
				if (i == 0)//�ж��Ƿ����׽ڵ�ҳ����Ϊ��һҳ�к��и��ڵ�Ҫ�ų�
				{
					j = 1;
				}
				for (j; j < nodescount; j++)
				{
					OGRPoint nodes;
					nodes.setX(root["nodes"][j]["obb"]["center"][0].asDouble());
					nodes.setY(root["nodes"][j]["obb"]["center"][1].asDouble());
					nodes.setZ(root["nodes"][j]["obb"]["center"][2].asDouble());
					nodes.setM(root["nodes"][j]["mesh"]["geometry"]["resource"].asDouble());//���ｫ�ڵ�ID�ŵ�M��
					allnodes.push_back(nodes);
				}

			}
		}
		remove(uncompesspath1.c_str());
		_rmdir(uncompesspath.c_str());//ɾ��bin�ļ�

	}
	return allnodes;
}
vector<DefPoint> SelectNodes::getall()
{
	//�Ѿ���slpkģ���ļ���ѹ����process�ļ����У����������·����ȡ�ڵ�ҳ�����ļ�������ѹ
	//������ȡnodepages�ļ����������е�ѹ����������ѹ
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
				int nodescount = root["nodes"].size();//�ڵ�ҳ�����нڵ�����
				int j = 0;
				if (i == 0)//�ж��Ƿ����׽ڵ�ҳ����Ϊ��һҳ�к��и��ڵ�Ҫ�ų�
				{
					j = 1;
				}
				for (j; j < nodescount; j++)
				{
					//OGRPoint nodes;
					//nodes.setX(root["nodes"][j]["obb"]["center"][0].asDouble());
					//nodes.setY(root["nodes"][j]["obb"]["center"][1].asDouble());
					//nodes.setZ(root["nodes"][j]["obb"]["center"][2].asDouble());
					//nodes.setM(root["nodes"][j]["mesh"]["geometry"]["resource"].asDouble());//���ｫ�ڵ�ID�ŵ�M��
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
		_rmdir(uncompesspath.c_str());//ɾ��bin�ļ�

	}
	return allnodes;
}
