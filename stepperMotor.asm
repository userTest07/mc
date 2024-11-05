;program for stepper motor thr.port 0 of 89v51RD2,
;lines used p0.0 to p0.3
;motor rotates in forward direction
;to change the direction use "Reverse" look up table
ORG 0000h
SJMP 0030H
ORG 0030H
MOV P0,#80H ; initialise port 0
MOV P2,#80H ;initialise port 2
ACALL DELAY ;delay
START1:
MOV DPTR,#REVERSE ;load forward direction table
MOV R7,#08H ; steps
NEXT: CLR A
MOVC A,@A+DPTR ; ini. A for signal.
INC DPTR
MOV P2,A ;out stepper signal to p2
MOV P0,A ; out stepper signal to p0
ACALL DELAY
DEC R7
CJNE R7,#00,NEXT ; keep in step loop
SJMP START1 ; keep in continous loop
DELAY:
MOV R1,#0F2H ; delay as per user
MOV R2,#0F2H ; motor speed is depend on this delay
MOV R3,#0f8H ; if you want slow speed increase delay
D1:
DJNZ R1,D1
MOV R1,#010H
DJNZ R2,D1
MOV R2,#010H
DJNZ R3,D1
RET
FORWARD: DB 01H,03H,02H,06H,04H,0CH,08H,09H ; forward direction table
REVERSE: DB 09H,08H,0CH,04H,06H,02H,03H,01H ;revese direction table
END
