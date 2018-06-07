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
#define  PANEL_GRAPHCURSOR                2       /* control type: graph, callback function: (none) */
#define  PANEL_CHECKBOX_COMPASS           3       /* control type: radioButton, callback function: index */
#define  PANEL_CHECKBOX_OPTION            4       /* control type: radioButton, callback function: index */
#define  PANEL_CHECKBOX_SELECTION         5       /* control type: radioButton, callback function: index */
#define  PANEL_CHECKBOX_COORDINMTE        6       /* control type: radioButton, callback function: index */
#define  PANEL_CHECKBOX_NAME              7       /* control type: radioButton, callback function: index */
#define  PANEL_CHECKBOX_CLOLR             8       /* control type: radioButton, callback function: index */
#define  PANEL_CHECKBOX_ZOOM              9       /* control type: radioButton, callback function: index */
#define  PANEL_CHECKBOX_INDEX             10      /* control type: radioButton, callback function: index */
#define  PANEL_DECORATION_2               11      /* control type: deco, callback function: (none) */
#define  PANEL_DECORATION                 12      /* control type: deco, callback function: (none) */
#define  PANEL_TEXTMSG_2                  13      /* control type: textMsg, callback function: (none) */
#define  PANEL_TEXTMSG                    14      /* control type: textMsg, callback function: (none) */
#define  PANEL_NUMERIC_NUMBER             15      /* control type: numeric, callback function: pos */
#define  PANEL_NUMERIC_POS                16      /* control type: numeric, callback function: pos */
#define  PANEL_RING_ALIGN                 17      /* control type: ring, callback function: pos */
#define  PANEL_QUITCALLBACK               18      /* control type: command, callback function: quitsys */
#define  PANEL_CMD_CLEAR                  19      /* control type: command, callback function: clear */
#define  PANEL_CMD_GEN                    20      /* control type: command, callback function: drawnoise */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK clear(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK drawnoise(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK index(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK pos(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK quitsys(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
