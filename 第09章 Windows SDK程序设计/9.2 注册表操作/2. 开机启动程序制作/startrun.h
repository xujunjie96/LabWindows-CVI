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
#define  PANEL_CMD_RUN                    2       /* control type: command, callback function: run */
#define  PANEL_CMD_UNRUN                  3       /* control type: command, callback function: unrun */
#define  PANEL_DECORATION                 4       /* control type: deco, callback function: (none) */
#define  PANEL_COMMANDBUTTON              5       /* control type: command, callback function: QuitCallback */
#define  PANEL_TEXTMSG                    6       /* control type: textMsg, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK QuitCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK run(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK unrun(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
