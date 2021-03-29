# Potato Presenter

Tool to create presentation slides that can be exported as PDF.

Content and appearance of slides is defined in a simple text format, similar to LaTeX.
This text is then converted into a set of slides.
Additionally, elements' position and size can be interactively adjusted with the mouse.

<img src="/images/screenshot.png">

## Basic Usage

Type your input in the editor on the left side.
A preview is shown immediately on the right.

Commands always starts with a "\".  
Create a new Slide with ```\slide title```.  
Create a title on your slide with ```\title```.  
Create a text with ```\body text```.  
Create an image with ```\image path_to_image```.  

You can move, rotate and scale your elements with the mouse on the panel on the right side.

When you are finished click "Export PDF" to export your presentation as PDF and present it with your PDF Viewer.

If you save the document a second file (JSON) is generated containing the elements' positions.

## Advanced functionality

### Basic Markdown Support

Text elements supports some markdown features like:  

Type \*\*Bold\*\* to get **Bold**.  
Type \_\_italic\_\_ to get _italic_.  
Type * at the start of the line to get a itemize list.  
Type a number with a point at the start of the line to get an enumeration list.  
Type $ \pi $ to get a formula showing a Pi.  
Type $$ \pi $$ to get a formula in the next line.  


### Arguments after Commands

You can give arguments after a commands in square brackets, that are similar to the CSS Properties:

e.g. ```\body[color: grey; text-align: right]```

List of supported arguments:

Argument | Functionality | Examples
------------ | ------------------ | -------------
color | Color of font, arrow, line | blue, #aa55ff
font | Font name | Hack
font-size | Font-size | 50
text-align | Text alignment | left, right, center, justify
line-height | Fraction of line height | 1.5
font-weight | Font weight | bold, normal
opacity | Opacitiy of whole element | 0.7
id | ID of element | see section ID
class | Class of element | see section Class
background | Background color of element | red, #aa55ff
border | Creates a border around the element | 2px solid blue
left | Sets the position of the element left | 100
top | Sets the position of the element top | 100
width | Sets the position of the element width | 100
height | Sets the position of the element height | 100
angle | Sets the rotation angle in degree | 180
movable | Element cannot manipulate with the mouse | false, true


### Possible Commands

Comands | Functionality
------------ | -------------
```\slide``` | Creates a new Slide
```\text``` | Creates a new text element
```\image``` | Creates an image from the given path
```\code``` | Creates a Code box with highlithing given by the argument "```language```"
```\arrow``` | Creates an arrow
```\line``` | Creates a line
```\title``` | same as ```\text[class: title]```
```\body``` | same as ```\text[class: body]```
```\setvar``` | Sets variable
```\usetemplate``` | Sets template



### Classes

Elements can have a class given by the argument ```class```.
Predefined Classes are:  
```title, body, fullscreen, leftcolumn, rightcolumn```  
A Class can specify a list of arguments which the element has by default, e.g. the position or the font-size.
Nevertheless, arguments can also be given to an element and overrides the given by the class.
Elements with a class can also be manipulated on the right panel.


### ID 

Every Box has an ID. The application save the position and the id of every Box.
Usually the box ID is generated with the frame ID, the box type and the class.
So if you rename your frame or swap some boxes the boxes' geometry may change.
You can define an id to a Box with the argument ```id```.


## Stuff

Implemented with C++, the Qt Framework and the KTextEditor.  

Work in progress, application is not finished yet.  
Formula support only works on Linux, needs: LaTeX, dvisvgm.
