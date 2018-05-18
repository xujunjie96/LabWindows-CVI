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
#define  PANEL_GRAPH_VERTICAL             2       /* control type: graph, callback function: scrollbarCB */
#define  PANEL_DECORATION                 3       /* control type: deco, callback function: (none) */
#define  PANEL_COLORNUM_COLOR             4       /* control type: color, callback function: adjustvalue */
#define  PANEL_TOGGLEBUTTON_MODE          5       /* control type: textButton, callback function: adjustvalue */
#define  PANEL_COMMANDBUTTON              6       /* control type: command, callback function: QuitCallback */
#define  PANEL_NUMERIC_VERTICAL_VIEW      7       /* control type: numeric, callback function: adjustvalue */
#define  PANEL_NUMERIC_VERTICAL_WID       8       /* control type: numeric, callback function: adjustvalue */
#define  PANEL_NUMERIC_VERTICAL_HEI       9       /* control type: numeric, callback function: adjustvalue */
#define  PANEL_NUMERIC_VERTICAL_MAX       10      /* control type: numeric, callback function: adjustvalue */
#define  PANEL_NUMERIC_VERTICAL_VAL       11      /* control type: numeric, callback function: adjustvalue */
#define  PANEL_NUMERIC_VERTICAL_MIN       12      /* control type: numeric, callback function: adjustvalue */
#define  PANEL_TEXTMSG                    13      /* control type: textMsg, callback function: (none) */


     /* Control Arrays: */

#define  CTRLARRAY                        1

     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK adjustvalue(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK QuitCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK scrollbarCB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
