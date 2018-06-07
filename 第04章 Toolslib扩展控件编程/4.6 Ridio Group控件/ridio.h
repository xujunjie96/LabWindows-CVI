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
#define  PANEL_RADIOGROUP                 2       /* control type: tree, callback function: help */
#define  PANEL_TEXTMSG                    3       /* control type: textMsg, callback function: (none) */
#define  PANEL_DECORATION                 4       /* control type: deco, callback function: (none) */


     /* Control Arrays: */

#define  CTRLARRAY                        1

     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK help(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK panelcb(int panel, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
