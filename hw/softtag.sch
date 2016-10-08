EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:pic12
LIBS:softtag-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L C C1
U 1 1 57EA5D0D
P 2650 2250
F 0 "C1" H 2765 2296 50  0000 L CNN
F 1 "C" H 2765 2205 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 2688 2100 50  0001 C CNN
F 3 "" H 2650 2250 50  0000 C CNN
	1    2650 2250
	1    0    0    -1  
$EndComp
$Comp
L CTRIM C2
U 1 1 57EA5D63
P 2900 2250
F 0 "C2" H 3015 2296 50  0000 L CNN
F 1 "CTRIM" H 3015 2205 50  0000 L CNN
F 2 "Capacitors_SMD:C_1206_HandSoldering" H 2900 2250 50  0001 C CNN
F 3 "" H 2900 2250 50  0000 C CNN
	1    2900 2250
	1    0    0    -1  
$EndComp
Wire Wire Line
	2450 1900 2450 2050
Wire Wire Line
	2450 2050 2500 2050
Wire Wire Line
	2500 2050 2500 2100
Wire Wire Line
	2500 2100 2450 2100
Wire Wire Line
	2450 2100 2450 2150
Wire Wire Line
	2450 2150 2500 2150
Wire Wire Line
	2500 2150 2500 2200
Wire Wire Line
	2500 2200 2450 2200
Wire Wire Line
	2450 2200 2450 2250
Wire Wire Line
	2450 2250 2500 2250
Wire Wire Line
	2500 2250 2500 2300
Wire Wire Line
	2500 2300 2450 2300
Wire Wire Line
	2450 2300 2450 2350
Wire Wire Line
	2450 2350 2500 2350
Wire Wire Line
	2500 2350 2500 2400
Wire Wire Line
	2500 2400 2450 2400
Wire Wire Line
	2450 2400 2450 2450
Wire Wire Line
	2450 2450 2500 2450
Wire Wire Line
	2500 2450 2500 2500
Wire Wire Line
	2500 2500 2450 2500
Wire Wire Line
	2450 2500 2450 2550
Text Notes 1750 2250 0    60   ~ 0
PCB Inductor
$Comp
L GND #PWR01
U 1 1 57EA5F2F
P 3450 2650
F 0 "#PWR01" H 3450 2400 50  0001 C CNN
F 1 "GND" H 3455 2477 50  0000 C CNN
F 2 "" H 3450 2650 50  0000 C CNN
F 3 "" H 3450 2650 50  0000 C CNN
	1    3450 2650
	1    0    0    -1  
$EndComp
$Comp
L D_Schottky D1
U 1 1 57EA5F4B
P 3700 2000
F 0 "D1" H 3700 1784 50  0000 C CNN
F 1 "D_Schottky" H 3700 1875 50  0000 C CNN
F 2 "Capacitors_SMD:C_1206_HandSoldering" H 3700 2000 50  0001 C CNN
F 3 "" H 3700 2000 50  0000 C CNN
	1    3700 2000
	-1   0    0    1   
$EndComp
$Comp
L ZENER D3
U 1 1 57EA62A2
P 4000 2250
F 0 "D3" V 3954 2329 50  0000 L CNN
F 1 "ZENER" V 4045 2329 50  0000 L CNN
F 2 "TO_SOT_Packages_SMD:SOT-23" H 4000 2250 50  0001 C CNN
F 3 "" H 4000 2250 50  0000 C CNN
	1    4000 2250
	0    1    1    0   
$EndComp
Wire Wire Line
	4000 2550 4000 2450
Wire Wire Line
	3850 2000 4950 2000
Wire Wire Line
	4000 2000 4000 2050
Wire Wire Line
	4450 1850 4450 2100
Connection ~ 4000 2000
Wire Wire Line
	4450 2550 4450 2400
Connection ~ 4000 2550
Wire Wire Line
	3450 2550 3450 2650
