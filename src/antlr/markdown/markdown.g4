grammar markdown;

markdown
    : ((paragraph | list | latex_next_line) '\n' )* EOF
    ;
    
list
    : itemization | enumeration
    ;
    
itemization
    : item ('\n' item)*
    ;
    
enumeration
    : enum_item ('\n' enum_item)*
    ;
    
item_second
    : ITEM_SECOND_INTRO paragraph
    ;
    
item 
    : ('*' ' ' paragraph) (enum_item_second+ | item_second+)?
    ;
    
enum_item
    : INT '.' ' ' paragraph (enum_item_second+ | item_second+)?
    ;

enum_item_second
    : ENUM_SECOND_INTRO paragraph
    ;
    
paragraph
    : (text_decorated | text_plain | latex | '_' )*
    ;
    
text_decorated
    : text_bold | text_italic | text_marked
    ;
    
text_bold
    : '**' (text_plain | text_italic | text_marked)+ '**'
    ;
    
text_marked
    : '*' (text_plain)+ '*'
    ;
    
text_italic
    : '__' (text_plain | text_bold | text_marked)+ '__'
    ;

latex
    : '$' (text_plain | '_' | STAR)+ '$'
    ;
    
latex_next_line
    : '$$'  (text_plain | '_' | STAR)+ '$$'
    ;
    
    
text_plain
    : (TEXT | ' ' | '.')+ (TEXT | ' ' | '.' | INT)*
    ;
    
ITEM_SECOND_INTRO
    : '\n' '    ' STAR ' '
    ;
    
ENUM_SECOND_INTRO
    : '\n' '    ' INT '.' ' '
    ;
    
UNDERSCORE
    : '_'
    ;
    
STAR
    : '*'
    ;

INT   
    : ('0'..'9')+
    ;
TEXT
    : ~[*$_\n.0123456789 ]+
    ;


