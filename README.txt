Shell Implementation:

1. Create a main loop with the readline function to have the shell prompt
2. Start with the implementation of the parser
3. The parser contains two parts:
	a) Lexical Analysis / Tokenization - takes the input and breaks it down into individual tokens. it will also examine each token and classify it based on its role.
	b) Syntactic Analysis - detects and reports syntax errors when the code violates the language's grammar rules.
	c) Expansion - takes the built tokens and looks for $. If it finds it, performs the required expansions.
	d) Command Table Creation - creates the final command table that will be used in the Executor.
4. Command Execution
