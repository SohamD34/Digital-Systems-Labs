	AREA sum, CODE
	EXPORT __main
	ENTRY
	
__main PROC
	LDR r0 , =0x00000005; n=5 
	MOV r1 , #0;   i=0
	MOV r2 , #0;   sum=0
	
LOOP
	CMP r1 , r0;  if i<5
	BGT DONE
	ADD r2 , r1;  sum+=i
	ADD r1 , #1;   i++
	B LOOP
	
DONE B DONE
	ENDP
	END