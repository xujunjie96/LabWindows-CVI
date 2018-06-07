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
#define  PANEL_SPLITTER_VER_RIGHT         2       /* control type: splitter, callback function: (none) */
#define  PANEL_SPLITTER_VER_LEFT          3       /* control type: splitter, callback function: (none) */
#define  PANEL_PICTURE                    4       /* control type: picture, callback function: (none) */
#define  PANEL_SPLITTER_HOR_TOP           5       /* control type: splitter, callback function: (none) */
#define  PANEL_SPLITTER_HOR_BOTTOM        6       /* control type: splitter, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK panelCB(int panel, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
