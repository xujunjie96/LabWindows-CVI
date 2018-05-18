/**************************************************************************/
/* LabWindows/CVI User Interface Resource (UIR) Include File              */
/*                                                                        */
/* WARNING: Do not add to, delete from, or otherwise modify the contents  */
/*          of this include file.                                         */
/**************************************************************************/

#include <userint.h>

#ifdef __cplusplus
    extern "C" {
#endif

     /* Panels and Controls: */

#define  PANEL                            1
#define  PANEL_NUMERICGAUGE               2       /* control type: scale, callback function: (none) */
#define  PANEL_CMD_RS_QUIT                3       /* control type: command, callback function: rs232quit */
#define  PANEL_CMD_232_RECEIVE            4       /* control type: command, callback function: rs232receive */
#define  PANEL_TIMER                      5       /* control type: timer, callback function: timerweight */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK rs232quit(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK rs232receive(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK timerweight(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
