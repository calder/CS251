COMPILER    = clang
INCLUDE     = -ISource
SOURCE      = Source/*.c
TESTS       = Tests/*.c
HEADERS     = Source/*.h
TESTHEADERS = Tests/*.h


test: ${SOURCE} ${TESTS} ${HEADERS} ${TESTHEADERS}
	@${COMPILER} ${INCLUDE} ${SOURCE} ${TESTS} -o Test
	@./Test

debug: ${SOURCE} ${TESTS} ${HEADERS} ${TESTHEADERS}
	@${COMPILER} ${INCLUDE} ${SOURCE} ${TESTS} -o Test
	@gdb Test

clean:
	@rm Test