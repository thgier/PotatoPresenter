grammar markdown;

markdown
    : (paragraph | list)+
    ;
    
list
    : itemize | enumeration
    ;
    
item_second
    : ('    *' paragraph?)
    ;
    
item 
    : ('*' paragraph?) (enum_item_second* | item_second*)
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
    : ((text_decorated | text_plain | latex | '_' | '*')+ | latex_next_line) (new_line+ | EOF)
    ;
    
text_decorated
    : text_bold | text_italic | text_marked
    ;
    
text_bold
    : '**' (text_plain | text_italic | text_marked)+ '**'
    ;
    
text_marked
    : '*' (text_plain | text_italic | text_bold)+ '*'
    ;
    
text_italic
    : '__' (text_plain | text_bold | text_marked)+ '__'
    ;

latex
    : '$' text '$'
    ;
    
latex_next_line
    : '$$'  text '$$'
    ;
    
new_line
    : '\n'
    ;
    
text
    : (text_plain | '_' | '*')+
    ;

text_plain
    : (TEXT | INT | '.')+
    ;
    
UNDERSCORE
    : '_'
    ;

INT   
    : ('0'..'9')+ 
    ;
TEXT
    : ~[*$_\n.0123456789]+
    ;


