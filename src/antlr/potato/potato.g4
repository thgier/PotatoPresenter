grammar potato;

potato
    : box+
    ;

box 
    : command ws*? property_list? paragraph (' '* '\n'+ | EOF)
    ;

paragraph
    : ws* text_in_bracket
    | (' ' | ' '* '\n'+) text
    |
    ;

text
    : oneline_text 
    | multiline_text
    ;

multiline_text 
    : '\n'*? (oneline_text ' '* '\n'+)+ oneline_text
    ;
    
oneline_text
    : first_word every_letter_word*
    ;
    
first_word
    : (WORD | SPECIAL_CHARACTER | ':' | ';' | ']' | ' ')
    ;

every_letter_word   
    : first_word | '[' | '\\'
    ;
    
property_list
    : '[' property_entry (';' property_entry)* (';' ws*)? ']'
    | '[' ']'
    ;
    
property_entry
    : ws*? property ws*? ':' ws*? value ws*?
    ;
    
property
    : WORD
    ;
    
value
    : WORD (WORD | ' ')* WORD
    | WORD
    ;
    
command
    : '\\' WORD
    ;
    
text_in_bracket
    : TEXT_BRACKET
    ;

ws
    : (' ' | '\n')
    ;
    
SPECIAL_CHARACTER
    : ~([ \\;:\n] | ']' | '[' | [a-z] | [A-Z] | '-' | [0-9] | '.')+
    ;
    
WORD
    : ([a-z] | [A-Z] | '-' | [0-9] | '.' | '#')+
    ;

TEXT_BRACKET
    : '\\{' .*? '\\}'
    ;
