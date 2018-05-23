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
#define  PANEL_STRING_CLIENTIPNAME        2       /* control type: string, callback function: (none) */
#define  PANEL_STRING_CLIENTIP            3       /* control type: string, callback function: (none) */
#define  PANEL_STRING_SERVERNAME          4       /* control type: string, callback function: (none) */
#define  PANEL_STRING_SERVERIP            5       /* control type: string, callback function: (none) */
#define  PANEL_STRING_PORTNUMBER          6       /* control type: string, callback function: (none) */
#define  PANEL_STRING_ADDRESS             7       /* control type: string, callback function: (none) */
#define  PANEL_DECORATION                 8       /* control type: deco, callback function: (none) */
#define  PANEL_TEXTBOX                    9       /* control type: textBox, callback function: (none) */
#define  PANEL_DECORATION_2               10      /* control type: deco, callback function: (none) */
#define  PANEL_LED_CLIENT                 11      /* control type: LED, callback function: (none) */
#define  PANEL_LED_SERVER                 12      /* control type: LED, callback function: (none) */
#define  PANEL_CMD_DISCONNECT             13      /* control type: command, callback function: disconnect */
#define  PANEL_CMD_CONNECT                14      /* control type: command, callback function: connect */
#define  PANEL_STRIPCHART                 15      /* control type: strip, callback function: (none) */
#define  PANEL_QUITBUTTON                 16      /* control type: command, callback function: QuitCallback */
#define  PANEL_CMD_CLEAR                  17      /* control type: command, callback function: clear */
#define  PANEL_CMD_SEND                   18      /* control type: command, callback function: send */
#define  PANEL_TIMER                      19      /* control type: timer, callback function: timer */


     /* Control Arrays: */

#define  CTRLARRAY                        1

     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK clear(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK connect(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK disconnect(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK QuitCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK send(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK timer(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
