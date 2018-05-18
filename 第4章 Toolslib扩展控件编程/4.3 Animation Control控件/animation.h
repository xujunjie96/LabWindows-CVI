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
#define  PANEL_ANIMATION                  2       /* control type: pictRing, callback function: animationevent */
#define  PANEL_NUMERIC                    3       /* control type: numeric, callback function: interval */
#define  PANEL_NUMERIC_NEXT_2             4       /* control type: numeric, callback function: (none) */
#define  PANEL_NUMERIC_CUR_2              5       /* control type: numeric, callback function: (none) */
#define  PANEL_NUMERIC_NEXT               6       /* control type: numeric, callback function: (none) */
#define  PANEL_NUMERIC_CUR                7       /* control type: numeric, callback function: (none) */
#define  PANEL_TEXTMSG                    8       /* control type: textMsg, callback function: (none) */
#define  PANEL_QUITBUTTON                 9       /* control type: command, callback function: quitsys */
#define  PANEL_CMD_RESTART                10      /* control type: command, callback function: restart */
#define  PANEL_CMD_PAUSE                  11      /* control type: command, callback function: pause */
#define  PANEL_TEXTMSG_2                  12      /* control type: textMsg, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK animationevent(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK interval(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK pause(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK quitsys(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK restart(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
