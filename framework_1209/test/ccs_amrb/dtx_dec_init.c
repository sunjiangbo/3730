/*
*****************************************************************************
*
*      GSM AMR-NB speech codec   R98   Version 7.5.0   March 2, 2001
*                                R99   Version 3.2.0                
*                                REL-4 Version 4.0.0                
*
*****************************************************************************
*/
#include "dtx_dec.h"
#include "dtx_dec_reset.h"
/*
**************************************************************************
*
*  Function    : dtx_dec_init
*
**************************************************************************
*/ 
int dtx_dec_init (dtx_decState *st)
{
   dtx_dec_reset(st);
   
   return 0;
}
 