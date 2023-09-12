grammar Expr;

formula: expr;
expr:
    op=NOT right=expr                                     #Not
    | atomic=ATOMIC                                       #Atomic
    | boolean=BOOL                                        #Boolean
    | <assoc=right> op=NEXT_STRONG right=expr             #NextStrong
    | <assoc=right> op=NEXT_WEAK right=expr               #NextWeak
    | <assoc=right> op=GLOBALLY right=expr                #Globally
    | <assoc=right> op=FUTURE right=expr                  #Future
	| <assoc=right> left=expr op=UNTIL right=expr         #Until
	| <assoc=right> left=expr op=RELEASE right=expr       #Release
    | <assoc=right> op=ONCE right=expr                    #Once
    | <assoc=right> op=PREVIOUSLY right=expr              #Previously
	| left=expr op=AND right=expr                         #And
	| left=expr op=OR right=expr                          #Or
	| left=expr op=XOR right=expr                         #Xor
	| <assoc=right> left=expr op=IMPL right=expr          #Implication
	| <assoc=right> left=expr op=EQ right=expr            #Equivalence
    | '(' content=expr+ ')'                               #Brackets
    ;
BOOL		: TRUE|FALSE;
NOT         : ('!'|'not');
GLOBALLY	: 'G';
FUTURE		: 'F';
NEXT_WEAK	: 'W';
NEXT_STRONG	: 'X';
UNTIL		: 'U';
RELEASE		: 'R';
ONCE        : 'O';
PREVIOUSLY  : 'P';
AND        	: ('&'|'and');
OR         	: ('|'|'or');
XOR         : ('^'|'xor');
IMPL       	: '->';
EQ          : '<->';
TRUE       	: ('True'|'true');
FALSE      	: ('False'|'false');
ATOMIC		: [a-z]+([_]?[a-z]+)*;
WS          : [ \t\n]+ -> skip;       //Skip whitespaces
