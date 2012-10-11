COMPILER    = clang
INCLUDE     = -ISource
SOURCE      = Source/*/*.c
HEADERS     = Source/*/*.h
TESTS       = Tests/*.c
TESTHEADERS = Tests/*.h


test: ${SOURCE} ${TESTS} ${HEADERS} ${TESTHEADERS}
	@${COMPILER} ${INCLUDE} ${SOURCE} ${TESTS} -o Test
	@./Test

debug: ${SOURCE} ${TESTS} ${HEADERS} ${TESTHEADERS}
	@${COMPILER} ${INCLUDE} ${SOURCE} ${TESTS} -o Test
	@gdb Test

clean:
	@rm Test