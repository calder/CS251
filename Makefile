COMPILER   = clang
INCLUDE    = -ISource
SOURCE     = Source/Tokenizer.c
TESTS      = Tests/Main.c


test: ${SOURCE} ${TESTS}
	@${COMPILER} ${INCLUDE} ${SOURCE} ${TESTS} -o Test
	@./Test

clean:
	@rm Test