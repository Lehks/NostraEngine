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
§2.1 A define directive is called by the keyword `define` followed by the keywords of the current context.  
§2.2 Defines will only replace specific keywords.  
§2.3 Defines will only be available after the definition, meaning that a defined object called before the definition will not be processed.  
§2.4 Defined objects will be recognized by their name, evaluated by their type and accordingly replaced.  

### §2.§VARIABLE_DEFINITION Defining Variables  
§2.§VARIABLE_DEFINITION.1 A variable is defined by the following syntax: `define <name> <value>` or `define <name>`.  
§2.§VARIABLE_DEFINITION.2 `<name>` can be any character or string from the alphabet.
§2.§VARIABLE_DEFINITION.3 `<value>` can be any alphanumeric character, string, whitespace or nothing.  
§2.§VARIABLE_DEFINITION.4 A defined object recognized as variable will be replaced by its assigned value in a later context.  

### §2.§MACRO_DEFINITION Defining Macros  
§2.§MACRO_DEFINITION.1 A macro is defined by the following syntax: `define <name>(<parameterlist>) <expression>` or `define <name>(parameterlist) {<body>}`.  
§2.§MACRO_DEFINITION.2 `<name>` can be any character or string from the alphabet. `<name>` cannot start with a number.  
§2.§MACRO_DEFINITION.3 `<parameterlist>` is a constelation one or multiple strings containing characters from the alphabet called parameters in the following context. Whitespace can be used.  
§2.§MACRO_DEFINITION.4 A parameterlist containing only a single parameter cannot contain a comma. When defining a parameterlist containing multiple parameters each parameter has to be seperated by a `,`.  
§2.§MACRO_DEFINITION.5 `<expression>` is any expression that is not another macro. For more information about expressions see the specification for the actual language  
§2.§MACRO_DEFINITION.6 `<body>` is a constellation of multiple or one `<expression>` calls each seperated by a `;`. Multiple expressions can be spread over multiple lines. Said expressions  
§2.§MACRO_DEFINITION.7 Macros cannot contain return statements.
§2.§MACRO_DEFINITION.8 A defined object regocnized as variable will be evaluated and every correctly recognized set paramter will be evaluated and replaced to the assigned value in the body of the macro. After this step the whole object will be replaced by the body of the macro.  

## §3 Conditional Directives  
§3.1 Conditional Directives can only evaluate preprocessor variables