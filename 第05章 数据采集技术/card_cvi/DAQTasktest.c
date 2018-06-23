//**************************************************************************
//* WARNING: This file was automatically generated.  Any changes you make  *
//*          to this file will be lost if you generate the file again.     *
//**************************************************************************
#include <ansi_c.h>
#include <NIDAQmx.h>

#define DAQmxErrChk(functionCall) if( (DAQmxError=(functionCall))<0 ) goto Error; else

//**************************************************************************
//* This generated function configures your DAQmx task.                    *
//*                                                                        *
//* Follow these steps to use this generated function:                     *
//*   1) Define a task handle variable in your program.                    *
//*   2) Call the generated function.                                      *
//*   3) Use the returned task handle as a parameter to other DAQmx        *
//*      functions.                                                        *
//*   4) Clear the task handle when you finish.                            *
//*                                                                        *
//*         TaskHandle task = 0;                                           *
//*         CreateDAQTask(&task);                                          *
//*         <use the DAQmx task handle>                                    *
//*         DAQmxClearTask(task);                                          *
//*                                                                        *
//**************************************************************************
int32 CreateDAQTasktest(TaskHandle *taskOut1)
{
	int32 DAQmxError = DAQmxSuccess;
    TaskHandle taskOut;

	DAQmxErrChk(DAQmxCreateTask("DAQTasktest", &taskOut));

	DAQmxErrChk(DAQmxCreateAIVoltageChan(taskOut, "PXI1Slot2/ai0", "电压",
		DAQmx_Val_Diff, -5, 5, DAQmx_Val_Volts, ""));	

	DAQmxErrChk(DAQmxSetChanAttribute(taskOut, "电压", DAQmx_AI_AutoZeroMode, 
		DAQmx_Val_None));
	DAQmxErrChk(DAQmxSetChanAttribute(taskOut, "电压", DAQmx_AI_Lowpass_Enable, 
		1));
	DAQmxErrChk(DAQmxSetChanAttribute(taskOut, "电压", DAQmx_AI_Lowpass_CutoffFreq, 
		(float64)10000));

	DAQmxErrChk(DAQmxCfgSampClkTiming(taskOut, "", 
		1000, DAQmx_Val_Rising, 
		DAQmx_Val_ContSamps, 100));

    *taskOut1 = taskOut;

Error:
	return DAQmxError;
}

