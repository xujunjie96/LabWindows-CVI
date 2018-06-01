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
#define  PANEL_NUMERIC_2                  2       /* control type: numeric, callback function: (none) */
#define  PANEL_NUMERIC                    3       /* control type: numeric, callback function: (none) */
#define  PANEL_QUITBUTTON                 4       /* control type: command, callback function: QuitCallback */
#define  PANEL_CMD_STOP                   5       /* control type: command, callback function: stop */
#define  PANEL_CMD_START                  6       /* control type: command, callback function: start */
#define  PANEL_TIMER                      7       /* control type: timer, callback function: timer */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK QuitCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK start(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK stop(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK timer(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
