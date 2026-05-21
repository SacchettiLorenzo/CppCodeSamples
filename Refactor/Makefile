# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -Wextra -std=c++17

#Log Separator
LOG_SEPARATOR = printf "\n========== [%s] ==========\n\n" "$$(date '+%Y-%m-%d %H:%M:%S')"

# Directories
OUTDIR = bin
LOGDIR = log
IO = i_o
DTC = data_types_and_casting
PTR = pointers
COL = collections
OOP = object_oriented_programming
F = files
THR = threads
BMK = benchmarking
DP = design_patterns

# Default rule
all: dirs $(OUTDIR)/i_o $(OUTDIR)/data_types $(OUTDIR)/type_casting $(OUTDIR)/pointers $(OUTDIR)/pointers_misc $(OUTDIR)/collections $(OUTDIR)/object_oriented_programming  $(OUTDIR)/files $(OUTDIR)/threads $(OUTDIR)/benchmarking

# Ensure output and log directory exists
.PHONY: dirs

dirs:
	mkdir -p $(OUTDIR) $(LOGDIR)

#make bin/i_o
$(OUTDIR)/i_o : $(IO)/i_o.cpp | dirs
	@$(LOG_SEPARATOR) >> $(LOGDIR)/i_o.log 
	$(CXX) $(CXXFLAGS) -o $(OUTDIR)/i_o $(IO)/i_o.cpp 2>&1 | tee -a $(LOGDIR)/i_o.log 
	
#make bin/data_types
$(OUTDIR)/data_types : $(DTC)/data_types.cpp | dirs
	@$(LOG_SEPARATOR) >> $(LOGDIR)/data_types.log 
	$(CXX) $(CXXFLAGS) -o $(OUTDIR)/data_types $(DTC)/data_types.cpp 2>&1 | tee -a $(LOGDIR)/data_types.log 

#make bin/type_casting
$(OUTDIR)/type_casting : $(DTC)/type_casting.cpp | dirs
	@$(LOG_SEPARATOR) >> $(LOGDIR)/type_casting.log 
	$(CXX) $(CXXFLAGS) -o $(OUTDIR)/type_casting $(DTC)/type_casting.cpp 2>&1 | tee -a $(LOGDIR)/type_casting.log 
	
#make bin/pointers
$(OUTDIR)/pointers : $(PTR)/pointers.c $(PTR)/pointers_misc.c | dirs
	@$(LOG_SEPARATOR) >> $(LOGDIR)/pointers.log 
	$(CXX) $(CXXFLAGS) -o $(OUTDIR)/pointers $(PTR)/pointers.c 2>&1 | tee -a $(LOGDIR)/pointers.log 
	$(CXX) $(CXXFLAGS) -o $(OUTDIR)/pointers_misc $(PTR)/pointers_misc.c 2>&1 | tee -a $(LOGDIR)/pointers.log 

#make bin/collections	
$(OUTDIR)/collections : $(COL)/collections.cpp | dirs
	@$(LOG_SEPARATOR) >> $(LOGDIR)/collections.log 
	$(CXX) $(CXXFLAGS) -Iinclude \
	$(COL)/collections.cpp \
	$(COL)/array.cpp \
	$(COL)/enum.cpp \
	$(COL)/list.cpp \
	$(COL)/map.cpp \
	$(COL)/queue.cpp \
	$(COL)/vector.cpp \
	-o $(OUTDIR)/collections 2>&1 | tee -a $(LOGDIR)/collections.log 

#make bin/object_oriented_programming
$(OUTDIR)/object_oriented_programming : $(OOP)/object_oriented_programming.cpp | dirs
	@$(LOG_SEPARATOR) >> $(LOGDIR)/object_oriented_programming.log 
	$(CXX) $(CXXFLAGS) -Iinclude \
	$(OOP)/object_oriented_programming.cpp \
    	$(OOP)/entity.cpp \
    	$(OOP)/player.cpp \
    	$(OOP)/enemy.cpp \
    	$(OOP)/opponent.cpp \
	-o $(OUTDIR)/object_oriented_programming 2>&1 | tee -a $(LOGDIR)/object_oriented_programming.log 

