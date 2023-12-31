.Phony: start
start: main.o sorts.o work_with_file.o
	clang++ main.o sorts.o work_with_file.o -o main
main.o: main.cpp
	clang++ -c main.cpp
sorts.o: sorts.cpp
	clang++ -c sorts.cpp
work_with_file.o: work_with_file.cpp
	clang++ -c work_with_file.cpp






# .PHONY: start
# start: main.o check.o solve.o work_with_command_line.o
# 	clang++ main.o check.o solve.o work_with_command_line.cpp -o output
#
# main.o: main.cpp solve.h read_coefficient.h
# 	clang++ -c main.cpp
#
# check.o: check.cpp solve.h read_coefficient.h unit_tests.h
# 	clang++ -c check.cpp
#
# solve.o: solve.cpp solve.h read_coefficient.h unit_tests.h
# 	clang++ -c solve.cpp
# work_with_command_line.o: work_with_command_line.cpp read_coefficient.h
# 	clang++ -c work_with_command_line.cpp
