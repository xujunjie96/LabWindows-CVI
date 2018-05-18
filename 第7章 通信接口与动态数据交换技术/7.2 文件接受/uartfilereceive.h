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
#define  PANEL_STRING_2                   2       /* control type: string, callback function: (none) */
#define  PANEL_STRING                     3       /* control type: string, callback function: (none) */
#define  PANEL_DECORATION                 4       /* control type: deco, callback function: (none) */
#define  PANEL_COMMANDBUTTON              5       /* control type: command, callback function: filesel */
#define  PANEL_OKBUTTON_2                 6       /* control type: command, callback function: receivefile */
#define  PANEL_OKBUTTON                   7       /* control type: command, callback function: receivefilename */
#define  PANEL_DECORATION_2               8       /* control type: deco, callback function: (none) */
#define  PANEL_TEXTMSG                    9       /* control type: textMsg, callback function: (none) */
#define  PANEL_QUITBUTTON                 10      /* control type: command, callback function: Quitcallback */
#define  PANEL_TEXTMSG_2                  11      /* control type: textMsg, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK filesel(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Quitcallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK receivefile(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK receivefilename(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
