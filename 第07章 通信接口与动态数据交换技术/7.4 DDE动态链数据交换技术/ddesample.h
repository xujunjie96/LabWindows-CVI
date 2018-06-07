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
#define  PANEL_CMD_LINK                   2       /* control type: command, callback function: linkexcel */
#define  PANEL_CMD_START                  3       /* control type: command, callback function: startexcel */
#define  PANEL_DECORATION                 4       /* control type: deco, callback function: (none) */
#define  PANEL_RINGSLIDE                  5       /* control type: slide, callback function: wavesignal */
#define  PANEL_TEXTMSG                    6       /* control type: textMsg, callback function: (none) */
#define  PANEL_DECORATION_2               7       /* control type: deco, callback function: (none) */
#define  PANEL_CELLVALUE                  8       /* control type: numeric, callback function: (none) */
#define  PANEL_TABLE                      9       /* control type: table, callback function: (none) */
#define  PANEL_TEXTMSG_2                  10      /* control type: textMsg, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK linkexcel(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK panelCB(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK startexcel(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK wavesignal(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
