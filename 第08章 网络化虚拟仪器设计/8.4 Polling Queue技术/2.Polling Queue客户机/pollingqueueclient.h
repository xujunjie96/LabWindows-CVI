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
#define  PANEL_TEXTBOX                    2       /* control type: textBox, callback function: (none) */
#define  PANEL_CMD_CONNECT                3       /* control type: command, callback function: connect */
#define  PANEL_STRIPCHART                 4       /* control type: strip, callback function: (none) */
#define  PANEL_CMD_RECEIVE                5       /* control type: command, callback function: receive */
#define  PANEL_TIMER                      6       /* control type: timer, callback function: timer */
#define  PANEL_STRING                     7       /* control type: string, callback function: (none) */
#define  PANEL_NUMERIC_PACKETS            8       /* control type: numeric, callback function: (none) */
#define  PANEL_NUMERIC_BYTES              9       /* control type: numeric, callback function: (none) */
#define  PANEL_NUMERICSLIDE_PACKETS       10      /* control type: scale, callback function: (none) */
#define  PANEL_NUMERICSLIDE_BYTES         11      /* control type: scale, callback function: (none) */


     /* Control Arrays: */

#define  CTRLARRAY                        1

     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK connect(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK panelcb(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK receive(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK timer(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
