	AREA matrix, DATA
	ALIGN
mat1 DCD 1,2,3,4,5,6,7,8,9
mat2 DCD 0,0,0,0,0,0,0,0,0
rows DCD 3
	
	
	AREA sum, CODE
	EXPORT __main
	ENTRY
	
__main PROC
	LDR r0, =mat1;	mat1 is stored in r0
	LDR r1, =mat2;	mat2 is stored in r1
	
	LDR r3, [r0,#0];
	STR r3, [r1];
	
	LDR r3, [r0,#12];
	STR r3, [r1,#4];
	
	LDR r3, [r0,#24];
	STR r3, [r1,#8];
	
	LDR r3, [r0,#4];
	STR r3, [r1,#12];
	
	LDR r3, [r0,#16];
	STR r3, [r1,#16];
	
	LDR r3, [r0,#28];
	STR r3, [r1,#20];
	
	LDR r3, [r0,#8];
	STR r3, [r1,#24];
	
	LDR r3, [r0,#20];
	STR r3, [r1,#28];
	
	LDR r3, [r0,#32];
	STR r3, [r1,#32];
	
	ENDP
	END