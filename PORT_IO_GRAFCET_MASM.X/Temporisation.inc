;*******************************************************************************
;	3 Sous Programmes qui réalisent les tamporisations suivantes:
; Temporisation1 = Nx * 1ms	la variable Nx contiendra le nombre de 1 ms
; Temporisation2 = Nx * 10ms	la variable Nx contiendra le nombre de 10 ms
; Temporisation3 = Nx * 100ms	la variable Nx contiendra le nombre de 100 ms
;*******************************************************************************

;*******************************************************************************
uDataAccess1	udata_acs	0x50		; Adresse de uDataAccess1 = 0x50 (access page)
Nx		res		1		; Adresse Variable Nx = 50h
N1		res		1		; Adresse Variable N1 = 51h    
N2		res		1		; Adresse Variable N2 = 52h
N3		res		1		; Adresse Variable N3 = 53h
;*******************************************************************************	    
	    
	ORG		0x500		; Adresse ROM des sous programmes TempoNx1ms, TempoNx10ms et TempoNx100ms
;*******************************************************************************
; Temporisation1 = Nx * 1ms	la variable N contiendra le nombre de 1 ms		
;*******************************************************************************
TempoNx1ms:		    ; Quartz = 8 MHz  --> Cycle instruction = 2 MHz --> 0,5 µs		
	MOVF	Nx	    ; Test la variable Nx 
	BZ	FinNx1ms    ; Si Nx = 0 --> pas de temporisation
T3_1ms:			    ; <----------------------------------------------------------------
	MOVLW	25	    ; 1 cycle								|
	MOVWF	N2	    ; 1 cycle								|
T2_1ms:			    ; <-------------------------------------------------		|
    MOVLW	25	    ; 1 cycle						|		|
	MOVWF	N1	    ; 1 cycle						|		|
T1_1ms:			    ; <-------------------------------------		|		|
	DECFSZ	N1, f	    ; 1 cycle si N1>0 et 3 cycles si N1=0   |T1=25*3	|		|
	GOTO	T1_1ms	    ; 2 cycles	<---------------------------		|		|
	DECFSZ	N2, f	    ; 1 cycle si N2>0 et 3 cycles si N2=0		|T2=25*(2+T1+3) |
	GOTO	T2_1ms	    ; 2 cycles	<---------------------------------------		|
	DECFSZ	Nx, f	    ; 1 cycle si N3>0 et 3 cycles si N3=0				|T3=Nx*(2+T2+3)
	GOTO	T3_1ms	    ; 2 cycles	<-------------------------------------------------------
FinNx1ms:
	RETURN		    ; 2 cycles		TempoNx1ms = T3 + 2 + 2 = Nx*T2 + 5*Nx + 4 


;*******************************************************************************
; Temporisation2 = Nx * 10ms la variable Nx contiendra le nombre de 10 ms		
;*******************************************************************************
TempoNx10ms:		    ; Quartz = 8 MHz  --> Cycle instruction = 2 MHz --> 0,5 µs		
	MOVF	Nx	    ; Test la variable Nx 
	BZ	FinNx10ms   ; Si Nx = 0 --> pas de temporisation
T3_10ms:			    ; <---------------------------------------------------------
	MOVLW	250	    ; 1 cycle								|
	MOVWF	N2	    ; 1 cycle								|
T2_10ms:		    ; <-------------------------------------------------		|
	MOVLW	25	    ; 1 cycle						|		|
	MOVWF	N1	    ; 1 cycle						|		|
T1_10ms:		    ; <-------------------------------------		|		|
	DECFSZ	N1, f	    ; 1 cycle si N1>0 et 3 cycles si N1=0   |T1=25*3	|		|
	GOTO	T1_10ms	    ; 2 cycles	<---------------------------		|		|
	DECFSZ	N2, f	    ; 1 cycle si N2>0 et 3 cycles si N2=0		|T2=250*(2+T1+3)|
	GOTO	T2_10ms	    ; 2 cycles	<---------------------------------------		|
	DECFSZ	Nx, f	    ; 1 cycle si N3>0 et 3 cycles si N3=0				|T3=Nx*(2+T2+3)
	GOTO	T3_10ms	    ; 2 cycles	<-------------------------------------------------------
FinNx10ms:
	RETURN		    ; 2 cycles		TempoNx10ms = T3 + 2 + 2 = Nx*T2 + 5*Nx + 4

;*******************************************************************************
; Temporisation3 = Nx * 100ms la variable Nx contiendra le nombre de 100 ms	
;*******************************************************************************
TempoNx100ms:		; Quartz = 8 MHz  --> Cycle instruction = 2 MHz --> 0,5 µs
	MOVF	Nx	; Test la variable Nx 
	BZ	FinNx100ms ; Si Nx = 0 --> pas de temporisation
T4_100ms:			; <-------------------------------------------------------------
	MOVLW	10	; 1 cycle								|
	MOVWF	N3	; 1 cycle								|
T3_100ms:		; <-----------------------------------------------------------------	|	
	MOVLW	250	; 1 cycle							    |	|
	MOVWF	N2	; 1 cycle							    |	|
T2_100ms:		; <-------------------------------------------------		    |	|
	MOVLW	25	; 1 cycle					    |		    |	|
	MOVWF	N1	; 1 cycle					    |		    |	|
T1_100ms:		; <-------------------------------------	    |		    |	|
	DECFSZ	N1, f	; 1 cycle si N1>0 et 3 cycles si N1=0	|T1=VN1*3   |		    |	|
	GOTO	T1_100ms; 2 cycles	<-----------------------	    |		    |	|
	DECFSZ	N2, f	; 1 cycle si N2>0 et 3 cycles si N2=0		    |T2=VN2*(2+T1+3)|	|
	GOTO	T2_100ms; 2 cycles	<-----------------------------------		    |	|
	DECFSZ	N3, f	; 1 cycle si N3>0 et 3 cycles si N3=0				    |	|
	GOTO	T3_100ms; 2 cycles	<--------------------------------T3=VN3*(2+T2+3)----	|
	DECFSZ	Nx, f	; 									|
	GOTO	T4_100ms ; <--------------------- T4 = Nx*(2+T3+3)---------------------------
FinNx100ms:
	RETURN		; 2 cycles	TempoNx100ms = T4 + 2 + 2 = Nx*T3 + 5*Nx + 4
	


