#pragma once
#include <string>
#include <vector>
#include <map>

typedef struct  _3DofStatus_
{
	_3DofStatus_()
	{
		dRoll		=	0.0;
		dPitch		=	0.0;
		dHeave		=	0.0;
		dRollSpd	=	0.0;
		dPitchSpd	=	0.0;
		dHeaveSpd	=	0.0;
		dRollAcc	=	0.0;
		dPitchAcc	=	0.0;
		dHeaveAcc	=	0.0;
	}
	double dRoll;
	double dPitch;
	double dHeave;
	double dRollSpd;
	double dPitchSpd;
	double dHeaveSpd;
	double dRollAcc;
	double dPitchAcc;
	double dHeaveAcc;
}STATUSDATA3DOF;


class CShipStatusOffline
{
public:
	CShipStatusOffline(void);
	~CShipStatusOffline(void);

private:
	static CShipStatusOffline* _instance;
public:
	static CShipStatusOffline* Instance();
	static void ExitInstance();

public:
	void setDefaultFilePath(std::string strPath);
	bool getShipStatusBySeaLevelAndWind(int nSeaLevel, int nWindDir, std::vector<double>& t, std::vector<STATUSDATA3DOF>& shipStatus);

private:
	std::map<int, std::vector<STATUSDATA3DOF>> m_AllData[4];   ///<degree, 3dofdata>    0-4 is the seawave level
	std::map<int, bool> m_AllDataStatus[4];   ///<degree, bool>    0-4 is the seawave level, to save the dataStatus if read correctly.
	std::vector<double> m_AllTime[4];
	std::vector<std::string> m_Allfiles;
	std::string _filePath;
private:
	void initAllGroup();
	void parseFile(std::string strPath);
	void getFiles(std::string path, std::string fileName, std::vector<std::string>& files);
	void readStatusFiles();
	void generateShipSpdData(std::vector<STATUSDATA3DOF>& shipStatus);
};

