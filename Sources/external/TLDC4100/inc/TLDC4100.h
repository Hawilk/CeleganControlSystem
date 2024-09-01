/****************************************************************************

	Thorlabs DC4100 - 4 Channel LED Driver -  VISA instrument driver

 	Copyright: 	Copyright(c) 2009-2012, Thorlabs GmbH (www.thorlabs.com)
 	Author:		Olaf Wohlmann (owohlmann@thorlabs.com)

	Disclaimer:

	This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
	License as published by the Free Software Foundation; either
	version 2.1 of the License, or (at your option) any later version.

	This library is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
	Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public
	License along with this library; if not, write to the Free Software
	Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA


 	Header file

 	Date:       	Jan-26-2012
 	Software-Nr:   09.182.100
 	Version:    	1.1

	Changelog:		see 'Readme.rtf'

****************************************************************************/

#ifndef __TLDC4100_H_
#define __TLDC4100_H_

/*=============================================================================
  Include files
=============================================================================*/	
#include <vpptype.h>  

/*=============================================================================
  Constants
=============================================================================*/

#if defined(__cplusplus) || defined(__cplusplus__)
extern "C"
{
#endif
	
/*========================================================================*//**
\defgroup Buffers Text Buffers
*//*=========================================================================*/
/**@{*/  
#define DC4100_BUFFER_SIZE               256      ///< General buffer size
#define DC4100_ERR_DESCR_BUFFER_SIZE     512      ///< Error description buffer size
/**@}*/   
	
/**	\brief Find pattern for 'viFindRsrc()'*/  
#define DC4100_FIND_PATTERN		      	"ASRL?*"

/*========================================================================*//**
\defgroup VI_INSTR_x Instrument error codes 
*//*=========================================================================*/
/**@{*/ 
#define VI_INSTR_ERROR_OFFSET          (_VI_ERROR + 0x3FFC0900L)	///< 0xBFFC0900
#define VI_ERROR_GET_INSTR_ERROR       (_VI_ERROR + 0x3FFC0805L)

#define VI_ERROR_UNKNOWN_ATTRIBUTE		(VI_ERROR_GET_INSTR_ERROR + 1)
#define VI_ERROR_NOT_SUPPORTED			(VI_ERROR_GET_INSTR_ERROR + 2)	
/**@}*/ 	

/*========================================================================*//**
\defgroup STAT__x Register Values
*//*=========================================================================*/
/**@{*/ 
#define STAT_VCC_FAIL_CHANGED				0x00000001
#define STAT_VCC_FAIL						0x00000002
#define STAT_OTP_CHANGED					0x00000004
#define STAT_OTP								0x00000008
#define STAT_NO_LED1_CHANGED				0x00000010
#define STAT_NO_LED1							0x00000020
#define STAT_NO_LED2_CHANGED				0x00000040
#define STAT_NO_LED2							0x00000080
#define STAT_NO_LED3_CHANGED				0x00000100
#define STAT_NO_LED3							0x00000200
#define STAT_NO_LED4_CHANGED				0x00000400
#define STAT_NO_LED4							0x00000800
#define STAT_LED_OPEN1_CHANGED			0x00001000
#define STAT_LED_OPEN1						0x00002000
#define STAT_LED_OPEN2_CHANGED			0x00004000
#define STAT_LED_OPEN2						0x00008000
#define STAT_LED_OPEN3_CHANGED			0x00010000
#define STAT_LED_OPEN3						0x00020000
#define STAT_LED_OPEN4_CHANGED			0x00040000
#define STAT_LED_OPEN4						0x00080000
#define STAT_LED_LIMIT1_CHANGED			0x00100000
#define STAT_LED_LIMIT1						0x00200000
#define STAT_LED_LIMIT2_CHANGED			0x00400000
#define STAT_LED_LIMIT2						0x00800000
#define STAT_LED_LIMIT3_CHANGED			0x01000000
#define STAT_LED_LIMIT3						0x02000000
#define STAT_LED_LIMIT4_CHANGED			0x04000000
#define STAT_LED_LIMIT4						0x08000000
#define STAT_IFC_REFRESH_CHANGED			0x10000000
/**@}*/ 	

/*========================================================================*//**
\defgroup MODUS_x Operation Modes
*//*=========================================================================*/
/**@{*/ 
#define MODUS_CONST_CURRENT		0
#define MODUS_PERCENT_CURRENT		1
#define MODUS_EXTERNAL_CONTROL	2
/**@}*/ 

/*========================================================================*//**
\defgroup Multi_Single Selection Modes
*//*=========================================================================*/
/**@{*/ 
#define MULTI_SELECT					0
#define SINGLE_SELECT				1
/**@}*/

/*========================================================================*//**
\defgroup HEAD_x LED Head Types
*//*=========================================================================*/
/**@{*/ 	
#define NO_HEAD						0		///< no head at all
#define FOUR_CHANNEL_HEAD			1		///< four channel head
#define ONE_CHANNEL_HEAD			2		///< single channel head
#define NOT_SUPPORTED_HEAD			253	///< head with unsupported forward bias
#define UNKNOWN_HEAD					254	///< head with unknown type
#define HEAD_WITHOUT_EEPROM		255	///< old standard heads
/**@}*/  

/*========================================================================*//**
\defgroup CHANNEL_x LED Channel Definitions
*//*=========================================================================*/
/**@{*/ 	
#define NUM_CHANNELS					4
#define MIN_CHANNEL					0
#define MAX_CHANNEL					3
#define ALL_CHANNELS					-1
#define CHANNEL_1						0
#define CHANNEL_2						1
#define CHANNEL_3						2
#define CHANNEL_4						3
/**@}*/  
	
/*=============================================================================
 Global functions
=============================================================================*/
ViStatus _VI_FUNC TLDC4100_init (ViRsrc rsrcName, 
											ViBoolean id_query, 
											ViBoolean reset_instr, 
											ViPSession vi);

ViStatus _VI_FUNC TLDC4100_close (ViSession vi);   

/*=============================================================================
 Utility functions
=============================================================================*/
ViStatus _VI_FUNC TLDC4100_reset (ViSession vi);

ViStatus _VI_FUNC TLDC4100_self_test (ViSession vi,
                                    ViInt16 *test_result,
                                    ViChar _VI_FAR test_message[]);

ViStatus _VI_FUNC TLDC4100_revision_query (ViSession vi, 
															ViChar _VI_FAR driver_rev[], 
															ViChar _VI_FAR instr_rev[]);

ViStatus _VI_FUNC TLDC4100_error_query (ViSession vi,
                                     	 ViInt32 *error_code, 
													 ViChar _VI_FAR error_message[]);

ViStatus _VI_FUNC TLDC4100_error_message (ViSession vi, 
														ViStatus status_code, 
														ViChar _VI_FAR message[]);
																							
ViStatus _VI_FUNC TLDC4100_identificationQuery (ViSession instrumentHandle, 
															ViChar _VI_FAR manufacturerName[], 
															ViChar _VI_FAR deviceName[],
                                             ViChar _VI_FAR serialNumber[], 
															ViChar _VI_FAR firmwareRevision[]);

ViStatus _VI_FUNC TLDC4100_getHeadInfo (ViSession instrumentHandle, 
														ViInt32 channel, 
														ViChar _VI_FAR serialNumber[], 
														ViChar _VI_FAR name[], 
														ViPInt32 type);

/*---------------------------------------------------------------------------
 Set/Get user limit current.
---------------------------------------------------------------------------*/
ViStatus _VI_FUNC TLDC4100_setLimitCurrent (ViSession instrumentHandle, ViInt32 channel, ViReal32 currentLimit);
ViStatus _VI_FUNC TLDC4100_getLimitCurrent (ViSession instrumentHandle, ViInt32 channel, ViPReal32 currentLimit);

/*---------------------------------------------------------------------------
 Set/Get maximum current.
---------------------------------------------------------------------------*/
ViStatus _VI_FUNC TLDC4100_setMaxLimit (ViSession instrumentHandle, ViInt32 channel, ViReal32 maximumCurrentLimit);
ViStatus _VI_FUNC TLDC4100_getMaxLimit (ViSession instrumentHandle, ViInt32 channel, ViPReal32 maximumCurrentLimit);

/*---------------------------------------------------------------------------
 Set/Get operation mode.
---------------------------------------------------------------------------*/
ViStatus _VI_FUNC TLDC4100_setOperationMode (ViSession instrumentHandle, ViInt32 operationMode);
ViStatus _VI_FUNC TLDC4100_getOperationMode (ViSession instrumentHandle, ViPInt32 operationMode);

/*---------------------------------------------------------------------------
 Set/Get LED output.
---------------------------------------------------------------------------*/
ViStatus _VI_FUNC TLDC4100_setLedOnOff (ViSession instrumentHandle, ViInt32 channel, ViBoolean LEDOnOff);
ViStatus _VI_FUNC TLDC4100_getLedOnOff (ViSession instrumentHandle, ViInt32 channel, ViPBoolean LEDOutputState);

/*---------------------------------------------------------------------------
 Set/Get selection mode.
---------------------------------------------------------------------------*/
ViStatus _VI_FUNC TLDC4100_setSelectionMode (ViSession instrumentHandle, ViInt32 selectionMode);
ViStatus _VI_FUNC TLDC4100_getSelectionMode (ViSession instrumentHandle, ViPInt32 selectionMode);

/*---------------------------------------------------------------------------
 Set/Get constant current.
---------------------------------------------------------------------------*/
ViStatus _VI_FUNC TLDC4100_setConstCurrent (ViSession instrumentHandle, ViInt32 channel, ViReal32 constantCurrent);
ViStatus _VI_FUNC TLDC4100_getConstCurrent (ViSession instrumentHandle, ViInt32 channel, ViPReal32 constantCurrent);

/*---------------------------------------------------------------------------
 Set/Get percental brightness current.
---------------------------------------------------------------------------*/
ViStatus _VI_FUNC TLDC4100_setPercentalBrightness (ViSession instrumentHandle, ViInt32 channel, ViReal32 brightness);
ViStatus _VI_FUNC TLDC4100_getPercentalBrightness (ViSession instrumentHandle, ViInt32 channel, ViPReal32 brightness);

/*---------------------------------------------------------------------------
 Set/Get the display brightness.
---------------------------------------------------------------------------*/
ViStatus _VI_FUNC TLDC4100_setDispBright (ViSession instrumentHandle, ViInt32 displayBrightness);
ViStatus _VI_FUNC TLDC4100_getDispBright (ViSession instrumentHandle, ViPInt32 displayBrightness);

/*---------------------------------------------------------------------------
 Get the status register.
---------------------------------------------------------------------------*/
ViStatus _VI_FUNC TLDC4100_getStatusRegister (ViSession instrumentHandle, ViPInt32 statusRegister);

/*---------------------------------------------------------------------------
 Get the wavelength information.
---------------------------------------------------------------------------*/
ViStatus _VI_FUNC TLDC4100_getWavelength (ViSession instrumentHandle, ViInt32 channel, ViPReal32 wavelength);

/*---------------------------------------------------------------------------
 Get the forward bias.
---------------------------------------------------------------------------*/
ViStatus _VI_FUNC TLDC4100_getForwardBias (ViSession instrumentHandle, ViInt32 channel, ViPReal32 forwardBias);



#if defined(__cplusplus) || defined(__cplusplus__)
}
#endif

#endif	/* _DC4100_HEADER_ */


/****************************************************************************
End of Header file
****************************************************************************/
