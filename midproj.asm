.MODEL SMALL

.DATA

I DB 0ah,0dh,'                                                 * Simple Calculator*$'



A DB 0ah,0dh,'                                                    ( 1 FOR ADDITION) :'1'$'
B DB 0ah,0dh,'                                                    ( 2 FOR SUBTRATION) :'2'$'
C DB 0ah,0dh,'                                                    ( 3 FOR MULTIPLE) :'3'$'
D DB 0ah,0dh,'                                                   ( 4 FOR DIVIDE) :'4'$'
E DB 0ah,0dh,'                                                   Select your choice:$'
F DB 0ah,0dh,'                                                    Insert first Number:$'
G DB 0ah,0dh,'                                                    Insert the secound Number:$'
H DB 0ah,0dh,'                                                 Insert Result after calculation is:$'


value1 DB ?

 value2 DB ?

 output DB ?


.CODE


MOV AX,@DATA

 MOV DS,AX

 LEA DX,I

 MOV AH,09h

 INT 21H
 
LEA DX,A




 MOV AH,09h

 INT 21H

 LEA DX,B
 
MOV AH,09h

 INT 21H

 LEA DX,C

 MOV AH,09h

 INT 21H

 LEA DX,D

 MOV AH,09h

 INT 21H

 LEA DX,E
 
MOV AH,09h

 INT 21H

 MOV AH,01h

 INT 21H

 MOV BH,AL

 SUB BH,48

 CMP BH,1

JE ADD

 CMP BH,2

 JE SUB

 CMP BH,3

 JE MUL

 CMP BH,4

 JE DIV


ADD:

 LEA DX,F

 MOV AH,09h

 INT 21H

 MOV AH,01h ;for entering the 1ST NUMBER

 INT 21H

 MOV BL,AL

 LEA DX,G

 MOV AH,09h

 INT 21H 


MOV AH,01h ;for entering the 2nd NUMBER

 INT 21H

 MOV CL,AL

 ADD AL,BL

 MOV AH,0

 AAA


 MOV BX,AX

 ADD BH,48

 ADD BL,48


 LEA DX,H

 MOV AH,09h

 INT 21H

 MOV AH,02h

 MOV DL,BH

 INT 21H

MOV AH,02h

 MOV DL,BL

 INT 21H


JMP EXIT_P





 SUB:

 LEA DX,F ;ENTER 1ST NUMBER

 MOV AH,09h

 INT 21H

 MOV AH,I

 INT 21H

 MOV BL,AL

 LEA DX,G ;ENTER 2ND NUMBER

 MOV AH,09h

 INT 21H



 MOV AH,1

 INT 21H

 MOV CL,AL


SUB BL,CL

 ADD BL,48



LEA DX,H

 MOV AH,09h

 INT 21H



 MOV AH,02h

 MOV DL,BL

 INT 21H

 JMP EXIT_P


 MUL:

 LEA DX,F

 MOV AH,09h

 INT 21H


 MOV AH,01h
 INT 21H

 SUB AL,30H

 MOV value1,AL


LEA DX,G

 MOV AH,09h

 INT 21H


 MOV AH,01h

 INT 21H

 SUB AL,30H

 MOV value2,AL


 MUL value1

 MOV output,AL

 AAM


 ADD AH,30H

 ADD AL,30H


 MOV BX,AX


 LEA DX,H

 MOV AH,09h

 INT 21H

 MOV AH,02h




MOV DL,BH
 INT 21H

 MOV AH,02h
 MOV DL,BL
 INT 21H



 JMP EXIT_P






 DIV:
 LEA DX,F
 MOV AH,09h
 INT 21H


 MOV AH,01h
 INT 21H

 SUB AL,30H

 MOV value1,AL
LEA DX,G

 MOV AH,09h

 INT 21H


 MOV AH,01h

 INT 21H

 SUB AL,30H

 MOV value2,AL

 MOV CL,value1

 MOV CH,00

 MOV AX,CX



 DIV value2

 MOV output,AL

 MOV AH, 00

 AAD


 ADD AH,30H

 ADD AL,30H


 MOV BX,AX


 LEA DX,H


MOV AH,09h

 INT 21H

 MOV AH,02h

 MOV DL,BH

 INT 21H

 MOV AH,02h

 MOV DL,BL

 INT 21H

 JMP EXIT_P

 EXIT_P:




ret
