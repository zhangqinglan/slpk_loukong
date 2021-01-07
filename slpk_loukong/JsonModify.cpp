#pragma warning(disable:4996)
#include "JsonModify.h"
JsonModify::JsonModify()
{

}
void JsonModify::modify3dScene()
{
	//修改slpk中的3dScenelayer.json文件中的
	ZipHelper uncompessjson;
	uncompessjson.exeUnCompress("process", "process/3dSceneLayer.json.gz");
	Json::Reader reader;
	Json::Value root;
	Json::Value delete1;
	ifstream f;
	f.open("process/3dSceneLayer.json", ios::binary);
	if (f.is_open())
	{
		bool parse_ok = reader.parse(f, root);
		f.close();
		remove("process/3dSceneLayer.json");
		if (parse_ok)
		{
			if (root["geometryDefinitions"][0]["geometryBuffers"].size() != 1)
			{
				//root.removeIndex(1, &root["geometryDefinitions"][0]["geometryBuffers"]);
				root["geometryDefinitions"][0]["geometryBuffers"].removeIndex(1, &delete1);
			}
			Json::StyledWriter sw;
			//输出到文件  
			ofstream os;
			os.open("process/3dSceneLayer.json", std::ios::trunc);
			os << sw.write(root);
			os.close();


		}
	}
	remove("process/3dSceneLayer.json.gz");
	//压缩3dSceneLayer.json
	uncompessjson.exeCompress("process/3dSceneLayer.json", "process/3dSceneLayer.json.gz");
	//删除3dSceneLayer.json
	remove("process/3dSceneLayer.json");

}

JsonModify::~JsonModify()
{

}