#make bin/files
$(OUTDIR)/files : $(F)/files.cpp | dirs
	@$(LOG_SEPARATOR) >> $(LOGDIR)/files.log 
	$(CXX) $(CXXFLAGS) -o $(OUTDIR)/files $(F)/files.cpp 2>&1 | tee -a $(LOGDIR)/files.log 

#make bin/threads
$(OUTDIR)/threads : $(THR)/threads.cpp $(THR)/mutex.cpp $(THR)/arguments.cpp $(THR)/condition_variable.cpp $(THR)/future_async.cpp $(THR)/packaged_task.cpp $(THR)/promise.cpp $(THR)/thread_guard.cpp $(THR)/thread_spawn.cpp | dirs
	@$(LOG_SEPARATOR) >> $(LOGDIR)/threads.log 
	$(CXX) $(CXXFLAGS) -pthread -o $(OUTDIR)/threads $(THR)/threads.cpp 2>&1 | tee -a $(LOGDIR)/threads.log
	$(CXX) $(CXXFLAGS) -pthread -o $(OUTDIR)/mutex $(THR)/mutex.cpp 2>&1 | tee -a $(LOGDIR)/threads.log
	$(CXX) $(CXXFLAGS) -pthread -o $(OUTDIR)/arguments $(THR)/arguments.cpp 2>&1 | tee -a $(LOGDIR)/threads.log
	$(CXX) $(CXXFLAGS) -pthread -o $(OUTDIR)/condition_variable $(THR)/condition_variable.cpp 2>&1 | tee -a $(LOGDIR)/threads.log
	$(CXX) $(CXXFLAGS) -pthread -o $(OUTDIR)/future_async $(THR)/future_async.cpp 2>&1 | tee -a $(LOGDIR)/threads.log
	$(CXX) $(CXXFLAGS) -pthread -o $(OUTDIR)/packaged_task $(THR)/packaged_task.cpp 2>&1 | tee -a $(LOGDIR)/threads.log
	$(CXX) $(CXXFLAGS) -pthread -o $(OUTDIR)/promise $(THR)/promise.cpp 2>&1 | tee -a $(LOGDIR)/threads.log
	$(CXX) $(CXXFLAGS) -pthread -o $(OUTDIR)/thread_guard $(THR)/thread_guard.cpp 2>&1 | tee -a $(LOGDIR)/threads.log
	$(CXX) $(CXXFLAGS) -pthread -o $(OUTDIR)/thread_spawn $(THR)/thread_spawn.cpp 2>&1 | tee -a $(LOGDIR)/threads.log

#make bin/benchmarking
$(OUTDIR)/benchmarking : $(BMK)/benchmarking.cpp | dirs
	@$(LOG_SEPARATOR) >> $(LOGDIR)/benchmarking.log 
	$(CXX) $(CXXFLAGS) -o $(OUTDIR)/benchmarking $(BMK)/benchmarking.cpp 2>&1 | tee -a $(LOGDIR)/benchmarking.log

