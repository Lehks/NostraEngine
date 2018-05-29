# Nostra Engine Shader Language Preprocessor Specification  

## §0 Word Definitions  
In the following context by whitespace it is meant to include tabs and spaces only and nothing else.  
By delimiter the following characters are meant: `;`, `{`  
By alphabet is meant: every alphanumeric character + `_`  

## §1 General Preprocessor Directives  
§1.1 Every directive begins with `#`.  
§1.2 A directive can have variable amounts of whitespace between the `#` and the actual  directive.  
§1.3 A directive has to end with `;`.  
§1.4 It is not possible to call multiple directives between delimiters.  
§1.5 Preprocessor directives are case sensitive.  
§1.6 Preprocessor directives can only contain characters from the alphabet.  

## §2 Define Directives  
§2.1 A define directive is called by the keyword `define` followed by the keywords of the corresponding context.  
§2.2 Defines will only replace specific keywords.  
§2.3 Defines will only be available after the definition, meaning that a defined object called before the definition will not be processed.  
§2.4 Defined objects will be recognized by their name, evaluated by their type and accordingly replaced.  

### §2.5 Defining Variables  
§2.5.1 A variable is defined by the following syntaxes:  
- `define <name> <value>`
- `define <name>`  

§2.5.2 `<name>` can be any character or string   from the alphabet.
§2.5.3 `<value>` can be any alphanumeric character, string, whitespace or nothing. Assigned values will be interpreted as a String and thus cannot execute any arithmetic.    
§2.5.4 A defined object recognized as variable will be replaced by its assigned value in a later context.  

### §2.6 Defining Macros  
§2.6.1 A macro is defined by the following syntaxes:  
- `define <name>(<parameterlist>) <expression>`  
- `define <name>(parameterlist) {<body>}`  

§2.6.2 `<name>` can be any character or string from the alphabet. `<name>` cannot start with a number.  
§2.6.3 `<parameterlist>` is a constellation one or multiple strings containing characters from the alphabet called parameters in the following context. Whitespace can be used.  
§2.6.4 A parameterlist containing only a single parameter cannot contain a comma. When defining a parameterlist containing multiple parameters each parameter has to be separated by a `,`.  
§2.6.5 `<expression>` is any expression that is either another allready defined macro or an expression valid in the actual language. For more information about expressions see the specification for the actual language  
§2.6.6 `<body>` is a constellation of multiple or one `<expression>` calls each separated by a `;`. Multiple expressions can be spread over multiple lines. Said expressions  
§2.6.7 Macros cannot contain return statements.
§2.6.8 A defined object recognized as variable will be evaluated and every correctly recognized set parameter will be evaluated and replaced to the assigned value in the body of the macro. After this step the whole object will be replaced by the body of the macro.  
§2.7 Defines can be undefined again by following syntaxes:
- `undefine <preprocessor variablename>`
- `undefine <preprocessor macroname>`
§2.8 Macros and variables can be redefined

## §3 Conditional Directives  
§3.1 A conditional directive is called by the following syntaxes:  
- `ifdef <condition> <block> endif`
- `ifdef <condition> <block> else <block> endif`
- `ifndef <condition> <block> endif`
- `ifndef <condition> <block> else <block> endif`

§3.2 Conditional directives can only evaluate preprocessor defined variables.  
§3.3 An `ifdef` directive evaluates the `<condition>` and deletes the corresponding `<block>` given `<condition>` evaluates to false.  
§3.3 An `ifndef` directive evaulates the `<condition>` and deletes the corresponding `<block>` given `<condition>` evaluates to true.  
§3.4 An `else` directive deletes the corresponding `<block>` if the `ifdef` condition evaluates to true or if the `ifndef` condition evaluates to false.  
§3.5.0 `<condition>` can have multiple syntaxes:
- `<preprocessor variable>`
- `<preprocessor variable> == <preprocessor variable>`
- `<preprocessor variable> == <value>`

§3.5.1 `<preprocessor variable>` determines whether the given preprocessor variable is defined or not resulting in either `true` or `false`  
§3.5.2 `<preprocessor variable> == <preprocessor variable>` determines whether both preprocessor variables have the same value resulting in `true` or `false`  
§3.5.3 `<preprocessor variable> == <value>` determines whether the given preprocessor variable is defined as the given value.  

## §4 Include Directives
§4.1 An include directive is called by the following syntax:
- `include "<source>"`

§4.2 An include directive has to copy the whole source to the position of the corresponding include call  
§4.2 Include directives have automated include guards, meaning a source cannot be included twice in the same target file.  
§4.3 `<source>` is an absolute or relative path to a file.  

## $5 Predefined Macros
§5.1 Depending on what context, specific Macros are already defined.  
$5.2 A variable called `SHADER_LANGUAGE` will be predefined with the corresponding target language.
- GLSL: `GLSL`  

## $6 Group Directives

§6.1 A group directive is called by the following syntax:
- `group <name>`  

§6.2 The group directive marks the following tokens as grouped until another group directive gets called or the file ends.  
§6.3 Each group gets treated as a seperate File. And will be processed to a seperate File.  
$6.4 The default group is called `default` and the output file will be called the same as the input.  