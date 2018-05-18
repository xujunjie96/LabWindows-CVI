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

#define  PANEL                            1       /* callback function: panelcb */
#define  PANEL_BALL                       2       /* control type: radioButton, callback function: (none) */
#define  PANEL_TIMER                      3       /* control type: timer, callback function: timer */
#define  PANEL_BAR                        4       /* control type: deco, callback function: (none) */

#define  PANEL_SET                        2
#define  PANEL_SET_COMMANDBUTTON_2        2       /* control type: command, callback function: exitsys */
#define  PANEL_SET_COMMANDBUTTON          3       /* control type: command, callback function: ok */
#define  PANEL_SET_STRING                 4       /* control type: string, callback function: (none) */
#define  PANEL_SET_TEXTMSG                5       /* control type: textMsg, callback function: (none) */
#define  PANEL_SET_NUMERIC                6       /* control type: numeric, callback function: (none) */
#define  PANEL_SET_PICTURE                7       /* control type: picture, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK exitsys(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ok(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK panelcb(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK timer(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
