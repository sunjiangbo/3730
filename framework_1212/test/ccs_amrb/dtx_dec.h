/*
*****************************************************************************
*
*      GSM AMR-NB speech codec   R98   Version 7.5.0   March 2, 2001
*                                R99   Version 3.2.0                
*                                REL-4 Version 4.0.0                
*
*****************************************************************************
*/
#ifndef dtx_dec_h
#define dtx_dec_h "$Id $" 
 
#include "typedef.h"
#include "dtx_def.h"
#include "d_plsf.h"
#include "gc_pred.h"
#include "frame.h"
#include "cb_gain_average.h"
/*
*****************************************************************************
*                         LOCAL VARIABLES AND TABLES
*****************************************************************************
*/
enum DTXStateType {SPEECH = 0, DTX, DTX_MUTE};

#define DTX_MAX_EMPTY_THRESH 50

/*
*****************************************************************************
*                         DEFINITION OF DATA TYPES
*****************************************************************************
*/

typedef struct {
   Word16 since_last_sid;
   Word16 true_sid_period_inv;
   Word16 log_en;
   Word16 old_log_en;
   Word32 L_pn_seed_rx; 
   Word16 lsp[M];
   Word16 lsp_old[M]; 
   
   Word16 lsf_hist[M*DTX_HIST_SIZE];
   Word16 lsf_hist_ptr;
   Word16 lsf_hist_mean[M*DTX_HIST_SIZE]; 
   Word16 log_pg_mean;
   Word16 log_en_hist[DTX_HIST_SIZE];
   Word16 log_en_hist_ptr;

   Word16 log_en_adjust;

   Word16 dtxHangoverCount;
   Word16 decAnaElapsedCount;

   Word16 sid_frame;       
   Word16 valid_data;          
   Word16 dtxHangoverAdded;
 
   enum DTXStateType dtxGlobalState;     /* contains previous state */
                                         /* updated in main decoder */ 

   Word16 data_updated;      /* marker to know if CNI data is ever renewed */ 

} dtx_decState;

 
/*
**************************************************************************
*
*  Function    : dtx_dec
*  Purpose     :
*  Description :
*                
**************************************************************************
*/
int dtx_dec(
   dtx_decState *st,                /* i/o : State struct                    */
   Word16 mem_syn[],                /* i/o : AMR decoder state               */
   D_plsfState* lsfState,           /* i/o : decoder lsf states              */
   gc_predState* predState,         /* i/o : prediction states               */
   Cb_gain_averageState* averState, /* i/o : CB gain average states          */
   enum DTXStateType new_state,     /* i   : new DTX state                   */    
   enum Mode mode,                  /* i   : AMR mode                        */
   Word16 parm[],                   /* i   : Vector of synthesis parameters  */
   Word16 synth[],                  /* o   : synthesised speech              */
   Word16 A_t[]                     /* o   : decoded LP filter in 4 subframes*/
   );


#endif