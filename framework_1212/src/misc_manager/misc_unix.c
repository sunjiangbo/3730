#include "misc_private.h"

static succeed_type misc_unix_deal( MISC_PRIVATE_HANDLE *phandle, UNIX_CMD_STRUCT *pcmd)
{
   switch(pcmd->cmd)	//根据不同的交互命令进行不同的处理
   {
       case 1:
	   break;
       default:
	   break;
   }
   return succeed_type_succeed;
}

succeed_type misc_unix(MISC_PRIVATE_HANDLE *phandle)
{
    unsigned char remotename[128];
    UNIX_CMD_STRUCT unix_rcv_cmd;

    memset(remotename, 0x00, 128);
    memset(&unix_rcv_cmd, 0x00, sizeof(UNIX_CMD_STRUCT));

    //1. recv the unix event
    if (UNIX_RECV( phandle->unix_fd, remotename, &unix_rcv_cmd) == succeed_type_failed )
    {
	SYS_ERROR("UNIX RECV failed.\r\n");
	return succeed_type_failed;
    }
    SYS_INFO("Rcv Event from %s in misc.\r\n", remotename); 
    
    //2. deal the receiving event.
    misc_unix_deal(phandle, &unix_rcv_cmd);
    return succeed_type_succeed;
}
