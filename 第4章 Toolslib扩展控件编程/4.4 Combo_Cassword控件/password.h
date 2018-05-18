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

#define  PANEL                            1       /* callback function: panelCB */
#define  PANEL_COMBO                      2       /* control type: string, callback function: (none) */
#define  PANEL_PASSWORD                   3       /* control type: string, callback function: (none) */
#define  PANEL_CMD_VIEW                   4       /* control type: command, callback function: passwoedview */
#define  PANEL_CMD_CLEAR                  5       /* control type: command, callback function: cancel */
#define  PANEL_CMD_OK                     6       /* control type: command, callback function: ok */
#define  PANEL_TIMER                      7       /* control type: timer, callback function: timer */

#define  PANEL_2                          2
#define  PANEL_2_COMMANDBUTTON            2       /* control type: command, callback function: hidepanel */
#define  PANEL_2_TEXTMSG                  3       /* control type: textMsg, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK cancel(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK hidepanel(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ok(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK panelCB(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK passwoedview(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK timer(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
