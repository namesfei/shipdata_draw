#include "stdafx.h"
#include "ShipStatusOffline.h"
#include "stdio.h"
#include "io.h"

#define _TOTAL_DATA_NUM_ 12002


CShipStatusOffline* CShipStatusOffline::_instance = 0;
CShipStatusOffline* CShipStatusOffline::Instance()
{
	if(_instance==0) _instance = new CShipStatusOffline;
	return _instance;
}

void CShipStatusOffline::ExitInstance()
{
	delete _instance;
}

void CShipStatusOffline::setDefaultFilePath(std::string strPath)
{
	_filePath = strPath;
	readStatusFiles();
}

bool CShipStatusOffline::getShipStatusBySeaLevelAndWind(int nSeaLevel, int nWindDir, std::vector<double>& t, std::vector<STATUSDATA3DOF>& shipStatus)
{
	bool bRVal = false;

	nSeaLevel = nSeaLevel -1;
	int n = nWindDir%15;
	int m = nWindDir/15;
	int nIdx = 0;

	if (n<8)
		nIdx = m *15;
	else
		nIdx = (m+1)* 15;

	if(m_AllDataStatus[nSeaLevel][nIdx] == false)
	{
		bRVal = false;
		return bRVal;
	}


	if (t.size()<_TOTAL_DATA_NUM_)
		t.resize(_TOTAL_DATA_NUM_);

	if(shipStatus.size()<_TOTAL_DATA_NUM_)
		shipStatus.resize(_TOTAL_DATA_NUM_);

	t = m_AllTime[nSeaLevel];
	shipStatus = m_AllData[nSeaLevel][nIdx];

	generateShipSpdData(shipStatus);
	return true;
}

CShipStatusOffline::CShipStatusOffline(void)
{
	//_filePath = std::string("E:\\shipStatus\\ShipStatusOffLine\\");
	_filePath = std::string("D:\\teenew\\git\\test2\\shipStatus\\ShipStatusOffLine\\");
	readStatusFiles();
}


CShipStatusOffline::~CShipStatusOffline(void)
{
}


void CShipStatusOffline::initAllGroup()
{
	for (int mm = 0; mm<4; mm++)
	{
		for (int i =0; i<360; i= i+15)
		{
			std::vector<STATUSDATA3DOF> data;
			for (int j =0; j <_TOTAL_DATA_NUM_; j++)
			{
				STATUSDATA3DOF status1;
				data.push_back(status1);

			}
			m_AllData[mm].insert(std::make_pair(i, data));
			m_AllDataStatus[mm].insert(std::make_pair(i, false));
		}	
	}

	for (int n = 0; n < 4; n++)
	{
		for (int j =0; j <_TOTAL_DATA_NUM_; j++)
		{
			double t = 0.0;
			m_AllTime[n].push_back(t);
		}
	}

}

void CShipStatusOffline::parseFile(std::string strPath)
{
	int nSealevel;
	int nWaveDir;
	std::string strStatus;
	std::string str(strPath);

	std::size_t npos = str.rfind("\\");
	str = std::string(str.begin()+npos+1, str.end());

	npos = str.rfind(".");
	std::string strName( str.begin(), str.begin()+npos);

	std::string str1 = std::string(str.begin()+10, str.begin()+13);
	nWaveDir = atol(str1.c_str());
	str1 = std::string(str.begin()+18, str.begin()+19);
	nSealevel = atol(str1.c_str());
	strStatus = std::string(str.begin()+19, str.begin()+npos);

	FILE *file;
	fopen_s(&file, str.c_str(), "r");

	if (file==nullptr)
		return;

	int nCount = 0;
	double data  = 0.0;

	if (strStatus.compare("t0")==0)
	{
		while( !feof(file) )
		{
			fscanf_s( file , "%lf" , &data );
			m_AllTime[nSealevel-1].at(nCount++) = data;
		}
	}
	else
	{
		/// Heave Pitch  Roll
		if (strStatus.compare("Heave")==0)
		{
			bool bRead = false;
			while( !feof(file) )
			{
				fscanf_s( file , "%lf" , &data );
				m_AllData[nSealevel-1][nWaveDir].at(nCount++).dHeave = data;
				bRead = true;
			}
			m_AllDataStatus[nSealevel-1][nWaveDir] = bRead;
		}
		else if (strStatus.compare("Roll")==0)
		{
			bool bRead = false;
			while( !feof(file) )
			{
				fscanf_s( file , "%lf" , &data );
				m_AllData[nSealevel-1][nWaveDir].at(nCount++).dRoll = data;
				bRead = true;
			}
			m_AllDataStatus[nSealevel-1][nWaveDir] = bRead;
		}
		else if (strStatus.compare("Pitch")==0)
		{
			bool bRead = false;
			while( !feof(file) )
			{
				fscanf_s( file , "%lf" , &data );
				m_AllData[nSealevel-1][nWaveDir].at(nCount++).dPitch = data;
				bRead = true;
			}
			m_AllDataStatus[nSealevel-1][nWaveDir] = bRead;
		}
	}
	fclose(file);	
	//generateShipStatusData();
}

