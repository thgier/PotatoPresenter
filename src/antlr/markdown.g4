/*
[The "BSD licence"]
Copyright (c) 2012 Tom Everett
All rights reserved.
Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:
1. Redistributions of source code must retain the above copyright
notice, this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright
notice, this list of conditions and the following disclaimer in the
documentation and/or other materials provided with the distribution.
3. The name of the author may not be used to endorse or promote products
derived from this software without specific prior written permission.
THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

grammar markdown;

markdown
    : (paragraph | itemize)+
    ;
    
paragraph
    : (text_plain | text_decorated | latex)+ (new_line | EOF)
    ;
    
text_decorated
    : text_bold | text_italic
    ;
        
text_bold
    : '**' (text_plain | text_decorated)+ '**'
    ;

text_italic
    : '__' (text_plain | text_decorated)+ '__'
    ;

text_plain
    : (TEXT | '*' | '_')+
    ;

latex
    : '$' text_plain '$'
    ;
    
new_line
    : '\n'
    ;
    
item 
    : ('* ' paragraph?)
    ;

itemize
    : item+
    ;

fragment S_CHAR
   : ~ ["\\]
   ;


fragment NONDIGIT
   : '_' | 'a' .. 'z' | 'A' .. 'Z'
   ;


STRING
   : '"' ( S_CHAR | S_ESCAPE )* '"'
   ;


fragment Q_CHAR
   : NONDIGIT | DIGIT | '!' | '#' | '$' | '%' | '&' | '(' | ')' | '*' | '+' | ',' | '-' | '.' | '/' | ':' | ';' | '<' | '>' | '=' | '?' | '@' | '[' | ']' | '^' | '{' | '}' | '|' | '~'
   ;


fragment S_ESCAPE
   : '\\' ('’' | '\'' | '"' | '?' | '\\' | 'a' | 'b' | 'f' | 'n' | 'r' | 't' | 'v')
   ;


fragment DIGIT
   : '0' .. '9'
   ;


fragment UNSIGNED_INTEGER
   : DIGIT (DIGIT)*
   ;


UNSIGNED_NUMBER
   : UNSIGNED_INTEGER ('.' (UNSIGNED_INTEGER)?)? (('e' | 'E') ('+' | '-')? UNSIGNED_INTEGER)?
   ;


WS
   : [ \r\n\t] + -> channel (HIDDEN)
   ;

COMMENT
    :   '/*' .*? '*/' -> channel (HIDDEN)
    ;

LINE_COMMENT
    :   '//' ~[\r\n]* -> channel (HIDDEN)
    ;
    
TEXT
    : ~[*_$\n]+
    ;

