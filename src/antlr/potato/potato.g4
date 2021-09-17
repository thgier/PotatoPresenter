grammar potato;

potato: box*;

box : command paragraph;

command : BACKSLASH TEXT ('[' property_entry (';' ' '? property_entry)* ']')? ' '?;

property_entry : text_colon value;

value: (TEXT | ' ')*;

paragraph: (NEWLINE? text)? (NEWLINE | NEWLINE? EOF) ;

text : oneline_text (NEWLINE oneline_text)*;

oneline_text: (TEXT | ' ' | text_colon | ';' | '[' | ']')+ (TEXT | ' ' | text_colon | ';' | '[' | ']' | BACKSLASH)*;

text_colon: TEXT ' '? ':' ' '?;

BACKSLASH : [\\];

NEWLINE : '\n'+ ; 

TEXT : ~([\][] | [\\] | [\n] | [ :;])+;
