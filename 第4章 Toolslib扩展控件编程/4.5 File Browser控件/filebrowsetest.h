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
#define  PANEL_FILEBROWSER                2       /* control type: tree, callback function: (none) */
#define  PANEL_PATH                       3       /* control type: string, callback function: path */
#define  PANEL_RING                       4       /* control type: ring, callback function: drivevol */
#define  PANEL_COMMANDBUTTON              5       /* control type: command, callback function: fileopen */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK drivevol(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK fileopen(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK panelcb(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK path(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
