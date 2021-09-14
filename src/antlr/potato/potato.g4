grammar potato;

potato: box* EOF;

box : command paragraph;

command : BACKSLASH TEXT property? ' '?;

property : '[' property_entry (';' ' '? property_entry)* ']';

property_entry : text_colon value;

value: (TEXT | ' ')*;

text : (TEXT | ' ' | text_colon | ';' | BACKSLASH) | (NEWLINE (TEXT | ' ' | text_colon | ';'))*;

paragraph: text NEWLINE;

text_colon: TEXT ' '? ':' ' '?;

BACKSLASH : [\\];

NEWLINE : '\n'+ ; 

TEXT : ~([\][] | [\\] | [\n] | [ :;])*;