Connection ~ 3450 2550
$Comp
L PWR_FLAG #FLG02
U 1 1 57EA649D
P 4950 2000
F 0 "#FLG02" H 4950 2095 50  0001 C CNN
F 1 "PWR_FLAG" V 4950 2178 50  0000 L CNN
F 2 "" H 4950 2000 50  0000 C CNN
F 3 "" H 4950 2000 50  0000 C CNN
	1    4950 2000
	0    1    1    0   
$EndComp
$Comp
L PWR_FLAG #FLG03
U 1 1 57EA64CD
P 4950 2550
F 0 "#FLG03" H 4950 2645 50  0001 C CNN
F 1 "PWR_FLAG" V 4950 2728 50  0000 L CNN
F 2 "" H 4950 2550 50  0000 C CNN
F 3 "" H 4950 2550 50  0000 C CNN
	1    4950 2550
	0    1    1    0   
$EndComp
Connection ~ 4450 2000
Connection ~ 4450 2550
$Comp
L VCC #PWR04
U 1 1 57EA65C6
P 4450 1850
F 0 "#PWR04" H 4450 1700 50  0001 C CNN
F 1 "VCC" H 4467 2023 50  0000 C CNN
F 2 "" H 4450 1850 50  0000 C CNN
F 3 "" H 4450 1850 50  0000 C CNN
	1    4450 1850
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR05
U 1 1 57EA6694
P 4850 3600
F 0 "#PWR05" H 4850 3450 50  0001 C CNN
F 1 "VCC" H 4850 3750 50  0000 C CNN
F 2 "" H 4850 3600 50  0000 C CNN
F 3 "" H 4850 3600 50  0000 C CNN
	1    4850 3600
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR06
U 1 1 57EA66B1
P 4850 5050
F 0 "#PWR06" H 4850 4800 50  0001 C CNN
F 1 "GND" H 4855 4877 50  0000 C CNN
F 2 "" H 4850 5050 50  0000 C CNN
F 3 "" H 4850 5050 50  0000 C CNN
	1    4850 5050
	1    0    0    -1  
$EndComp
Wire Wire Line
	4850 3700 4850 3600
Wire Wire Line
	4850 4950 4850 5050
$Comp
L Q_NMOS_GSD Q1
U 1 1 57EA68C5
P 3400 2250
F 0 "Q1" H 3350 2100 50  0000 L CNN
F 1 "Q_NMOS_GSD" H 3400 2600 50  0000 L CNN
F 2 "TO_SOT_Packages_SMD:SOT-23" H 3600 2350 50  0001 C CNN
F 3 "" H 3400 2250 50  0000 C CNN
	1    3400 2250
	-1   0    0    -1  
$EndComp
Wire Wire Line
	2650 1900 2650 2100
Connection ~ 2650 2000
Wire Wire Line
	2650 2400 2650 2550
Connection ~ 2650 2550
Wire Wire Line
	2900 2550 2900 2400
Connection ~ 2900 2550
Wire Wire Line
	2900 2100 2900 2000
Connection ~ 2900 2000
Wire Wire Line
	3300 950  3300 2050
Connection ~ 3300 2000
Wire Wire Line
	3300 2550 3300 2450
Connection ~ 3300 2550
Wire Wire Line
	3750 2250 3750 2850
Wire Wire Line
	3750 2850 4200 2850
Text Label 3800 2850 0    60   ~ 0
MOD_TX
$Comp
L C C3
U 1 1 57EA6EBF
P 4400 1150
F 0 "C3" H 4515 1196 50  0000 L CNN
F 1 "C" H 4515 1105 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 4438 1000 50  0001 C CNN
F 3 "" H 4400 1150 50  0000 C CNN
	1    4400 1150
	1    0    0    -1  
$EndComp
$Comp
L D D2
U 1 1 57EA6FEF
P 4000 950
F 0 "D2" H 4000 735 50  0000 C CNN
F 1 "D" H 4000 826 50  0000 C CNN
F 2 "Capacitors_SMD:C_1206_HandSoldering" H 4000 950 50  0001 C CNN
F 3 "" H 4000 950 50  0000 C CNN
	1    4000 950 
	-1   0    0    1   
