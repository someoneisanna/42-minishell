Shell Implementation:

1. Create a main loop with the readline function to have the shell prompt
2. Start with the implementation of the parser
3. The parser contains two parts:
	a) Lexical Analysis / Tokenization - takes the input and breaks it down into individual tokens. it will also examine each token and classify it based on its role
	b) Syntactic Analysis - Detects and reports syntax errors when the code violates the language's grammar rules
4. Command Execution
