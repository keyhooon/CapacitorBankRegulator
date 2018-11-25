/*
 /*
 * 3GPP_TS27.h
 *
 *  Created on: Nov 21, 2018
 *      Author: HP
 */

#ifndef GSMMODEM_API_3GPP_TS27_H_
#define GSMMODEM_API_3GPP_TS27_H_

#include "Gsm.h"

const CommandType_TypeDef Accumulated_Call_Meter_Reset_or_Query = { "CACM", 0,
		extended };
const CommandType_TypeDef Accumulated_Call_Meter_Maximum_Set_or_Query = {
		"CAMM", 0, extended };
const CommandType_TypeDef Advice_of_Charge = { "CAOC", 0, extended };
const CommandType_TypeDef Select_Bearer_Service_Type = { "CBST", 0, extended };
const CommandType_TypeDef Call_Forwarding_Number_and_Conditions_Control = {
		"CCFC", 0, extended };
const CommandType_TypeDef Call_Waiting_Control = { "CCWA", 15000, extended };
const CommandType_TypeDef Extended_Error_Report = { "CEER", 0, extended };
const CommandType_TypeDef Request_Manufacturer_Identification = { "CGMI", 20000,
		extended };
const CommandType_TypeDef Request_Model_Identification = { "CGMM", 0, extended };
const CommandType_TypeDef Request_TA_Revision_Identification_Software_Release =
		{ "CGMR", 0, extended };
const CommandType_TypeDef Request_Product_Serial_Number_Identification = {
		"CGSN", 0, extended };
const CommandType_TypeDef Select_TE_Character_Set = { "CSCS", 0, extended };
const CommandType_TypeDef Select_Type_Address = { "CSTA", 0, extended };
const CommandType_TypeDef Call_Hold_and_Multiparty = { "CHLD", 20000, extended };
const CommandType_TypeDef Request_International_Mobile_Subscriber_Identity = {
		"CIMI", 20000, extended };
const CommandType_TypeDef List_Current_Calls_ME = { "CLCC", 0, extended };
const CommandType_TypeDef Facility_Lock = { "CLCK", 0, extended };
const CommandType_TypeDef Calling_Line_Identification_Presentation = { "CLIP",
		15000, extended };
const CommandType_TypeDef Calling_Line_Identification_Restriction = { "CLIR",
		15000, extended };
const CommandType_TypeDef Report_Mobile_Equipment_Error =
		{ "CMEE", 0, extended };
const CommandType_TypeDef Connected_Line_Identification_Presentation = { "COLP",
		0, extended };
const CommandType_TypeDef Operator_Selection = { "COPS", 12000, extended };
const CommandType_TypeDef Phone_Activity_Status = { "CPAS", 0, extended };
const CommandType_TypeDef Find_Phonebook_Entries = { "CPBF", 0, extended };
const CommandType_TypeDef Read_Current_Phonebook_Entries =
		{ "CPBR", 0, extended };
const CommandType_TypeDef Select_Phonebook_Memory_Storage = { "CPBS", 3000,
		extended };
const CommandType_TypeDef Write_Phonebook_Entry = { "CPBW", 3000, extended };
const CommandType_TypeDef SET_DCDEnter_PIN_FUNCTION_MODE =
		{ "CPIN", 0, extended };
const CommandType_TypeDef Change_Password = { "CPWD", 5000, extended };
const CommandType_TypeDef Service_Reporting_Control = { "CR", 0, extended };
const CommandType_TypeDef Set_Cellular_Result_Codes_Incoming_Call_Indication = {
		"CRC", 0, extended };
const CommandType_TypeDef Network_Registration = { "CREG", 0, extended };
const CommandType_TypeDef Select_Radio_Link_Protocol_Parameters = { "CRLP", 0,
		extended };
