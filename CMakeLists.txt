cmake_minimum_required (VERSION 3.0)

project (ants)

ADD_CUSTOM_COMMAND(
	OUTPUT test.txt
	PRE_BUILD
	COMMAND ls -al
	COMMENT "================="
)

subdirs (datastructures)


