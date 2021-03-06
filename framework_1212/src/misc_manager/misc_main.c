#include "misc_private.h"

MISC_PRIVATE_HANDLE global_misc_private_handle;
int IsMiscSysQuit = 0;
void sig_sigint_proc(int sig);
#define WDQ_VERSION
static void misc_poll_init(MISC_PRIVATE_HANDLE *phandle)
{
	memset(&(phandle->polltimeout), 0x00, sizeof(struct pollfd) * MISC_POLL_COUNT_MAX );
	phandle->polltimeout[0].fd = phandle->unix_fd;
	phandle->polltimeout[0].events = POLLIN;

	phandle->polltimeout[1].fd = phandle->pgps_obj->gps_fd;
	phandle->polltimeout[1].events = POLLIN;

	phandle->active_fdcount = 2;

}
static succeed_type misc_init(MISC_PRIVATE_HANDLE *phandle)
{
	SIGNAL_STRUCT_T signal;
	net_param *plocalnet = NULL;
	if (NULL == phandle)
	{
		SYS_ERROR("in misc_init phandle is NULL.\r\n");
		return succeed_type_failed;
	}
	//1. 驱动句柄初始化
	phandle->gbshm_handle = GBSHM_INIT();
	if ( NULL == phandle->gbshm_handle)
	{
		SYS_ERROR("GBSHM_INIT failed.\r\n");
		return succeed_type_failed;
	}
	phandle->pgpio_obj = GPIO_INIT();
	if ( NULL == phandle->pgpio_obj )
	{
		SYS_ERROR("GPIO_INIT failed.\r\n");
		return succeed_type_failed;
	}
	phandle->pgps_obj = GPS_INIT();
	if ( NULL == phandle->pgps_obj )
	{
		SYS_ERROR("GPS_INIT failed.\r\n");
		return succeed_type_failed;
	}


	//2. 创建本进程绑定的UNIX文件，返回值为unix_fd
	if (UNIX_CREATE(UNIXFILE_SOCKET_MISC, &(phandle->unix_fd), 0) == succeed_type_failed )
	{
		SYS_ERROR("UNIX_CREATE %s failed.\r\n", UNIXFILE_SOCKET_MISC);
		return succeed_type_failed;
	}
	plocalnet = &(phandle->localnet);
    GBSHM_PARA_GET(phandle->gbshm_handle, PARA_CMD_SYSTEM_NET_PARAM , plocalnet , sizeof(phandle->localnet));
	{
		unsigned char systemcmd[256];
		memset(systemcmd, 0, 256);
		sprintf(systemcmd, "ifconfig eth0 gw %s ipaddr %s netmask %s ", plocalnet->ipgateway, plocalnet->ipaddr, plocalnet->ipmask);
		printf("systemcmd ======== %s.\r\n", systemcmd);
		system(systemcmd);
		system("ifconfig eth0");
		system("/opt/install/bin/boaserver -c /opt/install &");
		sleep(1);
		system("/opt/install/bin/rtsp_transfer &");
		sleep(1);
		system("/opt/install/bin/core &");
		sleep(1);
		system("/opt/install/bin/client_pc &");
	}
	//3. 本进程模块的poll初始化函数
	misc_poll_init(phandle);

	//信号量初始化操作
	memset(&signal, 0x00, sizeof(signal));
	signal.signo[0] = SIGINT;
	signal.sig_phandle[0] = sig_sigint_proc;
	SIGNAL_INIT(&signal, 1);

	return succeed_type_succeed;
}

void sig_sigint_proc(int sig)
{
	SYS_WARNING("Misc Rcv SigNo = %d",sig);
	IsMiscSysQuit = 1;
}

static succeed_type misc_exit(MISC_PRIVATE_HANDLE *phandle)
{
	if (NULL == phandle)
	{
		SYS_ERROR("in misc_exit phandle is NULL.\r\n");
		return succeed_type_failed;
	}
	GBSHM_DESTROY(phandle->gbshm_handle);

	if (UNIX_DESTROY(UNIXFILE_SOCKET_MISC, phandle->unix_fd) == succeed_type_failed )
	{
		SYS_ERROR("UNIX_CREATE %s failed.\r\n", UNIXFILE_SOCKET_MISC);
		return succeed_type_failed;
	}
	return succeed_type_succeed;
}
#define TEST_IP "www.baidu.com"

static void pingnet(MISC_PRIVATE_HANDLE *phandle)
{
	unsigned char cmd[128];
	int iping_ret = -1;
	memset(cmd, 0x00, 128);
	sprintf(cmd,"ping -c 1 %s >/dev/null",TEST_IP);

	{
		iping_ret = system(cmd);
		if( 0 == iping_ret) // 0x000-0x3FF
		{
			//GPIO_SETOUTPUT(phandle->pgpio_obj, GPIO_OUTPUT_3G_LED_GREEN);
			GPIO_3G_GREEN_ON(phandle->pgpio_obj);
			SYS_WARNING("3g normal!!\r\n");
		}
		else
		{
			GPIO_3G_GREEN_OFF(phandle->pgpio_obj);
			SYS_WARNING("3g unnormal!!\r\n");
		}
	}
}

void pthread_func(void* phandle)
{
	int fd;
//	system("/opt/install/sbin/3g_reset &");
	sleep(20);
	while(0 == IsMiscSysQuit)
	{
		fd=open("/var/log/pppfile",O_RDONLY);
		if(fd==-1)
		{	
			system("killall pppd");
			sleep(5);
			system("pppd call ppp0 2 >/dev/null &");
			SYS_WARNING("system pppd!!\r\n");
			sleep(20);
			pingnet(phandle);
		}
		else
		{
			pingnet(phandle);
			close(fd);
			sleep(8);
		}	
		sleep(10);
	}
	pthread_exit(NULL);	
}
int main(int argc, char **argv)
{
	pthread_t pthreadCheck_t;
	memset(&global_misc_private_handle, 0x00, sizeof(global_misc_private_handle));
	misc_init(&global_misc_private_handle);	
	SYS_INFO("Enter misc_manager func.\r\n");
#ifndef WDQ_VERSION 
	//PPPOE Thread:
	if(pthread_create(&pthreadCheck_t,NULL,pthread_func,&global_misc_private_handle) !=0)
	{
		SYS_ERROR("Create PPPThread Failed.\r\n");
	}
	else
	{
		SYS_INFO("PPPThread Start.\r\n");
	}
#endif
	while(0 == IsMiscSysQuit )
	{
		if ( poll( &(global_misc_private_handle.polltimeout), global_misc_private_handle.active_fdcount , -1 ) > 0 )
		{
			SYS_INFO("POLL event found.\r\n");
			if ( global_misc_private_handle.polltimeout[0].revents )
			{
				//do UNIX recv event.
				misc_unix(&global_misc_private_handle);
			}
			if ( global_misc_private_handle.polltimeout[1].revents )
			{
			    misc_gps(&global_misc_private_handle);
			}
			misc_poll_init(&global_misc_private_handle);
		}
	}
	pthread_join(pthreadCheck_t, NULL);
	misc_exit(&global_misc_private_handle);
	SYS_WARNING("Misc Quit!!\r\n");
	return 0;
}

