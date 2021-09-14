grammar markdown;

markdown
    : (list | paragraph)+
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
    : ((text_plain | text_decorated | latex)+ | latex_next_line) (new_line+ | EOF)
    ;
    
text_decorated
    : text_bold | text_italic
    ;
    
text_bold
    : '**' (text_plain | text_italic)+ '**'
    ;
    
text_italic
    : '__' (text_plain | text_bold)+ '__'
    ;

latex
    : '$' text_plain '$'
    ;
    
latex_next_line
    : '$$' text_plain '$$'
    ;
    
new_line
    : '\n'
    ;

text_plain
    : (TEXT | INT | '.' | '_' | '*')+
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