$EndComp
Wire Wire Line
	4400 1000 4400 950 
Wire Wire Line
	4150 950  5150 950 
Connection ~ 4400 950 
Wire Wire Line
	3850 950  3300 950 
$Comp
L GND #PWR07
U 1 1 57EA717E
P 4400 1450
F 0 "#PWR07" H 4400 1200 50  0001 C CNN
F 1 "GND" H 4405 1277 50  0000 C CNN
F 2 "" H 4400 1450 50  0000 C CNN
F 3 "" H 4400 1450 50  0000 C CNN
	1    4400 1450
	1    0    0    -1  
$EndComp
Wire Wire Line
	4400 1300 4400 1450
Text Label 5950 950  0    60   ~ 0
MOD_RX
$Comp
L R R2
U 1 1 57EA72F6
P 4750 1150
F 0 "R2" H 4820 1196 50  0000 L CNN
F 1 "R" H 4820 1105 50  0000 L CNN
F 2 "Resistors_SMD:R_0805" V 4680 1150 50  0001 C CNN
F 3 "" H 4750 1150 50  0000 C CNN
	1    4750 1150
	1    0    0    -1  
$EndComp
$Comp
L R R3
U 1 1 57EA7376
P 4750 2250
F 0 "R3" H 4820 2296 50  0000 L CNN
F 1 "R" H 4820 2205 50  0000 L CNN
F 2 "Resistors_SMD:R_0805" V 4680 2250 50  0001 C CNN
F 3 "" H 4750 2250 50  0000 C CNN
	1    4750 2250
	1    0    0    -1  
$EndComp
Wire Wire Line
	4750 2000 4750 2100
Connection ~ 4750 2000
Wire Wire Line
	4750 2550 4750 2400
Connection ~ 4750 2550
Wire Wire Line
	4750 1300 4750 1350
Wire Wire Line
	4750 1350 4400 1350
Connection ~ 4400 1350
Wire Wire Line
	4750 1000 4750 950 
Connection ~ 4750 950 
$Comp
L R R1
U 1 1 57EA771B
P 3650 2400
F 0 "R1" H 3720 2446 50  0000 L CNN
F 1 "R" H 3720 2355 50  0000 L CNN
F 2 "Resistors_SMD:R_0805" V 3580 2400 50  0001 C CNN
F 3 "" H 3650 2400 50  0000 C CNN
	1    3650 2400
	1    0    0    -1  
$EndComp
Wire Wire Line
	2450 2550 4950 2550
Connection ~ 3650 2550
Wire Wire Line
	3600 2250 3750 2250
Connection ~ 3650 2250
$Comp
L R R4
U 1 1 57EA7C47
P 7250 4050
F 0 "R4" H 7320 4096 50  0000 L CNN
F 1 "R" H 7320 4005 50  0000 L CNN
F 2 "Resistors_SMD:R_0805" V 7180 4050 50  0001 C CNN
F 3 "" H 7250 4050 50  0000 C CNN
	1    7250 4050
	1    0    0    -1  
$EndComp
$Comp
L R R5
U 1 1 57EA7CBA
P 7250 4450
F 0 "R5" H 7320 4496 50  0000 L CNN
F 1 "R" H 7320 4405 50  0000 L CNN
F 2 "Resistors_SMD:R_0805" V 7180 4450 50  0001 C CNN
F 3 "" H 7250 4450 50  0000 C CNN
	1    7250 4450
	1    0    0    -1  
$EndComp
Wire Wire Line
	7250 4200 7250 4300