const CommandType_TypeDef Restricted_SIM_Access = { "CRSM", 0, extended };
const CommandType_TypeDef Signal_Quality_Report = { "CSQ", 0, extended };
const CommandType_TypeDef Tone_Duration = { "VTD", 0, extended };
const CommandType_TypeDef DTMF_Tone_Generation = { "VTS", 0, extended };
const CommandType_TypeDef Multiplexer_Control = { "CMUX", 0, extended };
const CommandType_TypeDef Subscriber_Number = { "CNUM", 0, extended };
const CommandType_TypeDef Preferred_Operator_List = { "CPOL", 0, extended };
const CommandType_TypeDef Read_Operator_Names = { "COPN", 0, extended };
const CommandType_TypeDef Set_Phone_Functionality = { "CFUN", 10000, extended };
const CommandType_TypeDef Clock = { "CCLK", 0, extended };
const CommandType_TypeDef Generic_SIM_Access = { "CSIM", 0, extended };
const CommandType_TypeDef Alert_Sound_Mode = { "CALM", 0, extended };
const CommandType_TypeDef Alert_Sound_Select = { "CALS", 0, extended };
const CommandType_TypeDef Ringer_Sound_Level = { "CRSL", 0, extended };
const CommandType_TypeDef Loud_Speaker_Volume_Level = { "CLVL", 0, extended };
const CommandType_TypeDef Mute_Control = { "CMUT", 0, extended };
const CommandType_TypeDef Price_Per_Unit_and_Currency_Table = { "CPUC", 5000,
		extended };
const CommandType_TypeDef Call_Meter_Maximum_Even = { "CCWE", 0, extended };
const CommandType_TypeDef Battery_Charge = { "CBC", 0, extended };
const CommandType_TypeDef Unstructured_Supplementary_Service_Data = { "CUSD", 0,
		extended };
const CommandType_TypeDef Supplementary_Services_Notification = { "CSSN", 0,
		extended };

#define GSM_Accumulated_Call_Meter_Reset_or_Query()
#define GSM_Accumulated_Call_Meter_Maximum_Set_or_Query()
#define GSM_Advice_of_Charge()
#define GSM_Select_Bearer_Service_Type()
#define GSM_Call_Forwarding_Number_and_Conditions_Control()
#define GSM_Call_Waiting_Control()
#define GSM_Extended_Error_Report()
#define GSM_Request_Manufacturer_Identification()
#define GSM_Request_Model_Identification()
#define GSM_Request_TA_Revision_Identification_Software_Release()
#define GSM_Request_Product_Serial_Number_Identification()
#define GSM_Select_TE_Character_Set()
#define GSM_Select_Type_Address()
#define GSM_Call_Hold_and_Multiparty()
#define GSM_Request_International_Mobile_Subscriber_Identity()
#define GSM_List_Current_Calls_ME()
#define GSM_Facility_Lock()
#define GSM_Calling_Line_Identification_Presentation()
#define GSM_Calling_Line_Identification_Restriction()
#define GSM_Report_Mobile_Equipment_Error()
#define GSM_Connected_Line_Identification_Presentation()
#define GSM_Operator_Selection()
#define GSM_Phone_Activity_Status()
#define GSM_Find_Phonebook_Entries()
#define GSM_Read_Current_Phonebook_Entries()
#define GSM_Select_Phonebook_Memory_Storage()
#define GSM_Write_Phonebook_Entry()
#define GSM_SET_DCDEnter_PIN_FUNCTION_MODE()
#define GSM_Change_Password()
#define GSM_Service_Reporting_Control()
#define GSM_Set_Cellular_Result_Codes_Incoming_Call_Indication()
#define GSM_Network_Registration()
#define GSM_Select_Radio_Link_Protocol_Parameters()
#define GSM_Restricted_SIM_Access()
#define GSM_Signal_Quality_Report()
#define GSM_Tone_Duration()
#define GSM_DTMF_Tone_Generation()
#define GSM_Multiplexer_Control()
#define GSM_Subscriber_Number()
#define GSM_Preferred_Operator_List()
#define GSM_Read_Operator_Names()
#define GSM_Set_Phone_Functionality()
#define GSM_Clock()
#define GSM_Generic_SIM_Access()
#define GSM_Alert_Sound_Mode()
#define GSM_Alert_Sound_Select()
#define GSM_Ringer_Sound_Level()
#define GSM_Loud_Speaker_Volume_Level()
#define GSM_Mute_Control()
#define GSM_Price_Per_Unit_and_Currency_Table()
#define GSM_Call_Meter_Maximum_Even()
#define GSM_Battery_Charge()
#define GSM_Unstructured_Supplementary_Service_Data()
#define GSM_Supplementary_Services_Notification()

#endif /* GSMMODEM_API_3GPP_TS27_H_ */

