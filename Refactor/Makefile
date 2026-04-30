# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -Wextra -std=c++17

BREAKLINE = \n----------\n

# Directories
OUTDIR = bin
LOGDIR = log
DTC = data_types_and_casting
PTR = pointers

# Default rule
all: dirs $(OUTDIR)/i_o $(OUTDIR)/data_types $(OUTDIR)/type_casting $(OUTDIR)/pointers $(OUTDIR)/pointers_misc

# Ensure output and log directory exists
.PHONY: dirs

dirs:
	mkdir -p $(OUTDIR) $(LOGDIR)
	
$(OUTDIR)/i_o : i_o.cpp | dirs
	@echo "\n========== ##### ==========\n" >> $(LOGDIR)/i_o.log 
	$(CXX) $(CXXFLAGS) -o $(OUTDIR)/i_o i_o.cpp 2>&1 | tee -a $(LOGDIR)/i_o.log 
	
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

# Clean build files
clean:
	rm -rf $(OUTDIR) 

rmlog: 
	rm -rf $(LOGDIR)