$Comp
L VCC #PWR08
U 1 1 57EA7D55
P 7250 3850
F 0 "#PWR08" H 7250 3700 50  0001 C CNN
F 1 "VCC" H 7267 4023 50  0000 C CNN
F 2 "" H 7250 3850 50  0000 C CNN
F 3 "" H 7250 3850 50  0000 C CNN
	1    7250 3850
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR09
U 1 1 57EA7D8A
P 7250 4650
F 0 "#PWR09" H 7250 4400 50  0001 C CNN
F 1 "GND" H 7255 4477 50  0000 C CNN
F 2 "" H 7250 4650 50  0000 C CNN
F 3 "" H 7250 4650 50  0000 C CNN
	1    7250 4650
	1    0    0    -1  
$EndComp
Wire Wire Line
	7250 3900 7250 3850
Wire Wire Line
	7250 4600 7250 4650
Wire Wire Line
	5850 4350 6950 4350
Text Label 5900 4350 0    60   ~ 0
MOD_RX
Connection ~ 7250 4250
Wire Wire Line
	7250 4250 5850 4250
$Comp
L PIC12LF1612-E/SN U1
U 1 1 57EA8E99
P 4850 4350
F 0 "U1" H 4850 4450 60  0000 C CNN
F 1 "PIC12LF1612-E/SN" H 4850 4300 60  0000 C CNN
F 2 "Housings_SOIC:SOIC-8_3.9x4.9mm_Pitch1.27mm" H 6150 4800 60  0001 C CNN
F 3 "" H 6150 4800 60  0001 C CNN
	1    4850 4350
	1    0    0    -1  
$EndComp
Wire Wire Line
	3900 4250 2800 4250
Text Label 2900 4250 0    60   ~ 0
MOD_TX
$Comp
L CONN_01X06 P1
U 1 1 57EA97A6
P 5150 6350
F 0 "P1" H 5228 6391 50  0000 L CNN
F 1 "CONN_01X06" H 5228 6300 50  0000 L CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x06" H 5150 6350 50  0001 C CNN
F 3 "" H 5150 6350 50  0000 C CNN
	1    5150 6350
	1    0    0    -1  
$EndComp
Wire Wire Line
	4950 6100 3850 6100
Wire Wire Line
	4950 6200 3850 6200
Wire Wire Line
	4950 6300 3850 6300
Wire Wire Line
	4950 6400 3850 6400
Wire Wire Line
	4950 6500 3850 6500
Wire Wire Line
	4950 6600 3850 6600
$Comp
L GND #PWR010
U 1 1 57EA9939
P 3850 6700
F 0 "#PWR010" H 3850 6450 50  0001 C CNN
F 1 "GND" H 3855 6527 50  0000 C CNN
F 2 "" H 3850 6700 50  0000 C CNN
F 3 "" H 3850 6700 50  0000 C CNN
	1    3850 6700
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR011
U 1 1 57EA996B
P 3850 6000
F 0 "#PWR011" H 3850 5850 50  0001 C CNN
F 1 "VCC" H 3867 6173 50  0000 C CNN
F 2 "" H 3850 6000 50  0000 C CNN
F 3 "" H 3850 6000 50  0000 C CNN
	1    3850 6000
	1    0    0    -1  
$EndComp
Text Label 3900 6200 0    60   ~ 0
FREE0
Text Label 3900 6300 0    60   ~ 0
FREE1
Text Label 3900 6400 0    60   ~ 0
FREE2
Text Label 3900 6500 0    60   ~ 0
FREE3
Wire Wire Line
	3850 6100 3850 6000
Wire Wire Line
	3850 6600 3850 6700
Text Label 2900 4350 0    60   ~ 0
FREE0
Text Label 2900 4450 0    60   ~ 0
FREE1
Text Label 5900 4450 0    60   ~ 0
FREE2
Text Label 5900 4250 0    60   ~ 0
FREE3
Wire Wire Line
	3900 4350 2800 4350
Wire Wire Line
	3900 4450 2800 4450
Wire Wire Line
	5850 4450 6950 4450
