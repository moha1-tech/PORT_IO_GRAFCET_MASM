    LIST	p = 18F45K22, r = dec	;  Définition du µC utilisé
    #include    <p18f45k22.inc>		;  Définition des registres SFR et leurs bits
    #include    <config.inc>		;  Configuration des registres hardwares
    #include	<Temporisation.inc>	;  Contient les 3 sous programmes de temporisations suivantes: 
					;	TempoNx1ms   = Nx1ms	(La variable Nx est déjà déclarée)
					; 	TempoNx10ms  = Nx10ms	(La variable Nx est déjà déclarée)
					; 	TempoNx100ms = Nx100ms	(La variable Nx est déjà déclarée)

;*******************************************************************************
;*			Définition des Symboles avec EQU
;*******************************************************************************
t	EQU	RC0
k	EQU	RC1
m	EQU	RC2
p	EQU	RC3
MG	EQU	RC6
MD	EQU	RC7					

;*******************************************************************************
;*			Réservation des variables avec res
;*******************************************************************************
uDataAccess udata_acs	0x00	; Adresse de uDataAccess = 0x00 (access page)

 
uDataPage   udata	0x100	; Adresse de uDataPage = 0x100 (no access page)

;*******************************************************************************
;*			VECTEURS D'INTERRUPTIONS:
;*******************************************************************************					
	ORG	0x0000		; Adresse de départ après le RESET
	GOTO	main

;*******************************************************************************
;*			PROGRAMME PRINCIPAL:
;*******************************************************************************
	ORG	0100h

main:	CALL	Init_Ports	; Initialisation PORTC
Etape0:	BCF	LATC, MD	; MD = 0
	BSF	LATC, MG	; MG = 1
	BTFSC	PORTC, t	; Saut si t = 0
	GOTO	Etape4		; si t = 1, on se branche à l'étape 4
	MOVF	PORTC, w	; PORTC --> W
	ANDLW	b'00001011'	; On ne conserve que les bits p, k et t
	SUBLW	b'00001010'	; b'00001010' - W --> W
	BZ	Etape1		; on se branche à l'étape 1 si p = 1, k = 1 et t = 0
	GOTO	Etape0		; Sinon, on boucle sur l'étape 0


;*******************************************************************************
;*			SOUS PROGRAMMES:
;*******************************************************************************
Etape1:
	BSF	LATC, MD	; MD = 1
	BSF	LATC, MG	; MG = 1	
	BTFSS	PORTC, k 	; On saute si k = 1
	GOTO	Etape3		; Si k = 0, on se branche à l'étape 3
	BTFSC	PORTC, m	; on saute si m = 0
	GOTO	Etape2		; on se branche à l'étape 2 si m = 1
	BTFSS	PORTC, p	; on saute si p = 1
	GOTO	Etape2		; on se branche à l'étape 2 si p = 0
	GOTO	Etape1		; sinon, on boucle sur l'étape 1
Etape2:
	BCF	LATC, MD	; MD = 0
	BSF	LATC, MG	; MG = 1		 
	BTFSC	PORTC, t	; On saute si t = 0
	GOTO	Etape3		; Si t = 1, on se branche à l'étape 3
	GOTO	Etape2		; sinon, on boucle sur l'étape 2
Etape3:
	BSF	LATC, MD	; MD = 1
	BCF	LATC, MG	; MG = 0	
	MOVF	PORTC, W	; PORTC --> W
	ANDLW	b'00000011'	; On ne conserve que les bits k et t
	BZ	Etape0		; on se branche à l'étape 0 si k = 0 et t = 0
	GOTO	Etape3		; Sinon, on boucle sur l'étape 3
Etape4:
	BSF	LATC, MD	; MD = 0
	BCF	LATC, MG	; MG = 1
	MOVLW	10		; WREG contient 10
	MOVWF	Nx		; (Nx) = 10
	CALL	TempoNx100ms	; Nx * 100ms = 10 * 100 ms = 1000 ms = 1 seconde
	GOTO	Etape0

Init_Ports:
	MOVLB	0xF		; 15 --> BSR (BSR pointe la page 15), utilisé car ANSELC 
													; est un SFR qui n'appartient pas à la page d'accès
	CLRF	ANSELC, 1	; PORTC E/S numérique (a = 1 ? BSR)
	CLRF	LATC		; Initialisation des latchs de données du port C
	CLRF	PORTC		; Initialisation des latchs de données du port C
	MOVLW	b'00111111'	; Configuration de la direction du PORTC
	MOVWF	TRISC		; RC7 et RC6 en sortie et RC3,...,RC0 en entrée
	RETURN

	END 