#ifndef _PARAM_MGR_H_
#define _PARAM_MGR_H_


#ifdef _cplusplus
extern "C" {
#endif
	
#include <queue>
#include <string.h>
using namespace std;

typedef struct _FileNameNode_t
{
    char   v_name[128];
}FileNameNode_T;//��������Ԫ��

typedef  queue<FileNameNode_T> FileNameList_T;

#include "TypeDefs.h"
#include "CmdDef.h"
#include "SystemConf.h"
#include "AreaConf.h"
#include "MediaConf.h"
#include "Ptz.h"
//#include "AppSV/APPInterface.h"
#include "PtzControl/PtzControlInterface.h"

//�������б���ͨ���㲥ɨ�赽�ķ�������Ϣ��
typedef  struct _SERVER_LIST
{
	unsigned char ipaddr[32];//������IP��ַ
	unsigned char servername[128];//����������
	CAM_STATE cam_state;//ʶ����״̬
	unsigned int flagvalid;//��������Ч��־
}SERVER_LIST;


//�ͷ�������ز���
typedef  struct  _CENTER_PTHREAD_MAIN_PARA
{
	unsigned  char  picfar_name[128];//Զ����Ƭ����
	unsigned  char  picnear_name[128];//������Ƭ����
	unsigned  int   flag_valid;      //�Ƿ���Ч��־
	unsigned  int   savetime;       //����Ϊ��λ
}CENTER_PTHREAD_MAIN_PARA;//�����Ľ����߳��������̶�̬��������

//ʶ�����������洢��ز���
typedef  struct  _GLOBAL_FLASH
{
	PTZ_PARA  ptzpara;
	VIDEO_PARA videopara;
	ALG_PARA algpara;
#if 1
	ALG_QUAD_PARA algquadpara[32];//�ܹ�64������
	ALG_AREA_PARA  algareapara[8];
	ALG_LINE_PARA  alglinepara[4];
	ALG_COUNT_PARA  algcountpara[4];
	ALG_ENTER_PARA  algenterpara[4];
	ALG_OUT_PARA algoutpara[4];
//	ALG_STOP_PARA  algstoppara[2];
	ALG_LOST_PARA  alglostpara[2];
	ALG_DIRECT_PARA  algdirectpara[4];
	ALG_DETECT_PARA  algdetectpara[4];
	ALG_PEOPLEDENSE_PARA algpeopledectpara[4];  
	ALG_CLUSTERDETE_PARA algclusterdectpara[4];
	ALG_MOTIONHISTORY_PARA algmotionhistorypara[4];
	ALG_HOVERDETE_PARA alghoverdectpara[4];
  	ALG_ALARMLINE_PARA algalarmlinepara[4]; //�����������㷨   add by hzc 2012-05-20
	ALG_FINDBAG_PARA algfindbagpara[4]; //���������㷨		add by hzc 2012-05-20
	ALG_RUNNINGOBJ_PARA algrunningpara[4]; //�����㷨���		add by hzc 2012-05-20

	SYS_CONFIG_PARA  sysconfigpara;
	SYS_STORAGE_PARA  sysstoragepara;
#endif
}GLOBAL_FLASH;

typedef struct _GLOBAL_FLASH_INI_GROUP
{
	unsigned int bPtzPara:1;
	unsigned int bVideoPara:1;
	unsigned int bAlgPara:1;
	unsigned int bAlgQuadPara:1;
	unsigned int bAlgAreaPara:1;
	unsigned int bAlgLinePara:1;
	unsigned int bAlgCountPara:1;
	unsigned int bAlgEnterPara:1;
	unsigned int bAlgOutPara:1;
//	unsigned int bAlgStopPara:1;
	unsigned int bAlgLostPara:1;
	unsigned int bAlgDirectPara:1;
	unsigned int bAlgDetectPara:1;
	unsigned int bAlgPeopleDensePara:1;
	unsigned int bAlgPeopleClusterPara:1;
	unsigned int bAlgPeopleMotionPara:1;
	unsigned int bAlgHoverPara:1;
	unsigned int bAlgAlarmLinePara:1;
	unsigned int bAlgFindBagPara:1;
	unsigned int bAlgRunningPara:1;
	unsigned int bAlgSysConfigPara:1;
	unsigned int bAlgStoragePara:1;
}GLOBAL_FLASH_INI_GROUP;

//ʶ���������� ͨ�Žṹ
typedef struct _SOCKET_STRUCT_T
{
	int socket_it;//�׽���
	char socket_cip[32];//ip��ַ
	int socket_cport;//�˿ں�
}SOCKET_STRUCT_T;

typedef  struct _PTZ_CTL_HANDLE
{
	PtzControlInterface *ptz_Interface;	//��̨���ƾ��
	bool                 ptz_initd;     //�Ƿ�����
}PTZ_CTL_HANDLE;


//ʶ���������� ȫ�ֱ���
typedef  struct  _GLOBAL_VARIABLE
{
	GLOBAL_FLASH  globalflash; //�����Ǵ���ڲ����ļ��е�ϵͳ����
	SOCKET_STRUCT_T  center_tcpsocket;     //���������ӵ�TCP�׽��־��
	SOCKET_STRUCT_T  center_udpsocket;     //���������ӵ�UDP�׽��־��
	SOCKET_STRUCT_T  client_tcpsocket;     //�Ϳͻ������ӵ�TCP�׽��־��
	SOCKET_STRUCT_T  client_udpsocket;     //�Ϳͻ������ӵ�UDP�׽��־��
	//CENTER_PTHREAD_MAIN_PARA  center_pthread_main_para[100];//���Ԥ��100��������¼���壬�����͵����ķ�����
	//unsigned  char  *ptrrawdata;        //ָ��ԭʼ�ɼ������ָ��
	//CRITICAL_SECTION csFileNameList;	//�����̺����Ľ����߳�֮���ͬ���� ���Ʊ����ļ����еĻ�����
	//Pthread_mutex  pthread_center��       //�����̺����Ľ����߳�֮���ͬ����
	//Pthread_mutex  pthread_client��       //�����̺Ϳͻ����߳�֮���ͬ����
	//Video_Encoder  h264_handle;     //H264���
	//VCA_HANDLE  *pvca_handle��      //VCA������Ƿ����ֲ�ͬ���㷨��Ҫ������
	PTZ_CTL_HANDLE ptz_ctlhandle;	//��̨���ƾ��
	//ALARM_HANDLE *alarm_handle��
	unsigned  int  storage_alarmflag;    //�洢������־
	unsigned  int  usedtime;       //�Ƿ���Ϊ����ʱ�仹�ǰ�װʱ�䣿��Ҫ��̬����
}GLOBAL_VARIABLE;


//�����׽�����ز���
typedef  struct  _SERVER_SOCKET
{
	int  tcp_socketfd;//�����������ӵ�TCP�׽���
	int  udp_socketfd;//������������UDP�׽���
	int  connectindex;//��serverlist�е��ĸ����ڽ������ӣ����һ����û�У���ֵΪ-1��
}SERVER_SOCKET;


//������ز���
typedef  struct  _OTHER_PARA
{
	////
}OTHER_PARA;

typedef   struct   _GLOBAL_CLIENT_PARA
{
    unsigned  int  servercount;//��Ч����������Ŀ
	SERVER_LIST serverlist[1024];
	GLOBAL_FLASH globalflashpara;
	SERVER_SOCKET socketpara;
	OTHER_PARA otherpara;
}GLOBAL_CLIENT_PARA;

// typedef struct ParamNode_T
// {
//     string   v_name;
// 	string   v_type;
//     int		 v_len;
//     long int v_offset;
// }ParamNode_T;//��������Ԫ��

// class CParamMgr
// {
// 	
// private:
// 	static HANDLE						m_hMapFile;				//ӳ�䵽�����ڴ���
// 	static LPTSTR						m_psMapAddr;			//ӳ�䵽�����ڴ浽�����ڴ�ĵ�ַ
// 	static CRITICAL_SECTION				m_stSection;			//�ڴ���ʹؼ��� д����
// 	static unsigned long int			m_lMemSize;				//�ڴ��С
// 	static unsigned long int			m_lFixedParamSize;		//�̶�������С ��Ҫ�������Ϣ
// 	static unsigned long int			m_lCurOffset;			//��ǰƫ�ƴ� 
// 	static vector<ParamNode_T>			m_vParam;				//��������
// 	
// public:
// 	CParamMgr();
// 	CParamMgr(long int MemSize);
// 	virtual ~CParamMgr();
// 	static bool Param_DownLoad();				//���������浽�ļ�
// 	static bool Param_UpLoad();					//�������ϴ����ڴ���
// 	static bool Param_MemInit();				//�������ڴ�����ʼ��
// 	static bool Param_MemDestroy();				//�������ڴ�����
// 	//value ΪNULL��û�г�ʼֵ
// 	static bool Param_Define(string name, string type, int len, int flag, void *value=NULL);
// 	static bool Param_Set(string name, void *value=NULL);
// 	static void* Param_Addr_Get(string name);
// 	static bool Param_Get(string name, void *value=NULL);
// };
/************************************************************************/
/* ȫ����                                                                     */
/************************************************************************/
extern GLOBAL_FLASH g_stGlobal_Flash;
extern GLOBAL_VARIABLE g_stGlobal_Variable;//����ʱʹ�õ��ļ�
/*extern CParamMgr ParamMgrInstance;*/
//extern CRITICAL_SECTION g_csGlobal_Variable_Section;
extern FileNameList_T g_FileNameList;//����ͼƬһ������ ���ȷ��� ����ʧ�ܼ����������
extern FileNameList_T g_FileNameListReserved;//����ͼƬ�������� ��һ������Ϊ��ʱ���з��� ����ʧ������

/************************************************************************/
/* ��������                                                                     */
/************************************************************************/
//ֱ�ӶԲ�����ȫ�ֱ������в���
bool FlashParam_Init();//��ʼ���ؼ�������
bool FlashParam_UpLoad();//���ļ��е����ݿ�����ȫ�ֱ�����
bool FlashParam_DownLoad();//��ȫ�ֱ����е����ݱ��ֵ����ļ���


bool FlashParam_SetPtzPara(PTZ_PARA &para);//����Ptz����
bool FlashParam_SetVideoPara(VIDEO_PARA &para);//����Ptz����
bool FlashParam_SetAlgPara(ALG_PARA &para);//����Alg����
bool FlashParam_SetAlgParaConf(ALG_PARA_CONF_UINT *para,UINT num);//����Alg��������
bool FlashParam_SetAlgQuadPara(ALG_QUAD_PARA *para,UINT num);//����AlgQuad����
bool FlashParam_SetAlgAreaPara(ALG_AREA_PARA *para,UINT num);//����AlgArea����
bool FlashParam_SetAlgLinePara(ALG_LINE_PARA *para,UINT num);//����AlgLine����
bool FlashParam_SetAlgCountPara(ALG_COUNT_PARA *para,UINT num);//����AlgCount����
bool FlashParam_SetAlgEnterPara(ALG_ENTER_PARA *para,UINT num);//����AlgEnter����
bool FlashParam_SetAlgOutPara(ALG_OUT_PARA *para,UINT num);//����AlgOut����
//BOOL FlashParam_SetAlgStopPara(ALG_STOP_PARA *para,UINT num);//����AlgStop����
bool FlashParam_SetAlgLostPara(ALG_LOST_PARA *para,UINT num);//����AlgLost����
bool FlashParam_SetAlgDirectPara(ALG_DIRECT_PARA *para,UINT num);//����AlgDirect����
bool FlashParam_SetAlgDetectPara(ALG_DETECT_PARA *para,UINT num);//����AlgDetect����
bool FlashParam_SetAlgPeopleDensePara(ALG_PEOPLEDENSE_PARA *para,UINT num);//����AlgPeopleDete����
bool FlashParam_SetAlgClusterDetePara(ALG_CLUSTERDETE_PARA *para,UINT num);//����AlgClusterDete����
bool FlashParam_SetAlgMotionHistoryPara(ALG_MOTIONHISTORY_PARA *para,UINT num);//����AlgMotionHistory����
bool FlashParam_SetAlgHoverDetePara(ALG_HOVERDETE_PARA *para,UINT num);//����AlgHoverDete����
bool FlashParam_SetAlgFindbagPara(ALG_FINDBAG_PARA *para,UINT num);//����AlgFindbag����
bool FlashParam_SetAlgAlarmLinePara(ALG_ALARMLINE_PARA *para,UINT num);//�������߾����߲���
bool FlashParam_SetAlgRunningPara(ALG_RUNNINGOBJ_PARA *para,UINT num);//���ñ��ܲ���

bool FlashParam_SetSysStoragePara(SYS_STORAGE_PARA &para);//����SysStorage����

#if 0
#endif

bool FlashParam_SetSysConfigPara(SYS_CONFIG_PARA &para);//����SysConfig����

bool ParseINIFileToXML(unsigned int flag,string fname);
//�����ϵͳ������Ϣ
//��ϵͳע��ϵͳ���� ����ʱʹ�� ��Ҫ����
// #define PARAM_DEFINE(name, type, value) \
// 	do{									\
// 		ParamMgrInstance.Param_Define((name), #type, (sizeof(##type##)),1,##((type *)value));	\
// 	}while(0);
// 
// //��ϵͳע���ϵͳ���� ����ʱʹ�� ����Ҫ����
// #define PARAM_DEFINE_RUN(name, type, value) \
// 	do{									\
// 		ParamMgrInstance.Param_Define((name), #type, (sizeof(##type##)),0,##((type *)value));	\
// 	}while(0);
// 
// //��ȡ�ض�����ֵ
// #define PARAM_GET(name, value) \
// 	do{									\
// 		ParamMgrInstance.Param_Get((name), (value));	\
// 	}while(0);
// 
// //��ȡ�ض�����ָ��
// #define PARAM_ADDR_GET(name) ParamMgrInstance.Param_Addr_Get((name))
// 
// //�����ض�����
// #define PARAM_SET(name, value) \
// 	do{									\
// 		ParamMgrInstance.Param_Set((name), (value));	\
// 	}while(0);
// 
// //�������ļ���ȡĬ�ϲ������ڴ���
// #define PARAM_UPLOAD() \
// 	do{									\
// 		ParamMgrInstance.Param_UpLoad();	\
// 	}while(0);
// 
// //���ڴ��еĲ������浽�ļ���
// #define PARAM_DOWNLOAD() \
// 	do{									\
// 		ParamMgrInstance.Param_DownLoad();	\
// 	}while(0);

#ifdef _cplusplus
}
#endif

#endif // _PARAM_MGR_H_