void CShipStatusOffline::getFiles(std::string path, std::string fileName, std::vector<std::string>& files)
{
	//�ļ����  
	long   hFile = 0;
	//�ļ���Ϣ������һ���洢�ļ���Ϣ�Ľṹ��  
	struct _finddata_t fileinfo;

	//ȷ����β��"\\"
	std::size_t found = path.find_last_of("/\\")+1;
	if (found != path.size())
		path.append("\\");

	std::string p(path);//�ַ��������·��
	p+=fileName;


	////file check, only save the useful files.
	std::string strFileNameCheck("ztFn02");

	if ((hFile = _findfirst(p.c_str(), &fileinfo)) != -1)//�����ҳɹ��������
	{
		do
		{
			//�����Ŀ¼,����֮�����ļ����ڻ����ļ��У�  
			if ((fileinfo.attrib &  _A_SUBDIR))
			{
				//�ļ���������"."&&�ļ���������".."
				//.��ʾ��ǰĿ¼
				//..��ʾ��ǰĿ¼�ĸ�Ŀ¼
				//�ж�ʱ�����߶�Ҫ���ԣ���Ȼ�����޵ݹ�������ȥ�ˣ�
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
					getFiles(p.assign(path).append(fileinfo.name), fileName, files);
			}
			//�������,�����б�  
			else
			{
				std::string str(fileinfo.name);
				std::size_t nPos = str.find(strFileNameCheck);
				if (nPos==0)
					files.push_back(p.assign(path).append(fileinfo.name));
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		//_findclose������������
		_findclose(hFile);
	}
}


void CShipStatusOffline::readStatusFiles()
{
	getFiles(_filePath, "*.txt",  m_Allfiles);
	initAllGroup();
	std::vector<std::string>::iterator itr;
	for (itr = m_Allfiles.begin(); itr!= m_Allfiles.end(); itr++)
		parseFile(*itr);	
}

void CShipStatusOffline::generateShipSpdData(std::vector<STATUSDATA3DOF>& shipStatus)
{
	double dT = 0.1;
// 	for (int i = 0; i<4; i++)
	{
// 		std::map<int, std::vector<STATUSDATA3DOF>>::iterator itr;
// 		for (itr = m_AllData[i].begin(); itr != m_AllData[i].end(); itr++)
		{
			//std::vector<STATUSDATA3DOF>& shipStatus = itr->second;

			std::vector<STATUSDATA3DOF>::iterator it;
			for (it = shipStatus.begin(); it != shipStatus.end(); it++)
			{
				if (it == shipStatus.end()-1)
					continue;

				it->dHeaveSpd	= ((it+1)->dHeave - it->dHeave ) /dT;
				it->dPitchSpd	= ((it+1)->dPitch - it->dPitch ) /dT;
				it->dRollSpd	= ((it+1)->dRoll - it->dRoll ) /dT;
			}
		}
	}
}
