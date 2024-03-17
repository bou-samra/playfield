CUSTOM	=	$DFF000
BPLCON0	=	$100
BPLCON1	=	$102
BPLCON2	=	$104
BPL1MOD	=	$108
DDFSTRT	=	$092
DDFSTOP	=	$094
DIWSTRT	=	$08E
DIWSTOP	=	$090
VPOSR	=	$004
COLOR00	=	$180
COLOR01	=	$182
COLOR02	=	$184
COLOR03	=	$186
DMACON	=	$096
COPJMP1	=	$088
COP1LCH	=	$080			;Copper location register 1
					;  (high three bits)
	LEA	CUSTOM,A0		;A0 points at custom chips
	MOVE.W	#$1200,BPLCON0(A0)	;One bit-plane, enable composite color
	MOVE.W	#0,BPLCON1(A0)		;Set horizontal scroll value to 0
	MOVE.W	#0,BPL1MOD(A0)		;Set modulo to 0 for all odd bit-planes
	MOVE.W	#$0038,DDFSTRT(A0)	;Set data-fetch start to $38
	MOVE.W	#$00D0,DDFSTOP(A0)	;Set data-fetch stop to $D0
	MOVE.W	#$2C81,DIWSTRT(A0)	;Set DIWSTRT to $2C81
	MOVE.W	#$F4C1,DIWSTOP(A0)	;Set DIWSTOP to $F4C1
	MOVE.W	#$0F00,COLOR00(A0)	;Set background color to red
	MOVE.W	#$0FF0,COLOR01(A0)	;Set color register 1 to yellow
;
; Fill biy-plane with $FF00FF00 to produce stripes
;
	MOVE.L	#$21000,A1		;Point at beginning of bit-plane
	MOVE.L	#$FF00FF00,D0		;We will write $FF00FF00 long words
	MOVE.W	#2000,D1		;2000 long words = 8000 bytes
;
LOOP:	MOVE.L	D0,(A1)+		;Write a long word
	SUBQ.W	#1,D1			;Decrement counter
	BNE	LOOP			;Loop until bit-plane is filled
;
; Set up Copper list at $20000
;
	MOVE.L	#$20000,A1		;Point at Copper list destination
	LEA	COPPERL,A2		;Point A2 at Copper list data
CLOOP:	MOVE.L	(A2),(A1)+		;Move a word
	CMPI.L	#$FFFFFFFE,(A2)+	;Check for last longword of Copper list
	BNE	CLOOP
;
; Point Copper at Copper list
;
	MOVE.L	#$20000,COP1LCH(A0)	;Write to Copper location register
	MOVE.W	COPJMP1(A0),D0		;Force copper to $20000
;
; Start DMA
;
	MOVE.W	#$8380,DMACON(A0)	;Enable bit-plane and Copper DMA
HERE:	BRA	HERE			;Do do next task
;
; This is the data for the Copper list.
;
COPPERL:
	DC.W	$00E0,$0002		;Move $0002 to address $0E0
					;  (BPL1PTH)
	DC.W	$00E2,$1000		;Move $1000 to address $0E2
					;  (BPL1PTL)
	DC.W	$FFFF,$FFFE		;End of Copper list
;
