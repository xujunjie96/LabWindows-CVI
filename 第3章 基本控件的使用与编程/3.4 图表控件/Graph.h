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
#define  PANEL_GRAPH                      2       /* control type: graph, callback function: (none) */
#define  PANEL_DIGGRAPH                   3       /* control type: digitalGraph, callback function: (none) */
#define  PANEL_COMMANDBUTTON              4       /* control type: command, callback function: QuitCallback */
#define  PANEL_CMD_DIGITALGRAPH           5       /* control type: command, callback function: digitalgraph */
#define  PANEL_CMD_STRIPCHART             6       /* control type: command, callback function: stripchart */
#define  PANEL_CMD_GRAPH                  7       /* control type: command, callback function: graph */
#define  PANEL_STRIPCHART                 8       /* control type: strip, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK digitalgraph(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK graph(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK QuitCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK stripchart(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