$Comp
L C C5
U 1 1 57EA9F14
P 5750 3250
F 0 "C5" H 5865 3296 50  0000 L CNN
F 1 "C" H 5865 3205 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 5788 3100 50  0001 C CNN
F 3 "" H 5750 3250 50  0000 C CNN
	1    5750 3250
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR012
U 1 1 57EA9FA8
P 5750 3450
F 0 "#PWR012" H 5750 3200 50  0001 C CNN
F 1 "GND" H 5755 3277 50  0000 C CNN
F 2 "" H 5750 3450 50  0000 C CNN
F 3 "" H 5750 3450 50  0000 C CNN
	1    5750 3450
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR013
U 1 1 57EAA05D
P 5750 3050
F 0 "#PWR013" H 5750 2900 50  0001 C CNN
F 1 "VCC" H 5767 3223 50  0000 C CNN
F 2 "" H 5750 3050 50  0000 C CNN
F 3 "" H 5750 3050 50  0000 C CNN
	1    5750 3050
	1    0    0    -1  
$EndComp
Wire Wire Line
	5750 3050 5750 3100
Wire Wire Line
	5750 3400 5750 3450
$Comp
L ZENER D4
U 1 1 57EAA3A1
P 5650 1200
F 0 "D4" V 5604 1279 50  0000 L CNN
F 1 "ZENER" V 5695 1279 50  0000 L CNN
F 2 "TO_SOT_Packages_SMD:SOT-23" H 5650 1200 50  0001 C CNN
F 3 "" H 5650 1200 50  0000 C CNN
	1    5650 1200
	0    1    1    0   
$EndComp
Wire Wire Line
	4400 1400 5650 1400
Connection ~ 4400 1400
$Comp
L CP C4
U 1 1 57EAAB3E
P 4450 2250
F 0 "C4" H 4568 2296 50  0000 L CNN
F 1 "CP" H 4568 2205 50  0000 L CNN
F 2 "Capacitors_Tantalum_SMD:TantalC_SizeA_EIA-3216_HandSoldering" H 4488 2100 50  0001 C CNN
F 3 "" H 4450 2250 50  0000 C CNN
	1    4450 2250
	1    0    0    -1  
$EndComp
$Comp
L R R6
U 1 1 57EAB09B
P 3100 2250
F 0 "R6" H 3170 2296 50  0000 L CNN
F 1 "R" H 3170 2205 50  0000 L CNN
F 2 "Resistors_SMD:R_0805" V 3030 2250 50  0001 C CNN
F 3 "" H 3100 2250 50  0000 C CNN
	1    3100 2250
	1    0    0    -1  
$EndComp
Wire Wire Line
	3100 2100 3100 2000
Connection ~ 3100 2000
Wire Wire Line
	3100 2400 3100 2550
Connection ~ 3100 2550
$Comp
L R R7
U 1 1 57EA8A61
P 2550 1650
F 0 "R7" V 2343 1650 50  0000 C CNN
F 1 "0R" V 2434 1650 50  0000 C CNN
F 2 "Resistors_SMD:R_0603" V 2480 1650 50  0001 C CNN
F 3 "" H 2550 1650 50  0000 C CNN
	1    2550 1650
	0    1    1    0   
$EndComp
Wire Wire Line
	2650 2000 3550 2000
Wire Wire Line
	2700 1650 2700 1900
Wire Wire Line
	2700 1900 2650 1900
Wire Wire Line
	2450 1900 2400 1900
Wire Wire Line
	2400 1900 2400 1650
$Comp
L R R?
U 1 1 57F3D585
P 5300 950
F 0 "R?" V 5093 950 50  0000 C CNN
F 1 "R" V 5184 950 50  0000 C CNN
F 2 "" V 5230 950 50  0000 C CNN
F 3 "" H 5300 950 50  0000 C CNN
	1    5300 950 
	0    1    1    0   
$EndComp
Wire Wire Line
	5450 950  6350 950 
Wire Wire Line
	5650 1000 5650 950 
Connection ~ 5650 950 
$EndSCHEMATC