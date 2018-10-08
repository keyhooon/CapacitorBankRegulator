/*
 * CapacitorBank.h
 *
 *  Created on: Sep 30, 2018
 *      Author: HP
 */

#ifndef INC_CAPACITORBANK_H_
#define INC_CAPACITORBANK_H_

typedef struct {
	int capacitance;
	uint8_t isActive;
	uint8_t isExist;
} Capacitor_Typedef;

typedef enum {
	Idle, Run, Paused
} CapacitorBankState_Typedef;

typedef struct {
	int Voltage;
	int Current;
} LineParameter_Typedef;



typedef struct {
	int VoltageRms;
	int CurrentRms;
	int PhaseDifferent;
	int Harmonic[20];
} LineParameterInCycle_Typedef;

typedef struct {

};

typedef struct {
	CapacitorBankState_Typedef state;
	Capacitor_Typedef capacitors[10];
	LineParameterInCycle_Typedef LineParameterInCycle[3];
} CapacitorBank_Typedef;

#endif /* INC_CAPACITORBANK_H_ */
