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
#define  PANEL_NUMERIC_Z                  2       /* control type: numeric, callback function: (none) */
#define  PANEL_NUMERIC_Y                  3       /* control type: numeric, callback function: (none) */
#define  PANEL_NUMERIC_X                  4       /* control type: numeric, callback function: (none) */
#define  PANEL_DECORATION                 5       /* control type: deco, callback function: (none) */
#define  PANEL_DECORATION_2               6       /* control type: deco, callback function: (none) */
#define  PANEL_BINARYSWITCH               7       /* control type: binary, callback function: (none) */
#define  PANEL_QUITBUTTON                 8       /* control type: command, callback function: QuitCallback */
#define  PANEL_CMD_POPUP                  9       /* control type: command, callback function: popup */
#define  PANEL_CMD_CALC                   10      /* control type: command, callback function: calc */
#define  PANEL_TEXTMSG                    11      /* control type: textMsg, callback function: (none) */
#define  PANEL_TEXTMSG_2                  12      /* control type: textMsg, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK calc(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK popup(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK QuitCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
