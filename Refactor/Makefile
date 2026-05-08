# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -Wextra -std=c++17

# Directories
OUTDIR = bin
LOGDIR = log
IO = i_o
DTC = data_types_and_casting
PTR = pointers
COL = collections
OOP = object_oriented_programming

# Default rule
all: dirs $(OUTDIR)/i_o $(OUTDIR)/data_types $(OUTDIR)/type_casting $(OUTDIR)/pointers $(OUTDIR)/pointers_misc $(OUTDIR)/collections $(OUTDIR)/object_oriented_programming

# Ensure output and log directory exists
.PHONY: dirs

dirs:
	mkdir -p $(OUTDIR) $(LOGDIR)
	
$(OUTDIR)/i_o : $(IO)/i_o.cpp | dirs
	@echo "\n========== ##### ==========\n" >> $(LOGDIR)/i_o.log 
	$(CXX) $(CXXFLAGS) -o $(OUTDIR)/i_o $(IO)/i_o.cpp 2>&1 | tee -a $(LOGDIR)/i_o.log 
	
$(OUTDIR)/data_types : $(DTC)/data_types.cpp | dirs
	@echo "\n========== ##### ==========\n" >> $(LOGDIR)/data_types.log 
	$(CXX) $(CXXFLAGS) -o $(OUTDIR)/data_types $(DTC)/data_types.cpp 2>&1 | tee -a $(LOGDIR)/data_types.log 

$(OUTDIR)/type_casting : $(DTC)/type_casting.cpp | dirs
	@echo "\n========== ##### ==========\n" >> $(LOGDIR)/type_casting.log 
	$(CXX) $(CXXFLAGS) -o $(OUTDIR)/type_casting $(DTC)/type_casting.cpp 2>&1 | tee -a $(LOGDIR)/type_casting.log 
	
$(OUTDIR)/pointers : $(PTR)/pointers.c | dirs
	@echo "\n========== ##### ==========\n" >> $(LOGDIR)/pointers.log 
	$(CXX) $(CXXFLAGS) -o $(OUTDIR)/pointers $(PTR)/pointers.c 2>&1 | tee -a $(LOGDIR)/pointers.log 
	
$(OUTDIR)/pointers_misc : $(PTR)/pointers_misc.c | dirs
	@echo "\n========== ##### ==========\n" >> $(LOGDIR)/pointers_misc.log 
	$(CXX) $(CXXFLAGS) -o $(OUTDIR)/pointers_misc $(PTR)/pointers_misc.c 2>&1 | tee -a $(LOGDIR)/pointers_misc.log 
	
$(OUTDIR)/collections : $(COL)/collections.cpp | dirs
	@echo "\n========== ##### ==========\n" >> $(LOGDIR)/collections.log 
	$(CXX) $(CXXFLAGS) -Iinclude \
	$(COL)/collections.cpp \
	$(COL)/array.cpp \
	$(COL)/enum.cpp \
	$(COL)/list.cpp \
	$(COL)/map.cpp \
	$(COL)/queue.cpp \
	$(COL)/vector.cpp \
	-o $(OUTDIR)/collections 2>&1 | tee -a $(LOGDIR)/collections.log 

$(OUTDIR)/object_oriented_programming : $(OOP)/object_oriented_programming.cpp | dirs
	@echo "\n========== ##### ==========\n" >> $(LOGDIR)/object_oriented_programming.log 
	$(CXX) $(CXXFLAGS) -Iinclude \
	$(OOP)/object_oriented_programming.cpp \
    $(OOP)/entity.cpp \
    $(OOP)/player.cpp \
    $(OOP)/enemy.cpp \
    $(OOP)/opponent.cpp \
	-o $(OUTDIR)/object_oriented_programming 2>&1 | tee -a $(LOGDIR)/object_oriented_programming.log 

# Clean build files
clean:
	rm -rf $(OUTDIR) 

rmlog: 
	rm -rf $(LOGDIR)
