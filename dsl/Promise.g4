grammar Promise;

prog:   (factdef)* promisedef;

factdef  :   ID ':' fact END;

fact     :   sfact
         |   pfact
         ;

pfact    : pfname 'predicate that' algo? pred ;

pfname   :  'location'
         |  'duration'
         |  'lane change'
         |  'lane gap'
         |  'distance to vehicle' INT
         ;

pred     : 'equal to' param
         | 'less than' param
         | 'greater than' param
         | 'between' param 'and' param
         ;

algo     : 'average'
         | 'variance'
         ;

sfact    : 'collision'
         | 'stop'
         ;

promisedef  : 'promise' ':' promise END;  

promise  :   promise '&&' promise         # con
         |   promise '||' promise         # opt
         |   promise '->' promise         # seq
         |   promise '-|' promise         # until
         |   promise '-<' promise         # daemon
         |   '!' basepromise              # notExist
         |   basepromise                  # exist 
         |   '(' promise ')'              # parens
         ;         

basepromise : ID                          # factId
            | '[' ID ']'                  # closureFactId
            | sfact                       # factName
            | '[' sfact ']'               # closureFactName
            ;          

param  :   value unit* ;

value  :   INT | FLOAT ; 

unit   :   'm'
       |   's'
       |   'km/h' 
       ;        

NOT    :   '!'  ;
CON    :   '&&' ;
OPT    :   '||' ;
SEQ    :   '->' ;
UNTIL  :   '-|' ;
DAEMON :   '-<' ;
ID     :   [A-Za-z]+ [0-9]* ;
INT    :   [0-9]+ ;
FLOAT  :   [0-9]+ '.' [0-9]+ ;  
END    :   '.' ;       
WS     :   [ \t\r\n]+ -> skip ;