#make bin/design_patterns
$(OUTDIR)/design_patterns : \
$(DP)/neural_network.cpp $(DP)/singleton.cpp $(DP)/monostate.cpp \
$(DP)/factory.cpp $(DP)/inner_factory.cpp $(DP)/groovy_builder.cpp $(DP)/fluent_builder.cpp \
$(DP)/static_decorator.cpp $(DP)/dynamic_decorator.cpp $(DP)/functional_decorator.cpp \
$(DP)/object_duplication.cpp $(DP)/property_proxy.cpp $(DP)/virtual_proxy.cpp \
$(DP)/memento.cpp $(DP)/flyweight.cpp $(DP)/mediator.cpp $(DP)/pointer_chain.cpp \
$(DP)/filter.cpp | dirs
	@$(LOG_SEPARATOR) >> $(LOGDIR)/design_patterns.log 
	$(CXX) $(CXXFLAGS) -o $(OUTDIR)/neural_network $(DP)/neural_network.cpp 2>&1 | tee -a $(LOGDIR)/design_patterns.log  
	$(CXX) $(CXXFLAGS) -o $(OUTDIR)/singleton $(DP)/singleton.cpp 2>&1 | tee -a $(LOGDIR)/design_patterns.log
	$(CXX) $(CXXFLAGS) -o $(OUTDIR)/monostate $(DP)/monostate.cpp 2>&1 | tee -a $(LOGDIR)/design_patterns.log
	$(CXX) $(CXXFLAGS) -o $(OUTDIR)/factory $(DP)/factory.cpp 2>&1 | tee -a $(LOGDIR)/design_patterns.log
	$(CXX) $(CXXFLAGS) -o $(OUTDIR)/inner_factory $(DP)/inner_factory.cpp 2>&1 | tee -a $(LOGDIR)/design_patterns.log
	$(CXX) $(CXXFLAGS) -o $(OUTDIR)/groovy_builder $(DP)/groovy_builder.cpp 2>&1 | tee -a $(LOGDIR)/design_patterns.log
	$(CXX) $(CXXFLAGS) -o $(OUTDIR)/fluent_builder $(DP)/fluent_builder.cpp 2>&1 | tee -a $(LOGDIR)/design_patterns.log
	$(CXX) $(CXXFLAGS) -o $(OUTDIR)/static_decorator $(DP)/static_decorator.cpp 2>&1 | tee -a $(LOGDIR)/design_patterns.log
	$(CXX) $(CXXFLAGS) -o $(OUTDIR)/dynamic_decorator $(DP)/dynamic_decorator.cpp 2>&1 | tee -a $(LOGDIR)/design_patterns.log
	$(CXX) $(CXXFLAGS) -o $(OUTDIR)/functional_decorator $(DP)/functional_decorator.cpp 2>&1 | tee -a $(LOGDIR)/design_patterns.log
	$(CXX) $(CXXFLAGS) -o $(OUTDIR)/object_duplication $(DP)/object_duplication.cpp 2>&1 | tee -a $(LOGDIR)/design_patterns.log
	$(CXX) $(CXXFLAGS) -o $(OUTDIR)/property_proxy $(DP)/property_proxy.cpp 2>&1 | tee -a $(LOGDIR)/design_patterns.log
	$(CXX) $(CXXFLAGS) -o $(OUTDIR)/virtual_proxy $(DP)/virtual_proxy.cpp 2>&1 | tee -a $(LOGDIR)/design_patterns.log
	$(CXX) $(CXXFLAGS) -o $(OUTDIR)/memento $(DP)/memento.cpp 2>&1 | tee -a $(LOGDIR)/design_patterns.log
	$(CXX) $(CXXFLAGS) -o $(OUTDIR)/flyweight $(DP)/flyweight.cpp 2>&1 | tee -a $(LOGDIR)/design_patterns.log
	$(CXX) $(CXXFLAGS) -o $(OUTDIR)/mediator $(DP)/mediator.cpp 2>&1 | tee -a $(LOGDIR)/design_patterns.log
	$(CXX) $(CXXFLAGS) -o $(OUTDIR)/pointer_chain $(DP)/pointer_chain.cpp 2>&1 | tee -a $(LOGDIR)/design_patterns.log
	$(CXX) $(CXXFLAGS) -o $(OUTDIR)/filter $(DP)/filter.cpp 2>&1 | tee -a $(LOGDIR)/design_patterns.log

# Clean build files
clean:
	rm -rf $(OUTDIR) 

rmlog: 
	rm -rf $(LOGDIR)
