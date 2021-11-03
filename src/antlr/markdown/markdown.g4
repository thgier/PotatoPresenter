grammar markdown;

markdown
    : (paragraph | list | latex_next_line)+
    ;
    
list
    : itemize | enumeration
    ;
    
item_second
    : ('    ' STAR paragraph?)
    ;
    
item 
    : (STAR paragraph?) (enum_item_second* | item_second*)
    ;

itemize
    : item+
    ;
    
enumeration
    : enum_item+ 
    ;
    
enum_item
    : (INT '.') paragraph? (enum_item_second* | item_second*)
    ;

enum_item_second
    : ('    ' INT '.') paragraph?
    ;
    
paragraph
    : (text_decorated | text_plain | latex | '_')+ (new_line+ | EOF)
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
    : '$$'  (text_plain | '_' | STAR)+ '$$' (new_line+ | <EOF>)
    ;
    
new_line
    : '\n'
    ;
    
text_plain
    : (TEXT | INT | '.')+
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
    : ~[*$_\n.0123456789]+
    ;


