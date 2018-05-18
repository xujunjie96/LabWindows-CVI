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
#define  PANEL_NUMERICTHERM               2       /* control type: scale, callback function: (none) */
#define  PANEL_NUMERIC                    3       /* control type: numeric, callback function: (none) */
#define  PANEL_NUMERIC_2                  4       /* control type: numeric, callback function: (none) */
#define  PANEL_BINARYSWITCH               5       /* control type: binary, callback function: Acquire */
#define  PANEL_LED                        6       /* control type: LED, callback function: (none) */
#define  PANEL_COMMANDBUTTON              7       /* control type: command, callback function: Quit */
#define  PANEL_STRIPCHART                 8       /* control type: strip, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK Acquire(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Quit(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
