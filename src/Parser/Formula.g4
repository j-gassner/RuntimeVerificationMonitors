grammar Formula;
formula: expr;
expr
 : <assoc=right> left=expr op=IMPL right=expr   #Implication
 | <assoc=right> left=expr op=EQ right=expr     #Equivalence
 |  xor_expr                                    #XorExpr

 ;

xor_expr
 : or_expr (op=XOR or_expr)*                    #Xor
 ;

or_expr
 : and_expr (op=OR and_expr)*                   #Or
 ;

and_expr
 : release_until_expr (op=AND release_until_expr)*  #And
 ;

release_until_expr
: <assoc=right> left=unary op=RELEASE right=unary   #Release
| <assoc=right> left=unary op=UNTIL right=unary     #Until
| unary                                             #UnaryExpr
;


unary
: op=GLOBALLY right=atom        #Globally
  | op=FUTURE right=atom        #Future
  | op=ONCE right=atom          #Once
  | op=PREVIOUSLY right=atom    #Previously
  | op=NEXT_WEAK right=atom     #NextWeak
  | op=NEXT_STRONG right=atom   #NextStrong
  | op=NOT right=atom           #Not
  | op=NOT right=expr           #NotExpr
  | atom                        #AtomExpr
 ;

atom
 : BOOL                         #Boolean
 | ATOMIC                       #Atomic
 | '(' content=expr+ ')'        #Brackets
 ;

 BOOL		    : TRUE|FALSE;
 NOT            : ('!'|'not');
 GLOBALLY	    : 'G';
 FUTURE		    : 'F';
 NEXT_WEAK	    : 'W';
 NEXT_STRONG	: 'X';
 UNTIL		    : 'U';
 RELEASE		: 'R';
 ONCE           : 'O';
 PREVIOUSLY     : 'P';
 AND        	: ('&'|'and');
 OR         	: ('|'|'or');
 XOR            : ('^'|'xor');
 IMPL       	: '->';
 EQ             : '<->';
 TRUE       	: ('True'|'true');
 FALSE      	: ('False'|'false');
 ATOMIC		    : [a-z]+([_]?[a-z]+)*;
 WS             : [ \t\n]+ -> skip;       //Skip whitespaces
