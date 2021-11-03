grammar potato;

potato: NEWLINE? box*;

box : command paragraph;

command : BACKSLASH TEXT SPACE? ('[' SPACE? property_list ']')?;

property_list: property_entry (';' SPACE? property_entry)*;

property_entry : property SPACE? (':' SPACE? value)?;

property: (TEXT | SPACE)*;

value: (TEXT | SPACE)*;

paragraph: paragraph_bracket | paragraph_without_bracket;

paragraph_without_bracket: (SPACE? NEWLINE? text)? (NEWLINE | NEWLINE? EOF);

paragraph_bracket: SPACE? NEWLINE? BACKSLASH_CURLED_BRACKET_OPEN SPACE? NEWLINE? text_in_bracket SPACE? NEWLINE? BACKSLASH_CURLED_BRACKET_CLOSE (NEWLINE | NEWLINE? EOF);

text : (oneline_text_first (NEWLINE oneline_text)*);

oneline_text_first:  (text_sign| '{' | '}' | SPACE) (text_sign | BACKSLASH | '{' | '}' | SPACE)*;

oneline_text: (text_sign | '{' | '}' | SPACE) (text_sign | BACKSLASH | '{' | '}' | SPACE)*;

text_in_bracket: (text_sign | BACKSLASH | NEWLINE | '{' | '}' | SPACE)+;

text_sign: (TEXT | ';' | '[' | ']' | ':')+;

BACKSLASH : [\\];

BACKSLASH_CURLED_BRACKET_OPEN : BACKSLASH '{';

BACKSLASH_CURLED_BRACKET_CLOSE : BACKSLASH '}';

NEWLINE : '\n'+ ; 

SPACE : ' '+;

TEXT : ~([\][] | [\\] | [\n] | [:;}{] | ' ')+;
